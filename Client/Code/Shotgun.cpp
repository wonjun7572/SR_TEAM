#include "stdafx.h"
#include "..\Header\Shotgun.h"


CShotgun::CShotgun(LPDIRECT3DDEVICE9 pGraphicDev)
	:CWeapon(pGraphicDev)
{
}


CShotgun::~CShotgun()
{
}

HRESULT CShotgun::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CShotgun::Update_Object(const _float & fTimeDelta)
{
	m_fTimeDelta = fTimeDelta;

	Assemble();

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);
	CGameObject::Update_Object(fTimeDelta);

	return 0;
}

void CShotgun::LateUpdate_Object(void)
{


	FAILED_CHECK_RETURN(Add_Parts(), );
	FAILED_CHECK_RETURN(Get_Parts(), );
	CGameObject::LateUpdate_Object();

	//Animation_Fire();
}

void CShotgun::Render_Object(void)
{
}

HRESULT CShotgun::Add_Component(void)
{
	CComponent* pComponent = nullptr;
	return S_OK;
}

HRESULT CShotgun::Add_Parts()
{
	if (!m_bPartInit)
	{
		CGameObject*m_pShotgunCreate1 = CShotgunPart1::Create(m_pGraphicDev);
		CGameObject*m_pShotgunCreate2 = CShotgunPart2::Create(m_pGraphicDev);
		CGameObject*m_pShotgunCreate3 = CShotgunPart3::Create(m_pGraphicDev);
		CGameObject*m_pShotgunCreate4 = CShotgunPart4::Create(m_pGraphicDev);


		TCHAR* szFinalName = new TCHAR[64];
		wsprintf(szFinalName, L"ShotgunPart1");
		Engine::Add_GameObject(L"Layer_GameLogic", m_pShotgunCreate1, szFinalName);
		m_liszFinalName.push_back(szFinalName);

		TCHAR* szFinalName2 = new TCHAR[64];
		wsprintf(szFinalName2, L"ShotgunPart2");
		Engine::Add_GameObject(L"Layer_GameLogic", m_pShotgunCreate2, szFinalName2);
		m_liszFinalName.push_back(szFinalName2);

		TCHAR* szFinalName3 = new TCHAR[64];
		wsprintf(szFinalName3, L"ShotgunPart3");
		Engine::Add_GameObject(L"Layer_GameLogic", m_pShotgunCreate3, szFinalName3);
		m_liszFinalName.push_back(szFinalName3);

		TCHAR* szFinalName4 = new TCHAR[64];
		wsprintf(szFinalName4, L"ShotgunPart4");
		Engine::Add_GameObject(L"Layer_GameLogic", m_pShotgunCreate4, szFinalName4);
		m_liszFinalName.push_back(szFinalName4);
		
		m_bPartInit = true;

	}
	return S_OK;
}

HRESULT CShotgun::Get_Parts(void)
{
	m_pPart1 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"ShotgunPart1", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pPart1, E_FAIL);
	m_pPart2 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"ShotgunPart2", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pPart2, E_FAIL);
	m_pPart3 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"ShotgunPart3", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pPart3, E_FAIL);
	m_pPart4 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"ShotgunPart4", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pPart4, E_FAIL);
	//m_pPart5 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"ShotgunPart5", L"Proto_TransformCom", ID_DYNAMIC));
	//NULL_CHECK_RETURN(m_pPart5, E_FAIL);
	return S_OK;
}


void CShotgun::Assemble(void)
{
	FAILED_CHECK_RETURN(Get_Parts(), );
	_vec3 vBodyPos;
	m_pPart4->Set_Pos(20.f, 2.f, 10.f);
	m_pPart4->Get_BeforeInfo(INFO_POS, &vBodyPos);

	m_pPart1->Set_Pos(vBodyPos.x - 1.8f*1.5f, vBodyPos.y + 0.4f*1.5f, vBodyPos.z);
	m_pPart2->Set_Pos(vBodyPos.x - 0.8f*1.5f, vBodyPos.y + 0.2f*1.5f, vBodyPos.z);
	m_pPart3->Set_Pos(vBodyPos.x - 0.6f*1.5f, vBodyPos.y + 0.075f*1.5f, vBodyPos.z);

	//
	//cout << vBodyPos.y << endl;
}

void CShotgun::Animation_Fire(void)
{
}


void CShotgun::Set_OnTerrain(void)
{
	/*m_pShotgunWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"ShotgunPart5", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pShotgunWorld, );

	_vec3		vPos;
	m_pShotgunWorld->Get_Info(INFO_POS, &vPos);

	Engine::CTerrainTex*	pTerrainTexCom = dynamic_cast<Engine::CTerrainTex*>(Engine::Get_Component(L"Layer_Environment", L"Terrain", L"Proto_TerrainTexCom", ID_STATIC));
	NULL_CHECK(pTerrainTexCom);

	_float fHeight = m_pCalculatorCom->HeightOnTerrain(&vPos, pTerrainTexCom->Get_VtxPos(), VTXCNTX, VTXCNTZ);

	m_pShotgunWorld->Set_Pos(vPos.x, fHeight, vPos.z);*/
}


CShotgun * CShotgun::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CShotgun* pInstance = new CShotgun(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CShotgun::Free(void)
{
	for (auto& iter : m_liszFinalName)
	{
		if (iter != nullptr)
			delete iter;
	}

	m_liszFinalName.clear();
	CGameObject::Free();
}

