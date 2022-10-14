#pragma once
#include "GameObject.h"

class CMonsterUI;
class CComboUI;

class CKrakenBoss :
	public CGameObject
{
public:
	CKrakenBoss(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CKrakenBoss();


public:
	virtual	HRESULT Ready_Object(const _vec3& vPos, _tchar* Name);
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	Render_Object(void) override;
	virtual void	LateUpdate_Object(void) override;

private:
	void				Look_Direction(void);
	virtual _int		Update_Pattern(_float fTimeDelta);
	void				Hit_Check(_float _deltaTime);
	//애니메이션 관련
private:
	KRAKENSTATEID	m_STATE;
	KRAKENSTATEID   m_BeforeState;
	KRAKENWALKID	m_WALK;
	KRAKENIDLEID	m_IDLE;
	KRAKENATTACKID	m_ATTACK;
	KRAKENSHOTID	m_SHOT;
	HRESULT				Build(void);
	void				Load_Animation(wstring FileName, _uint AnimationID);
	void				Run_Animation(const _float& AnimationSpeed);
	void				Walk_Animation_Run(void);
	void				Idle_Animation_Run(void);
	void				Attack_Animation_Run(void);
	void				Shot_Animation_Run(void);
	void				Set_OnTerrain(void);

protected:
	CTransform*			m_pTransCom = nullptr;
	CTransform*			m_pTransUICom = nullptr;
	CTransform*			m_pHitBoxTransCom = nullptr;
	CTransform*			m_pSphereTransCom = nullptr;
	CTransform*			m_pMonsterMapping = nullptr;
	CTransform*			m_pPlayerTransCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CCubeTex*			m_pBufferCom = nullptr;
	CSphereTex*			m_pSphereBufferCom = nullptr;
	CMonsterUI*			m_pMonsterUI = nullptr;
	CRcTex*				m_pBufferUICom = nullptr;
	CCalculator*		m_pCalculatorCom = nullptr;
	CTexture*			m_pTextureUICom = nullptr;
	CHitBox*			m_pHitBox = nullptr;
	CCollision*			m_pCollision = nullptr;
	CComboUI*			m_pComboUI = nullptr;
	CLayer*				pMyLayer;

	//기능관련 
private:
	HRESULT				Add_Component(void);
	KRAKENABILITY*		m_tAbility;
	_tchar*				m_MonsterName;
	_bool				m_bFirst = true;
	list<_tchar*>		m_TcharList;
	_float				m_AnimationTime = 0.f;
	_float				m_fTimeDelta = 0.f;
	_float				m_fUISwitchTime = 0.f;
	_vec3				vUIPos;

public:
	static CKrakenBoss*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, _tchar* Name);
	virtual void	Free(void);
};

