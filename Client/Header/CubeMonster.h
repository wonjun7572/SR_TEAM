#pragma once
#include "GameObject.h"
#include "Export_Function.h"
#include "Engine_Include.h"
#include "CubePlayer.h"
#include "MonsterMapping.h"

namespace CurrentState
{
	enum MONSTERID { MONSTER_IDLE, MONSTER_COMEBACK, MONSTER_FIREATTACK, MONSTER_SWORDATTACK, MONSTER_DEATH, MONSTER_END };
}

USING(Engine)

class  CCubeMonster : public CGameObject
{

public:
	explicit CCubeMonster(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCubeMonster();


public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;


	//test

	virtual _int CurrentMonster(_float fTimeDelta);
	virtual void ChangeCurrent(CurrentState::MONSTERID Idstate);

public:
	//HP값을 들고오면 되지않을까 death나 여러가지 기타 값요소들을 안에다가 넣어주는 형식
	_float		Get_CurrentHP() { return m_MonsterState.fCurrentHp; }

private:
	map<const _tchar*, CGameObject*>	m_mapMonsterBody;
private:

	void			Set_OnTerrain(void);
	void			Assemble(void);
	void			Axis(void);
	void			Death(void);
	void			PatternAttackOne(void);
	void			PatternAttackTwo(void);


	void			FireBullet(const _float fTimeDelat);
	void			SwordAttack(void);
	HRESULT			Get_BodyTransform(void);
	HRESULT			Monster_Mapping(void);
private:
	HRESULT  Add_Component(void);

	//몬스터 

	CTransform*			m_pMTransform = nullptr;
	//팔
	CTransform*			m_pMleftArm = nullptr;
	CTransform*			m_pMrightArm = nullptr;

	//몸통
	CTransform*			m_pMbody = nullptr;

	//뚝배기
	CTransform*			m_pMhead = nullptr;

	CTexture*			m_pTextureCom = nullptr;

	//플레이어 
	CTransform*		pPlayerTransformCom = nullptr;

	CCalculator*		m_pCalculator = nullptr;

	//test
private:

	_int		ComeBack(_float fTimeDelta);


private:

	//탐지범위를 줄것이다. 
	_float			m_fDetectRange;
	_float			m_fAttackRange;
	_float			m_fLengthRange;
	_float			m_fMinLenghtRange;


	_float			m_fSpeed;
	_float			m_fTimeDelta;
	_float			m_fAngle = 0;
	_float			m_floatAngle = 0;

	_float			m_iInterval;
	//몬스터 상태를 확인해주기위해서 사용해보려고한다. 이게 가능하냐?
	CurrentState::MONSTERID		m_eCurrentState;
	CurrentState::MONSTERID		m_ePreviousState;


	//공격이 필요할것이고 멈추는상태도 필요하고 
	_bool				m_bAttack = false;
	_bool				m_bDeath = false;
	_float				m_bShoot;
	_float				m_fInterval;



	_vec3	m_vEye, m_vAt;
	_float m_fDistance = 13.f;


	// 몬스터 자기자신
	_vec3				m_vPos;
	_vec3				 BodyPos;
	//플레이어 정보값불러오기위함(몸)
	_vec3			vPlayerPos;
	//플레이어와 몬스터 거리를 구하기 위해서 
	_vec3				m_vDir;

	_vec3				m_vDirection = { 0.f, 0.f, 0.f };
	//몬스터만 관리하는것을 Engine::struct.h에 넣어서 체력을 넣어주면되지 않을까 
	//api방식 그대로 그냥 가져와주면 되지않을까라는 의문을 가져본다. 

	MONSTERABILITY					m_MonsterState;

	//맵핑 관련 변수입니다.
	_int		m_iCnt = 0;
	CTransform*			m_pMonsterMapping = nullptr;
	list<TCHAR*>		m_listMonsterCnt;
	_bool				m_MappingInit = false;


public:
	static CCubeMonster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free(void);

};

