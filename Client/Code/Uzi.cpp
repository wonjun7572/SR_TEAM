#include "stdafx.h"
#include "..\Header\Uzi.h"


CUzi::CUzi(LPDIRECT3DDEVICE9 pGraphicDev)
	:CWeapon(pGraphicDev)
{
}


CUzi::~CUzi()
{
}

HRESULT CUzi::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

_int CUzi::Update_Object(const _float & fTimeDelta)
{
	m_fTimeDelta = fTimeDelta;

	Assemble();

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);
	CGameObject::Update_Object(fTimeDelta);

	return 0;	
}

void CUzi::LateUpdate_Object(void)
{	
	FAILED_CHECK_RETURN(Add_Parts(), );
	FAILED_CHECK_RETURN(Get_Parts(), );
	CGameObject::LateUpdate_Object();


	//Animation_Fire();
}

void CUzi::Render_Object(void)
{	
}

HRESULT CUzi::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	return S_OK;
}

HRESULT CUzi::Add_Parts()
{			
	if (!m_bPartInit)
	{
		CGameObject*	m_pUziCreate1 = CUziPart1::Create(m_pGraphicDev);
		CGameObject*	m_pUziCreate2 = CUziPart2::Create(m_pGraphicDev);
		CGameObject*	m_pUziCreate3 = CUziPart3::Create(m_pGraphicDev);
		CGameObject*	m_pUziCreate4 = CUziPart4::Create(m_pGraphicDev);
		CGameObject*	m_pUziCreate5 = CUziPart5::Create(m_pGraphicDev);

		TCHAR* szFinalName = new TCHAR[64];
		wsprintf(szFinalName, L"UziPart1");
		Engine::Add_GameObject(L"Layer_GameLogic", m_pUziCreate1, szFinalName);
		m_liszFinalName.push_back(szFinalName);

		TCHAR* szFinalName2 = new TCHAR[64];
		wsprintf(szFinalName2, L"UziPart2");
		Engine::Add_GameObject(L"Layer_GameLogic", m_pUziCreate2, szFinalName2);
		m_liszFinalName.push_back(szFinalName2);

		TCHAR* szFinalName3 = new TCHAR[64];
		wsprintf(szFinalName3, L"UziPart3");
		Engine::Add_GameObject(L"Layer_GameLogic", m_pUziCreate3, szFinalName3);
		m_liszFinalName.push_back(szFinalName3);

		TCHAR* szFinalName4 = new TCHAR[64];
		wsprintf(szFinalName4, L"UziPart4");
		Engine::Add_GameObject(L"Layer_GameLogic", m_pUziCreate4, szFinalName4);
		m_liszFinalName.push_back(szFinalName4);

		TCHAR* szFinalName5 = new TCHAR[64];
		wsprintf(szFinalName5, L"UziPart5");
		Engine::Add_GameObject(L"Layer_GameLogic", m_pUziCreate5, szFinalName5);
		m_liszFinalName.push_back(szFinalName5);
		m_bPartInit = true;
	}
	return S_OK;
}

HRESULT CUzi::Get_Parts(void)
{
	m_pPart1 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"UziPart1", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pPart1, E_FAIL);
	m_pPart2 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"UziPart2", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pPart2, E_FAIL);
	m_pPart3 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"UziPart3", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pPart3, E_FAIL);
	m_pPart4 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"UziPart4", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pPart4, E_FAIL);
	m_pPart5 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"UziPart5", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pPart5, E_FAIL);
	return S_OK;
}


void CUzi::Assemble(void)
{
	FAILED_CHECK_RETURN(Get_Parts(),  );

	_vec3 vBodyPos;
	
	// »çÀÌÁî
	m_pPart5->Set_Pos(10.f, 2.f, 10.f);
	m_pPart5->Get_BeforeInfo(INFO_POS, &vBodyPos);

	m_pPart1->Set_Pos(vBodyPos.x -1.6f, vBodyPos.y +.6f, vBodyPos.z);
	m_pPart2->Set_Pos(vBodyPos.x -.2f, vBodyPos.y +.6f, vBodyPos.z);
	m_pPart3->Set_Pos(vBodyPos.x -.6f, vBodyPos.y + .2f, vBodyPos.z);
	m_pPart4->Set_Pos(vBodyPos.x -.1f, vBodyPos.y + .4f, vBodyPos.z);
	//cout << vBodyPos.y << endl;
}

void CUzi::Animation_Fire(void)
{
}


void CUzi::Set_OnTerrain(void)
{
	/*m_pUziWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"UziPart5", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pUziWorld, );

	_vec3		vPos;
	m_pUziWorld->Get_Info(INFO_POS, &vPos);

	Engine::CTerrainTex*	pTerrainTexCom = dynamic_cast<Engine::CTerrainTex*>(Engine::Get_Component(L"Layer_Environment", L"Terrain", L"Proto_TerrainTexCom", ID_STATIC));
	NULL_CHECK(pTerrainTexCom);

	_float fHeight = m_pCalculatorCom->HeightOnTerrain(&vPos, pTerrainTexCom->Get_VtxPos(), VTXCNTX, VTXCNTZ);

	m_pUziWorld->Set_Pos(vPos.x, fHeight, vPos.z);*/
}


CUzi * CUzi::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CUzi* pInstance = new CUzi(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;	
}

void CUzi::Free(void)
{
	for (auto& iter : m_liszFinalName)
	{
		if (iter != nullptr)
			delete iter;
	}

	m_liszFinalName.clear();
	CGameObject::Free();
}

