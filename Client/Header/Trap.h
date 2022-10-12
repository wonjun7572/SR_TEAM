#pragma once
#include "GameObject.h"

class CTrap : public CGameObject
{
protected:
	explicit CTrap(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTrap();

protected:
	virtual HRESULT		Ready_Object(const _vec3& vPos, _tchar* Name);
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object(void) override;
	virtual void		Render_Object(void) override;

protected:
	CCollision*			m_pCollision = nullptr;
	CHitBox*			m_pHitBox = nullptr;
	CTransform*			m_pTransCom = nullptr;

protected:
	list<_tchar*>		m_TcharList;

protected:
	virtual void		Free(void)override;
};

