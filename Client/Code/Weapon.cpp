#include "stdafx.h"
#include "..\Header\Weapon.h"
#include "Uzi.h"
#include "Shotgun.h"
#include "Sniper.h"


CWeapon::CWeapon(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}


CWeapon::~CWeapon()
{
	Free();
}

HRESULT CWeapon::Ready_Object(void)
{
	m_fUziSize = 2.f;
	return S_OK;
}

_int CWeapon::Update_Object(const _float & fTimeDelta)
{
	return _int();
}

void CWeapon::LateUpdate_Object(void)
{
}

void CWeapon::Render_Object(void)
{
}

HRESULT CWeapon::Ready_Weapon(LPDIRECT3DDEVICE9 pGraphicDev, const _uint & iIndex)
{
	switch (iIndex)
	{
	case 1:
		CUzi*	pInstance = CUzi::Create(pGraphicDev);
		NULL_CHECK_RETURN(pInstance, E_FAIL );
		m_WeaponList.push_back(pInstance);
		break;
	}	

	return S_OK;
}

void CWeapon::Free(void)
{
	for_each(m_WeaponList.begin(), m_WeaponList.end(), CDeleteObj());
	m_WeaponList.clear();
}