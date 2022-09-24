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
		TCHAR* szFinalName = new TCHAR[128];
		wsprintf(szFinalName, L"");

		const _tchar*	szWallName = L"Bullet_%d";
		wsprintf(szFinalName, szWallName, m_iBulletCnt);
		m_iBulletCnt++;

		Engine::Add_GameObject(L"Layer_Bullet", pObj, szFinalName);
		m_liBulletName.push_back(szFinalName);
		cout << m_ObjectPool.size() << endl;
	}
	else
	{
		pObj = m_ObjectPool.front();
		m_ObjectPool.pop_front();
		cout << "ReUse" << m_ObjectPool.size() << endl;
	}

	if (dynamic_cast<CBullet*>(pObj)->Get_Pos().x >= 50.f || dynamic_cast<CBullet*>(pObj)->Get_Pos().y >= 50.f || dynamic_cast<CBullet*>(pObj)->Get_Pos().z >= 50.f
		|| dynamic_cast<CBullet*>(pObj)->Get_Pos().x <= -50.f || dynamic_cast<CBullet*>(pObj)->Get_Pos().y <= -50.f || dynamic_cast<CBullet*>(pObj)->Get_Pos().z <= -50.f)
	{
		dynamic_cast<CBullet*>(pObj)->Set_Pos(*vPos);
	}
	dynamic_cast<CBullet*>(pObj)->MoveToDir(*vDir);

	return pObj;
}

void CPoolMgr::Free()
{
	for (auto& iter : m_liBulletName)
	{
		if (iter != nullptr)
			delete iter;
	}

	m_liBulletName.clear();
	m_ObjectPool.clear();
}