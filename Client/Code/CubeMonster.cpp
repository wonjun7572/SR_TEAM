#include "stdafx.h"
#include "..\Header\CubeMonster.h"
#include "Export_Function.h"
#include "Texture.h"


CCubeMonster::CCubeMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{

}

CCubeMonster::~CCubeMonster()
{
}

HRESULT CCubeMonster::Ready_Object(void)
{
	m_MonsterState = new MONSTERABILITY;
	m_fDetectRange = 30.f;
	m_fMinLenghtRange = 5.f;
	m_fAttackRange = 1.f;
	m_MonsterState->fCurrentHp = 100.f;
	m_MonsterState->fMaxHp = 100.f;
	m_MonsterState->fCurrentHp = m_MonsterState->fMaxHp;
	m_MonsterState->iLevel = 1;
	m_MonsterState->fDamage = 1.f;
	m_eCurrentState = CurrentState::MONSTER_IDLE;
	m_ePreviousState = m_eCurrentState;
	m_fSpeed = 1.f;
	m_fTimeDelta = 0.1f;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	//m_pMTransform->m_vInfo[Engine::INFO_POS] = m_vPos;
	return S_OK;
}

_int CCubeMonster::Update_Object(const _float & fTimeDelta)
{
	FAILED_CHECK_RETURN(Get_BodyTransform(), -1);

	CurrentMonster(fTimeDelta);

	Monster_Mapping();
	Axis();
	CGameObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);
	return 0;
}

void CCubeMonster::LateUpdate_Object(void)
{
	CTransform*		pPlayerTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_CHARACTER, L"BODY", TRANSFORM_COMP, ID_DYNAMIC));
	CGameObject::LateUpdate_Object();

	Assemble();
}

void CCubeMonster::Render_Object(void)
{


}

//���� ���ͻ��� 
_int CCubeMonster::CurrentMonster(_float fTimeDelta)
{
	CTransform*		pPlayerTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_CHARACTER, L"BODY", TRANSFORM_COMP, ID_DYNAMIC));
	NULL_CHECK_RETURN(pPlayerTransformCom, 0);
	
	//��
	m_pMbody = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_Body", TRANSFORM_COMP, ID_STATIC));
	NULL_CHECK_RETURN(m_pMbody, 0);
	m_pMbody->Get_Info(INFO_POS, &m_vPos);

	//����
	m_pMleftArm = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_LeftArm", TRANSFORM_COMP, ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pMleftArm, 0);
	//������
	m_pMrightArm = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_RighrArm", TRANSFORM_COMP, ID_DYNAMIC));
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

	//Ž��
	if (m_fLengthRange >= m_fMinLenghtRange && m_fLengthRange <= m_fDetectRange)
	{
		Axis();

		m_pMbody->Chase_Target(&vPlayerPos, m_fSpeed, m_fTimeDelta);
	}
	else
	{
		CurrentState::MONSTER_IDLE;
		ComeBack(fTimeDelta);
		return 0;
	}

	return 0;
}

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
	pInsatnce = m_pMTransform = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pMTransform, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, 	pInsatnce });

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
	m_pMleftArm->Get_BeforeInfo(INFO_LOOK, &vPlayerPos);
}

HRESULT CCubeMonster::Get_BodyTransform(void)
{
	//����
	m_pMleftArm = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_LeftArm", TRANSFORM_COMP, ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pMleftArm, E_FAIL);
	
	//������
	m_pMrightArm = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_RighrArm", TRANSFORM_COMP, ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pMrightArm, E_FAIL);
	
	//��
	m_pMbody = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_Body", TRANSFORM_COMP, ID_STATIC));
	NULL_CHECK_RETURN(m_pMbody, E_FAIL);

	//�Ӹ�
	m_pMhead = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_Head", TRANSFORM_COMP, ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pMhead, E_FAIL);

	return S_OK;
}

HRESULT CCubeMonster::Monster_Mapping(void)
{
	_vec3		vPos;
	m_pMbody->Get_Info(INFO_POS, &vPos);
	if (!m_MappingInit)
	{
		CGameObject*	m_pMapMonster = CMonsterMapping::Create(m_pGraphicDev);
		TCHAR* szCntName = new TCHAR[64];
		wsprintf(szCntName, L"");
		const _tchar*	szNumbering = L"MapMonster_%d";
		wsprintf(szCntName, szNumbering, m_iCnt);
		Engine::Add_GameObject(STAGE_MAPPING, m_pMapMonster, szCntName);
		m_listMonsterCnt.push_back(szCntName);

		m_pMonsterMapping = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_MAPPING, szCntName, TRANSFORM_COMP, ID_DYNAMIC));
		NULL_CHECK_RETURN(m_pMonsterMapping, E_FAIL);
		++m_iCnt;
		m_MappingInit = true;
	}

	m_pMonsterMapping->Set_Pos(vPos.x, vPos.y, vPos.z);

	return S_OK;
}

_int CCubeMonster::Attack(_float fTimeDelta)
{
	return 0;
}

_int CCubeMonster::ComeBack(_float fTimeDelta)
{
	ChangeCurrent(CurrentState::MONSTER_COMEBACK);
	return 0;
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
	for (auto& iter : m_listMonsterCnt)
	{
	if(iter != nullptr)
	delete iter;
	}

	m_listMonsterCnt.clear();

	Safe_Delete<MONSTERABILITY*>(m_MonsterState);

	CGameObject::Free();
}
