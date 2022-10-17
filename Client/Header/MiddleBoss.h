#pragma once
#include "GameObject.h"
#include "SparkEffect.h"
class CMonsterUI;
class CComboUI;

class CMiddleBoss :
	public CGameObject
{
public:
	explicit CMiddleBoss(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMiddleBoss();

public:
	virtual	HRESULT Ready_Object(const _vec3& vPos, _tchar* Name);
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;
	virtual _int	Update_Pattern(_float fTimeDelta);
	void			Hit_Check(_float _deltaTime);
private:
	HRESULT				Build(void);
	void				Load_Animation(wstring FileName, _uint AnimationID);
	void				Run_Animation(const _float& AnimationSpeed);
	void				Look_Direction(void);

	void				Walk_Animation_Run(void);
	void				Idle_Animation_Run(void);
	void				Attack_Animation_Run(void);
	void				Shot_Animation_Run(void);
	void				Set_OnTerrain(void);
	_bool				Collision_Wall(const _float& fTimeDelta);
	_float				m_fTimeDelta = 0.f;
	_bool				m_bFirst = true;
	_float				m_AnimationTime = 0.f;
	CLayer*				pMyLayer;
	_tchar*				m_MonsterName;
	list<_tchar*>		m_TcharList;


	MIDDLEBOSSSTATEID		m_STATE;
	MIDDLEBOSSSTATEID		m_BeforeState;
	MIDDLEBOSSWALKID		m_WALK;
	MIDDLEBOSSIDLEID		m_IDLE;
	MIDDLEBOSSATTACKID		m_ATTACK;
	MIDDLEBOSSSHOOTID		m_SHOT;

private:
	HRESULT				Create_Item();
	HRESULT				Monster_Mapping(void);
	HRESULT				Monster_DeleteMapping(void);

	

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
	CTexture*			m_pTextureUICom = nullptr;
	CHitBox*			m_pHitBox = nullptr;
	CCollision*			m_pCollision = nullptr;
	CComboUI*			m_pComboUI = nullptr;
	CCubeCol*			m_pAnimationBox = nullptr;
	CCalculator*	m_pCalculatorCom = nullptr;
	CSparkEffect* m_pSparkEffectParticle = nullptr;
	//CBrownCloudEffect* m_pBrownCloudEffectParticle = nullptr;
	//#### 갈색구름
//	if (!m_pBrownCloudEffectParticle)
//		m_pBrownCloudEffectParticle = dynamic_cast<CBrownCloudEffect*>(Engine::Get_GameObject(STAGE_ENVIRONMENT, L"BrownCloudEffect"));
//	m_pBrownCloudEffectParticle->Set_PclePos(m_vDeadPos);
//	for (_int i = 0; i < 70; ++i)
//	{
//		m_pBrownCloudEffectParticle->addParticle();
//	}

private:
	_float				m_fFrame = 0.f;
	_float				m_fTargetLength;
	_float				m_fDetectRange;
	_float				m_fAttackRange;
	_float				m_fUISwitchTime = 0.f;
	_float				m_fFireAngle = 0.f;
	_float				m_fSpeed = 1.f;
	_vec3				vUIPos;
	_bool				m_MappingInit = false;
	TCHAR*				m_szCntName = new TCHAR[64];
	_vec3		m_vDeadPos = { 0.f,0.f,0.f };
	list<TCHAR*>		m_listMonsterCnt;
private:
	HRESULT				Add_Component(void);
	MIDDLEBOSSABILITY*		m_tAbility;


public:
	static CMiddleBoss*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, _tchar* Name);
	virtual void	Free(void);


};

