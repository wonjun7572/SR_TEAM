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

CGameObject* CPoolMgr::Reuse_Obj(LPDIRECT3DDEVICE9& pGraphicDev,const _vec3* vPos, const _vec3* vDir)
{
	CGameObject* pObj = nullptr;

	if (m_ObjectPool.empty())
	{
		pObj = CBullet::Create(pGraphicDev, vPos, vDir);
		NULL_CHECK_RETURN(pObj, nullptr);
		++m_iCount;
	}
	else
	{
		pObj = m_ObjectPool.front();
		m_ObjectPool.pop_front();
	}

	dynamic_cast<CBullet*>(pObj)->Set_Pos(*vPos);
	dynamic_cast<CBullet*>(pObj)->MoveToDir(*vDir);

	return pObj;
}

void CPoolMgr::Free()
{
	/*for (auto iter : m_ObjectPool)
	{
		_ulong dwCnt = 0;

		dwCnt = iter->Release();

		if (dwCnt == 0)
			iter = nullptr;
	}*/
	//for (auto iter : m_ObjectPool)
	//{
	//	Safe_Release<CGameObject*>(iter);
	//}

	m_ObjectPool.clear();
}