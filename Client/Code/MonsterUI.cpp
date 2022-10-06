#include "stdafx.h"
#include "..\Header\MonsterUI.h"
#include "TargetCube.h"

CMonsterUI::CMonsterUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CMonsterUI::~CMonsterUI()
{
}

HRESULT CMonsterUI::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransCom->Set_Scale(1.f, 0.1f, 0.f);

	return S_OK;
}

_int CMonsterUI::Update_Object(const _float & fTimeDelta)
{
	CTransform*		pMonster = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_MONSTER, L"TargetCube1", TRANSFORM_COMP, ID_DYNAMIC));
	_vec3 vMonster;
	pMonster->Get_Info(INFO_POS, &vMonster);
	m_pTransCom->Set_Pos(vMonster.x, vMonster.y + 0.5f, vMonster.z);
	m_pTransCom->Billboard_Transform(fTimeDelta);

	_int iResult = CGameObject::Update_Object(fTimeDelta);
	if (m_pMonster == nullptr)
		m_pMonster = Engine::Get_GameObject(STAGE_MONSTER, L"TargetCube1");

	if (m_pMonster != nullptr)
	{
		m_fHp = dynamic_cast<CTargetCube*>(Engine::Get_GameObject(STAGE_MONSTER, L"TargetCube1"))->Get_MAbility()->fCurrentHp;
		
		m_fMaxHp = dynamic_cast<CTargetCube*>(Engine::Get_GameObject(STAGE_MONSTER, L"TargetCube1"))->Get_MAbility()->fMaxHp;
		
		m_strHp = to_wstring(m_fHp);
	}

	Add_RenderGroup(RENDER_NONALPHA, this);
	
	return iResult;
}

void CMonsterUI::LateUpdate_Object(void)
{

	CGameObject::LateUpdate_Object();
}

void CMonsterUI::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Resize_Buffer(m_fHp / m_fMaxHp);
	m_pBufferCom->Render_Buffer();
}

CMonsterUI * CMonsterUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMonsterUI* pInstance = new CMonsterUI(pGraphicDev);
	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CMonsterUI::Free(void)
{
	CGameObject::Free();
}

HRESULT CMonsterUI::Add_Component()
{
	CComponent* pComponent = nullptr;
	
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(RCTEX_MONTER_HP_COMP));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ RCTEX_MONTER_HP_COMP, pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Monster_HP"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Monster_HP", pComponent });

	return S_OK;
}
