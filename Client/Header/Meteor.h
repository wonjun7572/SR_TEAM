#pragma once
#include "GameObject.h"
class CMeteor :	public CGameObject
{
private:
	explicit CMeteor(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMeteor();

public:
	virtual		HRESULT		Ready_Object(const _vec3& Position);
	virtual		_int		Update_Object(const _float& fTimeDelta);
	virtual		void		LateUpdate_Object(void);
	virtual		void		Render_Object(void);

private:
	HRESULT					Add_Component(void);

private:
	CTransform*				m_pTransCom;
	CSphereTex*				m_pSphereTex;
	CTexture*				m_pTexture;

	_vec3					m_vTarget;

public:
	static CMeteor*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& Position);
	virtual void	Free(void);
};

