#pragma once
#include "PSystem.h"
class CMonsterParticle :
	public CPSystem
{
public:
	CMonsterParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMonsterParticle();


public:
	virtual		HRESULT		Ready_Object(void);
	virtual		_int		Update_Object(const _float& fTimeDelta);
	virtual		void		LateUpdate_Object(void);
	virtual		void		Render_Object(void);

public:
	HRESULT						Add_Component(void);
	static CMonsterParticle*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual		void		Free(void);

public:
	virtual		void		resetParticle(ATTRIBUTE* attribute);

private:
	CCollision*			m_pCollision = nullptr;
};

