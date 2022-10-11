#include "stdafx.h"
#include "..\Header\Illusioner.h"


CIllusioner::CIllusioner(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
}


CIllusioner::~CIllusioner()
{
}

HRESULT CIllusioner::Ready_Object(const _vec3 & vPos, _tchar * Name)
{
	m_tAbility = new MONSTERABILITY;
	m_tAbility->iLevel = 0;
	m_tAbility->fMaxHp = 100.f;
	m_tAbility->fCurrentHp = m_tAbility->fMaxHp;
	m_tAbility->fDamage = 1.f;
	m_tAbility->strObjTag = L"Illusioner";
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

_int CIllusioner::Update_Object(const _float & fTimeDelta)
{
	return _int();
}

void CIllusioner::LateUpdate_Object(void)
{
}

void CIllusioner::Render_Object(void)
{
}

HRESULT CIllusioner::Add_Component(void)
{
	return S_OK;
}

HRESULT CIllusioner::Create_Item()
{
	return S_OK;
}

CIllusioner * CIllusioner::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos, _tchar * Name)
{

	CIllusioner* pInstance = new CIllusioner(pGraphicDev, vPos, Name);
	if (FAILED(pInstance->Ready_Object(vPos, Name)))
	{
		Safe_Release(pInstance);
		return nullptr;

	}
	return pInstance;
}

void CIllusioner::Free(void)
{
	CMonster::Free();
}
