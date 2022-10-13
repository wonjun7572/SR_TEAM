#include "stdafx.h"

#include "PoolMgr.h"
#include "Export_Function.h"
#include "Bullet.h"
#include "SpBullet.h"

IMPLEMENT_SINGLETON(CPoolMgr)

CPoolMgr::CPoolMgr()
{
}

CPoolMgr::~CPoolMgr()
{
	Free();
}

void CPoolMgr::Collect_Obj(CGameObject * pObj)
{
	if (pObj == nullptr)
		return;

	m_ObjectPool.push_back(pObj);
}

void CPoolMgr::Collect_PlayerBullet(CGameObject * pObj)
{
	if (pObj == nullptr)
		return;

	m_PlayerBulletPool.push_back(pObj);
}

HRESULT CPoolMgr::Reuse_Obj(LPDIRECT3DDEVICE9& pGraphicDev, const _vec3* vPos, const _vec3* vDir, _float _fDamage)
{
	CGameObject* pObj = nullptr;

	if (m_ObjectPool.empty())
	{
		pObj = CBullet::Create(pGraphicDev, vPos, vDir, _fDamage);
		NULL_CHECK_RETURN(pObj, E_FAIL);

		Engine::Get_Layer(STAGE_BULLET)->Add_GameList(pObj);
	}
	else
	{
		pObj = m_ObjectPool.front();

		NULL_CHECK_RETURN(pObj, E_FAIL);
		m_ObjectPool.pop_front();

		dynamic_cast<CBullet*>(pObj)->Set_Dir(*vDir);

		Engine::Get_Layer(STAGE_BULLET)->Add_GameList(pObj);
	}

	dynamic_cast<CBullet*>(pObj)->Set_Pos(*vPos);
	dynamic_cast<CBullet*>(pObj)->MoveToDir(*vDir);

	return S_OK;
}

HRESULT CPoolMgr::Reuse_PlayerBullet(LPDIRECT3DDEVICE9 & pGraphicDev, const _vec3 * vPos, const _vec3 * vDir, _float _fDamage, _float _fSpeed)
{
	CGameObject* pObj = nullptr;

	if (m_PlayerBulletPool.empty())
	{
		pObj = CSpBullet::Create(pGraphicDev, vPos, vDir, _fDamage, _fSpeed);
		NULL_CHECK_RETURN(pObj, E_FAIL);

		Engine::Get_Layer(STAGE_BULLETPLAYER)->Add_GameList(pObj);
	}
	else
	{
		pObj = m_PlayerBulletPool.front();

		NULL_CHECK_RETURN(pObj, E_FAIL);
		m_PlayerBulletPool.pop_front();

		dynamic_cast<CSpBullet*>(pObj)->isAlive(true);
		dynamic_cast<CSpBullet*>(pObj)->Set_Dir(*vDir);

		Engine::Get_Layer(STAGE_BULLETPLAYER)->Add_GameList(pObj);
	}

	dynamic_cast<CSpBullet*>(pObj)->Set_Pos(*vPos);
	dynamic_cast<CSpBullet*>(pObj)->MoveToDir(*vDir);

	return S_OK;
}

void CPoolMgr::Free()
{
	for (auto& iter : m_ObjectPool)
	{
		Safe_Release<CGameObject*>(iter);
	}

	for (auto& iter : m_PlayerBulletPool)
	{
		Safe_Release<CGameObject*>(iter);
	}

	m_ObjectPool.clear();
}