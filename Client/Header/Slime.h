#pragma once
#include "Monster.h"

BEGIN(Engine)

class CHitBox;
class CTransform;
class CCalculator;
class CCollision;
class CCubeCol;

END

class CSlime : public CMonster
{
private:
	explicit CSlime(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSlime();

public:
	virtual		HRESULT		Ready_Object(const _vec3& vPos, _tchar* Name);
	virtual		_int		Update_Object(const _float& fTimeDelta);
	virtual		void		LateUpdate_Object(void);
	virtual		void		Render_Object(void);

private:
	HRESULT				Add_Component(void);
	HRESULT				Create_Item();

	CCubeCol*			m_pAnimationBox = nullptr;

	_float				m_fFrame = 0.f;

private:	//	애니메이션 관련
	HRESULT					Build(void);
	void					Load_Animation(wstring FileName);
	void					Run_Animation(const _float& AnimationSpeed);
	void					Jump_Animation_Run(void);

	_float					m_fTimeDelta = 0.f;
	_bool					m_bFirst = true;
	_float					m_AnimationTime = 0.f;

	SLIMESTATEID			m_STATE;
	SLIMEJUMPID				m_JUMP;

	CLayer*					pMyLayer;
	_tchar*					m_MonsterName;

	list<char*>				m_CharList;				// char쓰레기통
	list<_tchar*>			m_TcharList;			// tchar쓰레기통

public:
	static CSlime*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, _tchar* Name);
	virtual void	Free(void);
};

