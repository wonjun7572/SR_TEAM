#pragma once
#include "GameObject.h"
class CFlightBomb :
	public CGameObject
{
public:
	explicit CFlightBomb(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CFlightBomb();

public:
	virtual		HRESULT		Ready_Object(const _vec3& vPos);
	virtual		_int		Update_Object(const _float& fTimeDelta);
	virtual		void		LateUpdate_Object(void);
	virtual		void		Render_Object(void);



private:
	HRESULT					Add_Component(void);
	void					Bombing(void);

private:
	CTransform*				m_pTransCom = nullptr;
	CSphereTex*				m_pSphereTex = nullptr;
	CTexture*				m_pTexture = nullptr;

private:	
	_vec3					m_vPosition;
	_vec3					m_vDirection;
	_float					m_fAttacking = 0.f;
public:
	static CFlightBomb*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
	virtual void	Free(void);
};

