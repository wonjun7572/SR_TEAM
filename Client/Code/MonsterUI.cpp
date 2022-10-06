#include "stdafx.h"
#include "..\Header\MonsterUI.h"
#include "CubeMonster.h"

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

	m_pTransCom->Set_Scale(1.3f, 0.1f, 0.f);
	return S_OK;
}

_int CMonsterUI::Update_Object(const _float & fTimeDelta)
{

	CTransform*		pMonster = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Monster", L"M_Head", TRANSFORM_COMP, ID_DYNAMIC));
	_vec3 vMonster;
	pMonster->Get_Info(INFO_POS, &vMonster);
	
	m_pTransCom->Set_Pos(vMonster.x, vMonster.y + 2.f, vMonster.z);
	m_pTransCom->Billboard_Transform(0.1f);


	_int iResult = CGameObject::Update_Object(fTimeDelta);
	if (m_pMonster == nullptr)
		m_pMonster = Engine::Get_GameObject(L"Layer_Monster", L"CubeMonster");

	if (m_pMonster != nullptr)
	{
	m_iHp = dynamic_cast<CCubeMonster*>(Engine::Get_GameObject(L"Layer_Monster", L"CubeMonster"))->Get_MAbility()->fCurrentHp;
		m_strHp = to_wstring(m_iHp);
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
	m_pBufferCom->Resize_Buffer(m_iHp * 0.01f);
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
	
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"RcTex_MonsterHp", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Monster_HP"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Monster_HP", pComponent });

	return S_OK;
}
