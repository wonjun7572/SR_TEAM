#pragma once
#include "Monster.h"

BEGIN(Engine)

class CHitBox;
class CTransform;
class CCalculator;
class CCollision;
class CCubeCol;

END

class CIllusioner :	public CMonster
{
public:
	CIllusioner(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CIllusioner();

public:
	virtual		HRESULT		Ready_Object(const _vec3& vPos, _tchar* Name);
	virtual		_int		Update_Object(const _float& fTimeDelta);
	virtual		void		LateUpdate_Object(void);
	virtual		void		Render_Object(void);

private:
	HRESULT				Add_Component(void);
	HRESULT				Create_Item();

	CCubeCol*			m_pAnimationBox = nullptr;
	_float					m_fFrame = 0.f;
	_float					m_fTimeDelta = 0.f;
	_bool					m_bFirst = true;
	_float					m_AnimationTime = 0.f;
private:
	HRESULT					Build(void);
	void					Load_Animation(wstring FileName);
	void					Run_Animation(const _float& AnimationSpeed);
	void					Look_Direction(void);

	void					Walk_Animation_Run(void);
	void					Idle_Animation_Run(void);
	void					Attack_Animation_Run(void);

	_tchar*					m_MonsterName;

	ILLUSIONSTATEID			m_BeforeState;
	ILLUSIONSTATEID			m_STATE;
	ILLUSIONWALKID			m_WALK;
	ILLUSIONIDLEID			m_IDLE;
	ILLUSIONATTACKID		m_ATTACK;

	CLayer*					pMyLayer;
	list<char*>				m_CharList;
	list<_tchar*>			m_TcharList;

public:
	static CIllusioner*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, _tchar* Name);
	virtual void	Free(void);

};

