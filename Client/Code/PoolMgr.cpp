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

	return pObj;
}

void CPoolMgr::Release()
{
}

void CPoolMgr::Free()
{
	for_each(m_ObjectPool.begin(), m_ObjectPool.end(), CDeleteObj());
	m_ObjectPool.clear();
	Release();
}