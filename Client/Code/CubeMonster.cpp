#include "stdafx.h"
#include "..\Header\CubeMonster.h"
#include "Export_Function.h"

CCubeMonster::CCubeMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}


CCubeMonster::~CCubeMonster()
{
}

HRESULT CCubeMonster::Ready_Object(void)
{

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CCubeMonster::Update_Object(const _float & fTimeDelta)
{

	FAILED_CHECK_RETURN(Get_BodyTransform(), -1);


	CGameObject::Update_Object(fTimeDelta);


	Engine::Add_RenderGroup(RENDER_NONALPHA, this);
	return 0;
}

void CCubeMonster::LateUpdate_Object(void)
{
	//CTransform*		pPlayerTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"TestPlayer", L"Proto_TransformCom", ID_DYNAMIC));
	//NULL_CHECK(pPlayerTransformCom);
	//

	//_vec3		vPlayerPos;
	//pPlayerTransformCom->Get_Info(INFO_POS, &vPlayerPos);

	//m_pTransform->Chase_Target(&vPlayerPos, 10.f, 0.1f);
	CGameObject::LateUpdate_Object();

	Assemble();
	//Set_OnTerrain();

}

void CCubeMonster::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

}

HRESULT CCubeMonster::Add_Component(void)
{
	CComponent* pInsatnce = nullptr;
	pInsatnce = m_pTransform = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransform, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", 	pInsatnce });



	return S_OK;
}

void CCubeMonster::Set_OnTerrain(void)
{

	/*m_pMbody = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_Body", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pMbody, );

	_vec3		vPos;
	m_pMbody->Get_Info(INFO_POS, &vPos);

	Engine::CTerrainTex*	pTerrainTexCom = dynamic_cast<Engine::CTerrainTex*>(Engine::Get_Component(L"Layer_Environment", L"Terrain", L"Proto_TerrainTexCom", ID_STATIC));
	NULL_CHECK(pTerrainTexCom);

	_float fHeight = m_pCalculator->HeightOnTerrain(&vPos, pTerrainTexCom->Get_VtxPos(), VTXCNTX, VTXCNTZ);

	m_pMbody->Set_Pos(vPos.x, fHeight, vPos.z);*/
}

void CCubeMonster::Assemble(void)
{
	FAILED_CHECK_RETURN(Get_BodyTransform(), );

	_vec3 BodyPos;
	m_pMbody->Get_BeforeInfo(INFO_POS, &BodyPos);
	m_pMhead->Set_Pos(BodyPos.x, BodyPos.y + 3.f, BodyPos.z);
	m_pMleftArm->Set_Pos(BodyPos.x - 1.f, BodyPos.y + 0.65f, BodyPos.z + 1.f);
	m_pMrightArm->Set_Pos(BodyPos.x + 1.f, BodyPos.y + 0.65f, BodyPos.z + 1.f);

}

HRESULT CCubeMonster::Get_BodyTransform(void)
{
	//¿ÞÆÈ
	m_pMleftArm = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_LeftArm", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pMleftArm, E_FAIL);
	//¿À¸¥ÆÈ
	m_pMrightArm = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_RighrArm", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pMrightArm, E_FAIL);
	//¸ö
	m_pMbody = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_Body", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pMbody, E_FAIL);

	//¸Ó¸®
	m_pMhead = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_Head", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pMhead, E_FAIL);




	return S_OK;
}



CCubeMonster * CCubeMonster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{

	CCubeMonster* pInstance = new CCubeMonster(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CCubeMonster::Free(void)
{
	CGameObject::Free();
}
