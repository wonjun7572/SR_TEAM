#include "stdafx.h"
#include "TestCube.h"
#include "WallMapping.h"
#include "LetterBox.h"
#include "Export_Function.h"
#include "CubePlayer.h"

static _int m_iMappingCnt = 0;
static _int m_iLetterCnt = 0;

CTestCube::CTestCube(LPDIRECT3DDEVICE9 pGraphicDev) : CGameObject(pGraphicDev)

{
}

CTestCube::CTestCube(const CGameObject& rhs) : CGameObject(rhs)
{
}

CTestCube::~CTestCube()
{
}

HRESULT CTestCube::Ready_Object(int PosX, int PosY)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	if (PosX == 0 && PosY == 0) {}
	else
	{ Set_TransformPositon(); }
	
	_vec3 vScale = { 0.5f,0.5f,0.5f };
	m_pTransCom->Set_Scale(&vScale);
	
	return S_OK;
}


_int CTestCube::Update_Object(const _float& fTimeDelta)
{
	if (m_bDead)
	{
		m_pStaticCam->CameraShaking();
		return -1;
	}
	Update_NullCheck();
	CGameObject::Update_Object(fTimeDelta);
	if (!(dynamic_cast<CBaseMapping*>(Engine::Get_GameObject(STAGE_MAPPING, L"BaseMapping"))->Get_Worldmap()))
	{
		Add_RenderGroup(RENDER_NONALPHA, this);
	}
	Wall_Mapping();
	Interact();
	m_fTimer += fTimeDelta;
	return 0;
}

void CTestCube::Render_Object()
{
	//빛표현 블랜딩
	//		m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//		m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	//간단한 그림자
	//m_pGraphicDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	//m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	//곱셈합성 스킬뷰에 쓰면 좋을듯
	//m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
	//m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);

	//제곱합성 밝은색은 그대로, 어두운색은 더 어둡게 ( 보스전 방 꾸미는 데 쓰면 좋을듯)
	//m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
	//m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);

	//네거티브, 포지티브 합성 (검<->흰)
	//m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	//m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);

	//불투명
	//m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	//m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	if(! (dynamic_cast<CBaseMapping*>(Engine::Get_GameObject(STAGE_MAPPING, L"BaseMapping"))->Get_Worldmap()))
	{
		if (m_bWireFrame)
			m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
		m_pTextureCom->Set_Texture(m_iTexIndex);
		m_pBufferCom->Render_Buffer();

		if (m_bWireFrame)
			m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

// 큐브를 선택 후 터레인 자리위에 올려 놓는 함수
void CTestCube::Set_TransformPositon()
{
	CTerrainTex*	pTerrainBufferCom = dynamic_cast<CTerrainTex*>(Engine::Get_Component(L"Layer_Tool", L"TerrainByTool", L"Proto_TerrainTexCom", ID_STATIC));
	NULL_CHECK_RETURN(pTerrainBufferCom, );

	CTransform*		pTerrainTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Tool", L"TerrainByTool", TRANSFORM_COMP, ID_DYNAMIC));
	NULL_CHECK_RETURN(pTerrainTransformCom, );

	_vec3 Temp = m_pCalculatorCom->Peek_Target_Vector(g_hWnd, &(_vec3(0.f,0.f,0.f)), pTerrainBufferCom, pTerrainTransformCom);

	m_pTransCom->Set_Pos(Temp.x, Temp.y, Temp.z);
}

bool CTestCube::Set_SelectGizmo()
{
	if (m_pCalculatorCom->Peek_Cube_Target(g_hWnd, &(_vec3(0.f, 0.f, 0.f)), m_pBufferCom, m_pTransCom))
		return true;

	return false;
}

void CTestCube::Update_NullCheck()
{
	if (!m_pMonsterParticle)
		m_pMonsterParticle = dynamic_cast<CMonsterParticle*>(Engine::Get_GameObject(STAGE_ENVIRONMENT, L"MonsterParticle"));
}


HRESULT CTestCube::Interact(void)
{
	CGameObject*		pGameObject = nullptr;
	CProjectileParticle* m_pProjectileParicle = nullptr;

	CTransform*		pPlayerTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_CHARACTER, L"BODY", TRANSFORM_COMP, ID_DYNAMIC));
	NULL_CHECK_RETURN(pPlayerTransformCom, E_FAIL);
	if (!m_pProjectileParicle)
		m_pProjectileParicle = dynamic_cast<CProjectileParticle*>(Engine::Get_GameObject(STAGE_ENVIRONMENT, L"ProjectileParticle"));
	
	


	_vec3		vPlayerPos;
	_vec3		vPos;
	_vec3		vDir;
	_float		fDistance;
	m_pTransCom->Get_Info(INFO_POS, &vPos);
	pPlayerTransformCom->Get_Info(Engine::INFO_POS, &vPlayerPos);
	vDir = vPos - vPlayerPos;
	fDistance = D3DXVec3Length(&vDir);

	_vec3		vGrenadePos;
	_vec3		vGPos;
	_vec3		vGDir;
	_float		fGDistance;
	vGPos = m_pProjectileParicle->Get_DeadPos();
	pPlayerTransformCom->Get_Info(Engine::INFO_POS, &vGrenadePos);
	vGDir = vPos- vGPos ;
	fGDistance = D3DXVec3Length(&vGDir);


	if (fDistance <= 12.f)
	{
		m_bSwitch = true;
	}
	if (fDistance > 12.f)
	{
		m_bSwitch = false;
	}

	if (!m_bLetterboxInit&& m_bSwitch)
	{
		if (m_iTexIndex == 37 || m_iTexIndex == 99)
		{
			m_bLetterboxInit = true;

			m_pLetterBox = CLetterBox::Create(m_pGraphicDev, L"Press [E] to Interact", sizeof(L"Press [E] to Interact"), 0);

			TCHAR* szCntName = new TCHAR[64];
			wsprintf(szCntName, L"");
			const _tchar*	szNumbering = L"WallLetter_%d";
			wsprintf(szCntName, szNumbering, m_iLetterCnt);
			Engine::Add_GameObject(STAGE_MAPPING, m_pLetterBox, szCntName);
			m_listWallCnt.push_back(szCntName);

			++m_iLetterCnt;
		}
	}

	if (m_bSwitch && Get_DIKeyState(DIK_E))
	{
		if (m_iTexIndex == 37 || m_iTexIndex == 99) //초록색문
			if (vPos.y < 15)
			{
				m_bDoorOpen = true;
			}
	}	

	if (fGDistance < 5)
	{
		if (m_iTexIndex == 45) // 갈색문
		{
			if (vPos.y <= 5)
			{
				m_bDead = true;
				m_bDoorUp = true;
				m_bCameraShaking = true;
				for (_int i = 0; i < 15; ++i)
				{
					m_pBrownCloudEffect->addParticle();
				};
			}
		}
	}

	if (m_bSwitch && m_pLetterBox != nullptr)
	{
		dynamic_cast<CLetterBox*>(m_pLetterBox)->On_Switch();
	}
	if (!m_bSwitch && m_pLetterBox !=nullptr)
	{
		dynamic_cast<CLetterBox*>(m_pLetterBox)->Off_Switch();
	}

	if (m_bSwitch &&m_iTexIndex == 45)
	{
		m_bDoorFall = true;
	}
	if (!m_bSwitch &&m_iTexIndex == 45)
	{
		m_bDoorUp = true;
	}
	if(m_bDoorOpen)
	{ 
		if (vPos.y > -15)
		{
			vPos.y -= 0.1f;
			m_pTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
		}
	}

	if (m_bDoorFall&&!m_bDoorUp)
	{
		if (m_pStaticCam == nullptr)
			m_pStaticCam = dynamic_cast<CStaticCamera*>(Engine::Get_GameObject(STAGE_ENVIRONMENT, L"StaticCamera"));
		if (!m_pBrownCloudEffect)
			m_pBrownCloudEffect = dynamic_cast<CBrownCloudEffect*>(Engine::Get_GameObject(STAGE_ENVIRONMENT, L"BrownCloudEffect"));
		m_pBrownCloudEffect->Set_PclePos(vPos);
		if (vPos.y > 5)
		{
			vPos.y -= 1.f;
			m_pTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
			m_fTimer = 0.f;
		}
		if (vPos.y <= 5)
		{
		
			m_bDoorFall = false;	

			if (m_bCameraShaking)
			{
				m_pStaticCam->CameraShaking();
				for (_int i = 0; i < 15; ++i)
					{
						m_pBrownCloudEffect->addParticle();
					}
				if (m_fTimer > 0.5f)
					m_bCameraShaking = false;
			}
		}
	}
	if (m_bDoorUp&&!m_bDoorFall)
	{
		if (vPos.y < 10)
		{
			vPos.y += 0.5f;
			m_pTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
		}
		if (vPos.y >= 10)
			m_bDoorUp = false;
		m_bCameraShaking = true;
	}

	return S_OK;
}

