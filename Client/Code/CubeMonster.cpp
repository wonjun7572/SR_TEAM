#include "stdafx.h"
#include "..\Header\CubeMonster.h"
#include "Export_Function.h"
#include "Texture.h"
CCubeMonster::CCubeMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
	m_fDetectRange = 50.f;
	m_fMinLenghtRange = 5.f;
	m_fAttackRange = 1.f;
	m_MonsterState.fCurrentHp = 100.f;
	m_MonsterState.fMaxHp = 100.f;
	m_MonsterState.fCurrentHp = m_MonsterState.fMaxHp;
	m_MonsterState.iLevel = 1;
	m_MonsterState.fDamage = 1.f;
	m_eCurrentState = CurrentState::MONSTER_IDLE;
	m_ePreviousState = m_eCurrentState;
	m_fSpeed = 1.f;
	m_fTimeDelta = 0.1f;
}


CCubeMonster::~CCubeMonster()
{
}

HRESULT CCubeMonster::Ready_Object(void)
{

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	//m_pMTransform->m_vInfo[Engine::INFO_POS] = m_vPos;
	return S_OK;
}

_int CCubeMonster::Update_Object(const _float & fTimeDelta)
{

	FAILED_CHECK_RETURN(Get_BodyTransform(), -1);

	CurrentMonster(fTimeDelta);


	Axis();
	CGameObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);
	return 0;
}

void CCubeMonster::LateUpdate_Object(void)
{
	CTransform*		pPlayerTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"BODY", L"Proto_TransformCom", ID_DYNAMIC));
	//NULL_CHECK(pPlayerTransformCom);


	//_vec3		vPlayerPos;
	//pPlayerTransformCom->Get_Info(INFO_POS, &vPlayerPos);

	//m_pMTransform->Chase_Target(&vPlayerPos, 1.f, 0.1f);
	CGameObject::LateUpdate_Object();

	Assemble();

	//Set_OnTerrain();

}

void CCubeMonster::Render_Object(void)
{
//	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pMTransform->Get_WorldMatrixPointer());

}

//ÇöÀç ¸ó½ºÅÍ»óÅÂ 
_int CCubeMonster::CurrentMonster(_float fTimeDelta)
{
	CTransform*		pPlayerTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"BODY", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(pPlayerTransformCom, 0);
	
	//¸ö
	m_pMbody = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_Body", L"Proto_TransformCom", ID_STATIC));
	NULL_CHECK_RETURN(m_pMbody, 0);
	m_pMbody->Get_Info(INFO_POS, &m_vPos);

	//¿ÞÆÈ
	m_pMleftArm = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_LeftArm", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pMleftArm, 0);
	//¿À¸¥ÆÈ
	m_pMrightArm = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_RighrArm", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pMrightArm, 0);

	pPlayerTransformCom->Get_Info(Engine::INFO_POS, &vPlayerPos);
	m_pMbody->Set_Info(INFO_LOOK, &vPlayerPos);
	m_pMleftArm->Set_Info(INFO_LOOK, &vPlayerPos);
	m_pMrightArm->Set_Info(INFO_LOOK, &vPlayerPos);

	m_pMrightArm->Compute_LookAtTarget(&vPlayerPos);
	_matrix matWorld;
	m_pMTransform->Get_WorldMatrix(&matWorld);
	m_vDir = vPlayerPos - m_vPos;
	m_fLengthRange = D3DXVec3Length(&m_vDir);
	D3DXVec3Normalize(&m_vDir, &m_vDir);

	_vec3		vRight;
	memcpy(&vRight, &pPlayerTransformCom->m_matWorld.m[0][0], sizeof(_vec3));


	_matrix		matRot;
	D3DXMatrixRotationAxis(&matRot, &vRight, m_fAngle);
	//Å½Áö
	if (m_fLengthRange >= m_fMinLenghtRange && m_fLengthRange <= m_fDetectRange)
	{
		Axis();

		m_pMbody->Chase_Target(&vPlayerPos, m_fSpeed, m_fTimeDelta);
		m_pMhead->Chase_Target(&vPlayerPos, m_fSpeed, m_fTimeDelta);
		m_pMleftArm->Chase_Target(&vPlayerPos, m_fSpeed, m_fTimeDelta);
		m_pMrightArm->Chase_Target(&vPlayerPos, m_fSpeed, m_fTimeDelta);

	}
	else
	{
		CurrentState::MONSTER_IDLE;
		ComeBack(fTimeDelta);
		return 0;
	}

	return 0;

	
}


//»óÈ²ÀÌ ¹Ù²î´Â°ÍÀ» ÀÎÁö½ÃÄÑÁà¾ßÇÏÁö¾ÊÀ»±î
void CCubeMonster::ChangeCurrent(CurrentState::MONSTERID Idstate)
{
	m_eCurrentState = Idstate;
	if (m_ePreviousState != m_eCurrentState)
	{
		m_ePreviousState = m_eCurrentState;
	}

	
}



HRESULT CCubeMonster::Add_Component(void)
{
	CComponent* pInsatnce = nullptr;
	pInsatnce = m_pMTransform = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pMTransform, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", 	pInsatnce });



	return 0;
}





void CCubeMonster::Set_OnTerrain(void)
{
	
}




void CCubeMonster::Assemble(void)
{
	FAILED_CHECK_RETURN(Get_BodyTransform(), );
	m_pMbody->Get_Info(INFO_POS, &BodyPos);
	m_pMhead->Set_Pos(BodyPos.x, BodyPos.y + 3.f, BodyPos.z);
	m_pMleftArm->Set_Pos(BodyPos.x - 1.f, BodyPos.y + 0.65f, BodyPos.z + 1.f);
	m_pMrightArm->Set_Pos(BodyPos.x + 1.f, BodyPos.y + 0.65f, BodyPos.z + 1.f);
}

void CCubeMonster::Axis(void)
{
	
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
	m_pMbody = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_Body", L"Proto_TransformCom", ID_STATIC));
	NULL_CHECK_RETURN(m_pMbody, E_FAIL);

	//¸Ó¸®
	m_pMhead = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_Head", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pMhead, E_FAIL);

	return S_OK;
}



_int CCubeMonster::Attack(_float fTimeDelta)
{
	return 0;
}

_int CCubeMonster::ComeBack(_float fTimeDelta)
{
	ChangeCurrent(CurrentState::MONSTER_COMEBACK);


	return NO_EVENT;
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
