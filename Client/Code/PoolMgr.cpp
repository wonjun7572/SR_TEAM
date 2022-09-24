#include "stdafx.h"

#include "PoolMgr.h"
#include "Export_Function.h"
#include "Bullet.h"

IMPLEMENT_SINGLETON(CPoolMgr)

CPoolMgr::CPoolMgr()
{
	/*CGameObject* pObj = nullptr;

	for (int i = 0; i < 99; ++i)
	{
	m_ObjectPool.push_back(pObj);
	}*/
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

	cout << "Collect : " << m_ObjectPool.size() << endl;
}

HRESULT CPoolMgr::Reuse_Obj(LPDIRECT3DDEVICE9& pGraphicDev, const _vec3* vPos, const _vec3* vDir)
{
	CGameObject* pObj = nullptr;

	if (m_ObjectPool.empty())
	{
		pObj = CBullet::Create(pGraphicDev, vPos, vDir);
		NULL_CHECK_RETURN(pObj, E_FAIL);

		Engine::Get_Layer(L"Layer_Bullet")->Add_GameList(pObj);

		cout << "EmptyPoolSize : " << m_ObjectPool.size() << endl;

		/*TCHAR* szFinalName = new TCHAR[128];
		wsprintf(szFinalName, L"");

		const _tchar*	szWallName = L"Bullet_%d";
		wsprintf(szFinalName, szWallName, m_iBulletCnt);

		Engine::Add_GameObject(L"Layer_Bullet", pObj, szFinalName);

		m_liBulletName.push_back(szFinalName);*/

		//cout << "EmptyName : " << m_liBulletName.size() << " PoolSize : " << m_ObjectPool.size() << endl;

		//++m_iCount;

		//cout << sizeof(szFinalName) << endl;
	}
	else
	{
		pObj = m_ObjectPool.front();

		NULL_CHECK_RETURN(pObj, E_FAIL);
		m_ObjectPool.pop_front();

		dynamic_cast<CBullet*>(pObj)->Set_Dir(*vDir);

		Engine::Get_Layer(L"Layer_Bullet")->Add_GameList(pObj);

		cout << " PoolSize : " << m_ObjectPool.size() << endl;

		/*TCHAR* szFinalName = new TCHAR[128];
		wsprintf(szFinalName, L"");

		const _tchar*	szWallName = L"Bullet_%d";
		wsprintf(szFinalName, szWallName, m_iBulletCnt);

		Engine::Add_GameObject(L"Layer_Bullet", pObj, szFinalName);

		m_liBulletName.push_back(szFinalName);

		cout << "PoolName : " << m_liBulletName.size() << " PoolSize : " << m_ObjectPool.size() << endl;*/
	}

	dynamic_cast<CBullet*>(pObj)->Set_Pos(*vPos);
	dynamic_cast<CBullet*>(pObj)->MoveToDir(*vDir);

	return S_OK;
}

//CGameObject* CPoolMgr::Reuse_Obj(LPDIRECT3DDEVICE9& pGraphicDev,const _vec3* vPos, const _vec3* vDir)
//{
//	CGameObject* pObj = nullptr;
//
//	if (m_ObjectPool.empty())
//	{
//		pObj = CBullet::Create(pGraphicDev, vPos, vDir);
//		NULL_CHECK_RETURN(pObj, nullptr);
//
//		TCHAR* szFinalName = new TCHAR[128];
//		wsprintf(szFinalName, L"");
//
//		const _tchar*	szWallName = L"Bullet_%d";
//		wsprintf(szFinalName, szWallName, m_iBulletCnt);
//
//		Engine::Add_GameObject(L"Layer_Bullet", pObj, szFinalName);
//
//		m_liBulletName.push_back(szFinalName);
//
//		cout << "EmptyName : " << m_liBulletName.size() << " PoolSize : " << m_ObjectPool.size() << endl;
//
//		++m_iCount;
//	}
//	else
//	{
//		pObj = m_ObjectPool.front();
//		//if (pObj == nullptr)
//		//{
//		//	cout << "Fuck" << m_ObjectPool.front() << endl;
//		//	return nullptr;
//		//}
//		////NULL_CHECK_RETURN(pObj, nullptr);
//		m_ObjectPool.pop_front();
//
//		Engine::Add_GameObject(L"Layer_Bullet", pObj, m_liBulletName.front());
//		m_liBulletName.push_back(m_liBulletName.front());
//		m_liBulletName.pop_front();
//
//		//cout << "PoolName : " << m_liBulletName.size() << " PoolSize : " << m_ObjectPool.size() << endl;
//	}
//
//	//cout << m_iCount << endl;
//
//	dynamic_cast<CBullet*>(pObj)->Set_Pos(*vPos);
//	dynamic_cast<CBullet*>(pObj)->MoveToDir(*vDir);
//
//	return pObj;
//}

void CPoolMgr::Free()
{
	/*for (auto iter : m_ObjectPool)
	{
	_ulong dwCnt = 0;

	dwCnt = iter->Release();

	if (dwCnt == 0)
	iter = nullptr;
	}*/

	for (auto& iter : m_ObjectPool)
	{
		Safe_Release<CGameObject*>(iter);
	}

	/*for (auto& iter : m_liBulletName)
	{
	if (iter != nullptr)
	Safe_Delete(iter);
	}*/

	m_ObjectPool.clear();
}