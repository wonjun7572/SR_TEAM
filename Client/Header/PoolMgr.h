#pragma once

#include "GameObject.h"

class CPoolMgr// : public CComponent
{
	DECLARE_SINGLETON(CPoolMgr)

private:
	explicit CPoolMgr();
	virtual ~CPoolMgr();

public:
	void Collect_Obj(CGameObject* pObj);
	HRESULT Reuse_Obj(LPDIRECT3DDEVICE9& pGraphicDev, const _vec3* vPos, const _vec3* vDir);
	//HRESULT Retry_Obj(LPDIRECT3DDEVICE9& pGraphicDev, const _vec3* vPos, const _vec3* vDir, const _float fSpeed, const _float fScale, const _float fDamage, const _float fInterval);
private:
	list<CGameObject*>		m_ObjectPool;
	int						m_iCount = 0;

private:
	list<TCHAR*>		m_liBulletName;
	_uint				m_iCnt = 0;
	_uint				m_iBulletCnt = 0;

public:
	virtual	void Free();

private:
	virtual CComponent* Clone() { return nullptr; }
};
