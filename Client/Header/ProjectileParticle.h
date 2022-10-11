#pragma once
#include "PSystem.h"

class CItemParticle;

class CProjectileParticle : public CPSystem
{
protected:
	explicit CProjectileParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CProjectileParticle();

public:
	virtual		HRESULT		Ready_Object(void);
	virtual		_int		Update_Object(const _float& fTimeDelta);
	virtual		void		LateUpdate_Object(void);
	virtual		void		Render_Object(void);

public:
	HRESULT						Add_Component(void);
	static CProjectileParticle*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual		void			Free(void);

public:
	virtual		void		resetParticle(ATTRIBUTE* attribute);
private:
	void		Dead_Effect();
private:
	_float		Gravity = 0.f;
	CItemParticle* m_pItemParticle = nullptr;
};

