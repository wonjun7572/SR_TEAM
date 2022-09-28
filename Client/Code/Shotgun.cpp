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
	FAILED_CHECK_RETURN(Get_Parts(), );
	CGameObject::LateUpdate_Object();
}

void CShotgun::Render_Object(void)
{
}

HRESULT CShotgun::Add_Component(void)
{
	CComponent* pComponent = nullptr;
	return S_OK;
}

HRESULT CShotgun::Get_Parts(void)
{
	m_pPart1 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Gun", L"Shotgun_Part_1", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pPart1, E_FAIL);
	m_pPart2 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Gun", L"Shotgun_Part_2", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pPart2, E_FAIL);
	m_pPart3 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Gun", L"Shotgun_Part_3", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pPart3, E_FAIL);
	m_pPart4 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Gun", L"Shotgun_Part_4", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pPart4, E_FAIL);
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
	CWeapon::Free();
}

