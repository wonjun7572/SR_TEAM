//#pragma once
//#include "Monster.h"
//class CZombie :	public CMonster
//{
//private:
//	explicit CZombie(LPDIRECT3DDEVICE9 pGraphicDev);
//	virtual ~CZombie();
//
//	virtual	HRESULT Ready_Object(const _vec3& vPos);
//	virtual _int	Update_Object(const _float& fTimeDelta) override;
//	virtual void	LateUpdate_Object(void) override;
//	virtual void	Render_Object(void) override;
//
//private:
//	HRESULT				Add_Component(void);
//	HRESULT				Create_Item();
//
//	_float				m_fFrame = 0.f;
//
//public:
//	static CZombie*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
//	virtual void	Free(void);
//};
//

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
	void					Load_Animation(wstring FileName);
	void					Run_Animation(const _float& AnimationSpeed);
	void					Walk_Animation_Run(void);
	void					Look_Direction(void);

private:
	HRESULT				Add_Component(void);
	HRESULT				Create_Item();
	HRESULT				Build(void);
	CCubeCol*			m_pAnimationBox = nullptr;
	_float				m_fFrame = 0.f;
	_bool				m_bFirst = true;
	_float				m_fTimeDelta = 0.f;
	_float				m_AnimationTime = 0.f;
private:
	list<char*>							m_CharList;
	list<_tchar*>						m_TcharList;
	CLayer* pMyLayer = nullptr;
	_tchar*					m_MonsterName;

	MONSTERSTATEID			m_STATE;
	MONSTERWALKID			m_WALK;
	MONSTERSTOPID			m_STOP;

public:
	static CZombie*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, _tchar* Name);
	virtual void	Free(void);
};

