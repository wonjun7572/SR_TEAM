#include "stdafx.h"
#include "..\Header\TestPlayer.h"

#include "Export_Function.h"
#include "Wall.h"
#include "PoolMgr.h"

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
	Key_Input(fTimeDelta);
	Engine::CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_NONALPHA, this);
	return 0;
}

void CTestPlayer::LateUpdate_Object(void)
{
	/*Engine::CGameObject::LateUpdate_Object();*/
	Set_OnTerrain();
}

void CTestPlayer::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTextureCom->Set_Texture(0);	
	m_pBufferCom->Render_Buffer();
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

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

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

	if (Get_DIMouseState(DIM_LB))
	{
		Fire_Bullet(&m_vDirection);
		m_iBulletCnt++;
	}


	if (Get_DIKeyState(DIK_SPACE) & 0x80)
	{
		Create_Wall(m_iCnt, 0);
		m_iCnt++;
	}
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

	Engine::Add_GameObject(L"Layer_Wall", pWall, szFinalName);
	m_liszFinalName.push_back(szFinalName);
}

void CTestPlayer::Fire_Bullet(const _vec3* pDir)
{
	_vec3		vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);

	CGameObject*	pBullet = CPoolMgr::GetInstance()->Reuse_Obj(m_pGraphicDev, &vPos, pDir);

	TCHAR* szFinalName = new TCHAR[128];
	wsprintf(szFinalName, L"");

	const _tchar*	szWallName = L"Bullet_%d";
	wsprintf(szFinalName, szWallName, m_iBulletCnt);

	Engine::Add_GameObject(L"Layer_Bullet", pBullet, szFinalName);
	m_liBulletName.push_back(szFinalName);
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
	for (auto& iter : m_liszFinalName)
		delete iter;
	
	m_liszFinalName.clear();

	for (auto& iter : m_liBulletName)
		delete iter;

	m_liBulletName.clear();

	CGameObject::Free();
}
