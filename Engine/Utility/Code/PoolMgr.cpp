#include "..\..\Header\PoolMgr.h"
#include "Export_Utility.h"
#include "..\..\Client\Header\Wall.h"

USING(Engine)
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

CGameObject* CPoolMgr::Reuse_Obj(const _vec3 & vPos, const _vec3 & vDir)
{
	CGameObject* pObj = nullptr;

	if (m_ObjectPool.empty())
	{
		//pObj = CWall::Create(m_pGraphicDev,0,&(_vec3(0.f, 0.f, 0.f)));
		Engine::Add_GameObject(L"Layer_Wall", pObj, L"Wall");
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