HRESULT CTestCube::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CCubeTex*>(Clone_Proto(L"Proto_CubeTexCom"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubeTexCom", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_CubePlayerTexture"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubePlayerTexture", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Clone_Proto(CALCULATOR_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ CALCULATOR_COMP, pComponent });

	pComponent = m_pHitBox = dynamic_cast<CHitBox*>(Clone_Proto(HITBOX_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ HITBOX_COMP, pComponent });


	return S_OK;
}

HRESULT CTestCube::Wall_Mapping(void)
{
	_vec3		vPos;
	_vec3		vSize;
	m_pTransCom->Get_Info(INFO_POS, &vPos);
	m_pTransCom->Get_Scale(&vSize);
	if (!m_bMappingInit)
	{
		m_bMappingInit = true;

		CGameObject*	m_pMapWall = CWallMapping::Create(m_pGraphicDev);
		if (m_pMapWall != nullptr && m_iTexIndex == 37 || m_iTexIndex == 45 || m_iTexIndex == 99)
		{
			
			dynamic_cast<CWallMapping*>(m_pMapWall)->Set_Texture(37);
		}
		TCHAR* szCntName = new TCHAR[64];
		wsprintf(szCntName, L"");
		const _tchar*	szNumbering = L"MapWall_%d";
		wsprintf(szCntName, szNumbering, m_iMappingCnt);
		Engine::Add_GameObject(STAGE_MAPPING, m_pMapWall, szCntName);
		m_listWallCnt.push_back(szCntName);

		
		m_pWallMapping = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_MAPPING, szCntName, TRANSFORM_COMP, ID_DYNAMIC));
		NULL_CHECK_RETURN(m_pWallMapping, E_FAIL);
		++m_iMappingCnt;
		
	}

	m_pWallMapping->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pWallMapping->Set_Scale(vSize.x, vSize.y, vSize.z);
	
	return S_OK;
}
CTestCube* CTestCube::Create(LPDIRECT3DDEVICE9 pGraphicDev, int Posx, int Posy)
{
	CTestCube*	pInstance = new CTestCube(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(Posx, Posy)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CTestCube::Free()
{
	for (auto& iter : m_listWallCnt)
	{
		if (iter != nullptr)
			delete iter;
	}

	m_listWallCnt.clear();	
	m_listLetterCnt.clear();
	CGameObject::Free();
}

