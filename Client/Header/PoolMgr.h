#pragma once

#include "GameObject.h"

class CPoolMgr : public CComponent
{
	DECLARE_SINGLETON(CPoolMgr)

private:
	explicit CPoolMgr();
	virtual ~CPoolMgr();

public:
	void Collect_Obj(CGameObject* pObj);
	CGameObject* Reuse_Obj(LPDIRECT3DDEVICE9& pGraphicDev, const _vec3* vPos, const _vec3* vDir);

private:
	void Release();

private:
	list<CGameObject*>		m_ObjectPool;
	int						m_iCount = 0;

private:
	virtual CComponent* Clone() { return nullptr; }
	virtual	void Free();
};
