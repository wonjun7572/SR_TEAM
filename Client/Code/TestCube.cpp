#include "stdafx.h"
#include "TestCube.h"
#include "WallMapping.h"
#include "LetterBox.h"

#include "Export_Function.h"
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
	CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_NONALPHA, this);
	Wall_Mapping();
	Interact();
		
	return 0;
}

void CTestCube::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	

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


	if (m_bWireFrame)
		m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTextureCom->Set_Texture(m_iTexIndex);
	m_pBufferCom->Render_Buffer();

	if (m_bWireFrame)
		m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pHitBox->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

// 큐브를 선택 후 터레인 자리위에 올려 놓는 함수
void CTestCube::Set_TransformPositon()
{
	CTerrainTex*	pTerrainBufferCom = dynamic_cast<CTerrainTex*>(Engine::Get_Component(L"Layer_Tool", L"TerrainByTool", L"Proto_TerrainTexCom", ID_STATIC));
	NULL_CHECK_RETURN(pTerrainBufferCom, );

	CTransform*		pTerrainTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Tool", L"TerrainByTool", L"Proto_TransformCom", ID_DYNAMIC));
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

HRESULT CTestCube::Interact(void)
{
	CGameObject*		pGameObject = nullptr;

	CTransform*		pPlayerTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"BODY", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(pPlayerTransformCom, E_FAIL);
	_vec3		vPlayerPos;
	_vec3		vPos;
	_vec3		vDir;
	_float		fDistance;
	m_pTransCom->Get_Info(INFO_POS, &vPos);
	pPlayerTransformCom->Get_Info(Engine::INFO_POS, &vPlayerPos);
	vDir = vPos - vPlayerPos;
	fDistance = D3DXVec3Length(&vDir);
	
	
	if (fDistance <= 15.f)
	{
		m_bSwitch = true;
	}
	if (fDistance > 15.f)
	{
		m_bSwitch = false;
	}

	if (!m_bLetterboxInit&& m_iTexIndex == 37 && m_bSwitch)
	{
		m_bLetterboxInit = true;

		m_pLetterBox = CLetterBox::Create(m_pGraphicDev, L"Press [E] to Interact", sizeof(L"Press [E] to Interact"), 0);

		TCHAR* szCntName = new TCHAR[64];
		wsprintf(szCntName, L"WallLetter");
		Engine::Add_GameObject(L"Layer_Mapping", m_pLetterBox, szCntName);
		m_listLetterCnt.push_back(szCntName);

		++m_iLetterCnt;
		cout << m_iLetterCnt << endl;
		Safe_Delete_Array(szCntName);

	}

	if (m_bSwitch && Get_DIKeyState(DIK_E))
	{
		if (m_iTexIndex == 37) //초록색문
			if (vPos.y < 15)
				m_bDoorOpen = true;			
	}	

	if (m_bSwitch && m_pLetterBox != nullptr)
	{
		dynamic_cast<CLetterBox*>(m_pLetterBox)->On_Switch();
	}
	if (!m_bSwitch && m_pLetterBox !=nullptr)
	{
		dynamic_cast<CLetterBox*>(m_pLetterBox)->Off_Switch();
	}

	if(m_bDoorOpen)
	{ 
		if(vPos.y < 15)
		vPos.y -= 0.1f;
		m_pTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
	}
}

HRESULT CTestCube::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CCubeTex*>(Clone_Proto(L"Proto_CubeTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubeTexCom", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_CubePlayerTexture"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubePlayerTexture", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Clone_Proto(L"Proto_CalculatorCom"));
	NULL_CHECK_RETURN(m_pCalculatorCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CalculatorCom", pComponent });

	pComponent = m_pHitBox = dynamic_cast<CHitBox*>(Clone_Proto(L"Proto_HitboxCom"));
	NULL_CHECK_RETURN(m_pCalculatorCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_HitboxCom", pComponent });


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
		TCHAR* szCntName = new TCHAR[64];
		wsprintf(szCntName, L"");
		const _tchar*	szNumbering = L"MapWall_%d";
		wsprintf(szCntName, szNumbering, m_iMappingCnt);
		Engine::Add_GameObject(L"Layer_Mapping", m_pMapWall, szCntName);
		m_listWallCnt.push_back(szCntName);


		m_pWallMapping = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Mapping", szCntName, L"Proto_TransformCom", ID_DYNAMIC));
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


	CGameObject::Free();
}

