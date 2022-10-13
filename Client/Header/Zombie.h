#pragma once
#include "Monster.h"
#include "Engine_Include.h"

class CZombie : public CMonster
{
private:
	explicit CZombie(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CZombie();

	virtual	HRESULT Ready_Object(const _vec3& vPos, _tchar* Name);
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

private:
	HRESULT				Add_Component(void);
	HRESULT				Create_Item();

private:	//	애니메이션 관련
	HRESULT				Build(void);
	void				Load_Animation(wstring FileName, _uint AnimationID);
	void				Run_Animation(const _float& AnimationSpeed);
	void				Look_Direction(void);

	_float				m_fTimeDelta = 0.f;
	_bool				m_bFirst = true;
	_float				m_AnimationTime = 0.f;

	void				Walk_Animation_Run(void);
	void				Idle_Animation_Run(void);
	void				Attack_Animation_Run(void);
	void				Dead_Animation_Run(void);

	ZOMBIESTATEID		m_STATE;
	ZOMBIEWALKID		m_WALK;
	ZOMBIEIDLEID		m_IDLE;
	ZOMBIEATTACKID		m_ATTACK;
	ZOMBIEDEADID		m_DEAD;

	CLayer*				pMyLayer;
	_tchar*				m_MonsterName;

	list<_tchar*>		m_TcharList;



//private:
//	HRESULT				Add_Component(void);
//	HRESULT				Create_Item();
//	CCubeCol*			m_pAnimationBox = nullptr;
//	_float				m_fFrame = 0.f;
//	_bool				m_bFirst = true;
//	_float				m_fTimeDelta = 0.f;
//	_float				m_AnimationTime = 0.f;
//
//private:
//	list<char*>							m_CharList;
//	list<_tchar*>						m_TcharList;
//	CLayer* pMyLayer = nullptr;
//	_tchar*								m_MonsterName;
//
//	MONSTERSTATEID			m_STATE;
//	MONSTERWALKID			m_WALK;
//	MONSTERSTATEID			m_BeforeState;
//	MONSTERIDLEID			m_IDLE;
//	MONSTERATTACKID			m_ATTACK;
//	MONSTERDEADID			m_DEAD;

public:
	static CZombie*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, _tchar* Name);
	virtual void	Free(void);
};

