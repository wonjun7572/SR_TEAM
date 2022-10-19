#pragma once
#include "GameObject.h"
class CKrakenBullet :
	public CGameObject
{
public:
	CKrakenBullet(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CKrakenBullet();

public:
	virtual		HRESULT		Ready_Object(const _vec3& vPos, _tchar* Name);
	virtual		_int		Update_Object(const _float& fTimeDelta);
	virtual		void		LateUpdate_Object(void);
	virtual		void		Render_Object(void);

private:
	HRESULT					Add_Component(void);

	
protected:
	CTransform*			m_pKrakenBullet;
	CSphereTex*				m_pSphereTex = nullptr;
	CTexture*				m_pTexture = nullptr;
	
private:
	_tchar*					m_KrakenInk;
	_vec3					m_vDir;
	_vec3					m_vPos;
	

	_float					m_fSpeed;

	

private:
	HRESULT					Build(void);
public:
	static CKrakenBullet*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, _tchar* Name);
	virtual void	Free(void);
};
