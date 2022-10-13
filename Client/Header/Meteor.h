#pragma once
#include "GameObject.h"
#include "RcEffect.h"
#include "SparkEffect.h"
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
	void					Meteor_Effect(void);


private:
	CTransform*				m_pTransCom;
	CSphereTex*				m_pSphereTex;
	CTexture*				m_pTexture;
	CGameObject*			m_pEffect = nullptr;
	CSparkEffect*			 m_SparkEffectParticle = nullptr;

	_vec3					m_vTarget;
	_vec3					m_vPos;
	_float					m_fTimer = 0.f;
	_float					m_fParticleTimer = 0.f;


public:
	static CMeteor*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& Position);
	virtual void	Free(void);
};

