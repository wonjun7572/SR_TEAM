#include "stdafx.h"
#include "..\Header\TestPlayer.h"

#include "Export_Function.h"
#include "Wall.h"
#include "PoolMgr.h"

#include "UziPart1.h"

float g_fPlaySound = 1.f;

CTestPlayer::CTestPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_vDirection(0.f, 0.f, 0.f)
{
}

CTestPlayer::~CTestPlayer()
{
}

HRESULT CTestPlayer::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CTestPlayer::Update_Object(const _float & fTimeDelta)
{
	if (m_bDead)
	{
		return -1;
	}

	Key_Input(fTimeDelta);

	Engine::CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_NONALPHA, this);
	return 0;
}

void CTestPlayer::LateUpdate_Object(void)
{
	/*Engine::CGameObject::LateUpdate_Object();*/
	Set_OnTerrain();

	if (Hit_Check())
	{
		this->Kill_Obj();
	}
	//m_pHitBox->Get_MinMax(&m_vMin, &m_vMax);
	//Get_HitboxMin(&vT1, &vT2);
}

void CTestPlayer::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pHitBox->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

HRESULT CTestPlayer::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CCubeTex*>(Clone_Proto(L"Proto_CubeTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubeTexCom", pComponent });
   
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_CubePlayerTexture"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubePlayerTexture", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Clone_Proto(CALCULATOR_COMP));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ CALCULATOR_COMP, pComponent });

	pComponent = m_pHitBox = dynamic_cast<CHitBox*>(Engine::Clone_Proto(HITBOX_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ HITBOX_COMP, pComponent });

	pComponent = m_pCollision = dynamic_cast<CCollision*>(Engine::Clone_Proto(COLLISION_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ COLLISION_COMP, pComponent });

	return S_OK;
}

void CTestPlayer::Key_Input(const _float& fTimeDelta)
{
	m_pTransCom->Get_Info(INFO_LOOK, &m_vDirection);
	if (Get_DIKeyState(DIK_UP) & 0x8000)
	{
		PlaySoundW(L"explosion_rubble_stone_2.wav", SOUND_BGM, g_fPlaySound);
		D3DXVec3Normalize(&m_vDirection, &m_vDirection);
		m_pTransCom->Move_Pos(&(m_vDirection * 10.f * fTimeDelta));
	}

	if (Get_DIKeyState(DIK_DOWN) & 0x8000)
	{
		D3DXVec3Normalize(&m_vDirection, &m_vDirection);
		m_pTransCom->Move_Pos(&(m_vDirection * -10.f * fTimeDelta));
	}

	if (Get_DIKeyState(DIK_RIGHT) & 0x8000)
		m_pTransCom->Rotation(ROT_Y, D3DXToRadian(180.f * fTimeDelta));

	if (Get_DIKeyState(DIK_LEFT) & 0x8000)
		m_pTransCom->Rotation(ROT_Y, D3DXToRadian(-180.f * fTimeDelta));

	/*if (Get_DIMouseState(DIM_LB))
	{
		Fire_Bullet(&m_vDirection);
	}*/


	/*if (Get_DIMouseState(DIM_LB) & 0x80)
	{
		_vec3 vMyPos;
		m_pTransCom->Get_Info(INFO_POS, &vMyPos);
		_vec3 vPeekPos, vDir;
		vPeekPos = Mouse_Peeking();
		vDir = vPeekPos - vMyPos;
		m_pTransCom->Move_Pos(&(vDir * 10.f * fTimeDelta));
	}*/
}

void CTestPlayer::Set_OnTerrain(void)
{
	_vec3		vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);

	Engine::CTerrainTex*	pTerrainTexCom = dynamic_cast<Engine::CTerrainTex*>(Engine::Get_Component(L"Layer_Environment", L"Terrain", L"Proto_TerrainTexCom", ID_STATIC));
	NULL_CHECK(pTerrainTexCom);

	_float fHeight = m_pCalculatorCom->HeightOnTerrain(&vPos, pTerrainTexCom->Get_VtxPos(), VTXCNTX, VTXCNTZ);

	m_pTransCom->Set_Pos(vPos.x, fHeight + m_pTransCom->m_vScale.y, vPos.z);
}

void CTestPlayer::Create_Wall(const _uint& iCnt, const _uint& iTextureNum)
{
	_vec3		vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);

	CGameObject*	pWall = CWall::Create(m_pGraphicDev, iTextureNum, &vPos);

	TCHAR* szFinalName = new TCHAR[128];
	wsprintf(szFinalName, L"");

	const _tchar*	szWallName = L"Wall_%d";
	wsprintf(szFinalName, szWallName, iCnt);

	Engine::Add_GameObject(STAGE_WALL, pWall, szFinalName);
	m_liszFinalName.push_back(szFinalName);
}

void CTestPlayer::Fire_Bullet(const _vec3* pDir)
{
	_vec3		vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);
	FAILED_CHECK_RETURN(CPoolMgr::GetInstance()->Reuse_Obj(m_pGraphicDev, &vPos, pDir , 10.f), );
}

_bool CTestPlayer::Hit_Check(void)
{
	_vec3 vSrcPos;
	dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_GUN, L"Uzi_Part_1_1", TRANSFORM_COMP, ID_DYNAMIC))->Get_Info(INFO_POS, &vSrcPos);
	m_pTransCom->Static_Update();

	_vec3 vDir;

	if (m_pCollision->HitScan(g_hWnd, &vSrcPos, this->m_pBufferCom, this->m_pTransCom, &vDir))
	{
		cout << "À¸¾Ç" << endl;
		return true;
	}

	//m_pCollision->Hit_In_ViewPort(g_hWnd, this->m_pBufferCom, this->m_pTransCom);

	//FAILED_CHECK_RETURN(CPoolMgr::GetInstance()->Reuse_Obj(m_pGraphicDev, &vSrcPos, &vDir), );

	return false;
}

_vec3 CTestPlayer::Mouse_Peeking(void)
{
	_vec3		vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);

	CTerrainTex*	TerrainTex = dynamic_cast<CTerrainTex*>(Engine::Get_Component(L"Layer_Environment", L"Terrain", L"Proto_TerrainTexCom", ID_STATIC));
	NULL_CHECK_RETURN(TerrainTex, vPos);

	CTransform*		TerrainTransform = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Environment", L"Terrain", TRANSFORM_COMP, ID_DYNAMIC));
	NULL_CHECK_RETURN(TerrainTransform, vPos);

	/*if (m_pCalculatorCom->Peek_Target_Vector(g_hWnd, &_vec3(0, 0, 0), TerrainTex, TerrainTransform).x > 128 ||
		m_pCalculatorCom->Peek_Target_Vector(g_hWnd, &_vec3(0, 0, 0), TerrainTex, TerrainTransform).x < 0 ||
		m_pCalculatorCom->Peek_Target_Vector(g_hWnd, &_vec3(0, 0, 0), TerrainTex, TerrainTransform).z > 128 ||
		m_pCalculatorCom->Peek_Target_Vector(g_hWnd, &_vec3(0, 0, 0), TerrainTex, TerrainTransform).z < 0)
	{
		return _vec3(0, 0, 0);
	}*/
	return m_pCalculatorCom->Peek_Target_Vector(g_hWnd, &_vec3(0, 0, 0), TerrainTex, TerrainTransform);
}

CTestPlayer * CTestPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTestPlayer *	pInstance = new CTestPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CTestPlayer::Free(void)
{
	/*for (auto& iter : m_liszFinalName)
	{
		if(iter != nullptr)
			delete iter;
	}
	
	m_liszFinalName.clear();*/

	CGameObject::Free();
}
