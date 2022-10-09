#include "stdafx.h"

#include "PoolMgr.h"
#include "Export_Function.h"
#include "Bullet.h"

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

HRESULT CPoolMgr::Reuse_Obj(LPDIRECT3DDEVICE9& pGraphicDev, const _vec3* vPos, const _vec3* vDir)
{
	CGameObject* pObj = nullptr;

	if (m_ObjectPool.empty())
	{
		pObj = CBullet::Create(pGraphicDev, vPos, vDir);
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

void CPoolMgr::Free()
{
	for (auto& iter : m_ObjectPool)
	{
		Safe_Release<CGameObject*>(iter);
	}

	m_ObjectPool.clear();
}