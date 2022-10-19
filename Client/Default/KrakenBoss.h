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
	void				ShootInk(void);


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
	CTransform*			m_pSearchRange_TransCom = nullptr;
	CTransform*			m_pAttackRange_TransCom = nullptr;
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
	CCubeCol*			m_pAnimationBox = nullptr;
	//기능관련 
private:
	HRESULT				Add_Component(void);
	HRESULT				Monster_Mapping(void);
	HRESULT				Monster_DeleteMapping(void);
	
private:
	KRAKENABILITY*		m_tAbility;
	_tchar*				m_MonsterName;
	TCHAR*				m_szCntName = new TCHAR[64];
	_bool				m_bFirst = true;
	_bool				m_MappingInit = false;
	list<_tchar*>		m_TcharList;
	list<TCHAR*>		m_listMonsterCnt;
	_float				m_AnimationTime = 0.f;
	_float				m_fTimeDelta = 0.f;
	_float				m_fUISwitchTime = 0.f;
	_float				m_fFrame = 0.f;
	_float				m_fFireAngle = 0.f;
	_vec3				vUIPos;
public:
	static CKrakenBoss*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, _tchar* Name);
	virtual void	Free(void);
};

