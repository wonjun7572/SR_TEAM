#pragma once
#include "Monster.h"
class CAlien :
	public CMonster
{
public:
	explicit CAlien(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CAlien();

public:
	virtual		HRESULT		Ready_Object(const _vec3& vPos, _tchar* Name);
	virtual		_int		Update_Object(const _float& fTimeDelta);
	virtual		void		LateUpdate_Object(void);
	virtual		void		Render_Object(void);

private:
	HRESULT				Add_Component(void);
	HRESULT				Create_Item(void);
	_float				m_fTimeDelta = 0.f;
	_float				m_fFrame = 0.f;
private:
	ALIENSTATEID	m_STATE;
	ALIENSTATEID	m_BeforeState;
	ALIENWALKID		m_WALK;
	ALIENIDLEID     m_IDLE;
	ALIENATTACKID   m_ATTACK;
	ALIENSHOTTINGID m_SHOT;
	_tchar*			m_MonsterName;


public:
	static CAlien*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, _tchar* Name);
	virtual void	Free(void);


};

