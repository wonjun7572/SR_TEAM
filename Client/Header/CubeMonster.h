#pragma once
#include "GameObject.h"
#include "Export_Function.h"
#include "Engine_Include.h"
#include "CubePlayer.h"
#include "MonsterMapping.h"

namespace CurrentState
{
	enum MONSTERID { MONSTER_IDLE, MONSTER_COMEBACK, MONSTER_ATTACK, MONSTER_DEATH, MONSTER_END };
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
	virtual _int CurrentMonster(_float fTimeDelta);
	virtual void ChangeCurrent(CurrentState::MONSTERID Idstate);

public:
	//HP값을 들고오면 되지않을까 death나 여러가지 기타 값요소들을 안에다가 넣어주는 형식
	
	_float		Get_CurrentHP() { return m_MonsterState.fCurrentHp; }
	
	MONSTERABILITY	Get_MAbility() { return m_MonsterState; }
	
	void		Set_Damage() { m_MonsterState.fCurrentHp -= 10; }
private:
	map<const _tchar*, CGameObject*>	m_mapMonsterBody;
private:

	void			Set_OnTerrain(void);
	void			Assemble(void);
	void			Axis(void);

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

	_int		Attack(_float fTimeDelta);
	_int		ComeBack(_float fTimeDelta);


private:

	
	_float			m_fDetectRange;
	_float			m_fAttackRange;
	_float			m_fLengthRange;
	_float			m_fMinLenghtRange;


	_float			m_fSpeed;
	_float			m_fTimeDelta;
	_float			m_fAngle = 0;
	_float			m_floatAngle = 0;
	
	CurrentState::MONSTERID		m_eCurrentState;
	CurrentState::MONSTERID		m_ePreviousState;


	_bool				m_bAttack;
	_bool				m_bShoot;
	_vec3	m_vEye, m_vAt;
	_float m_fDistance = 13.f;
	// 몬스터 자기자신
	_vec3				m_vPos;
	_vec3				 BodyPos;
	//플레이어 정보값불러오기위함(몸)
	_vec3			vPlayerPos;
	//플레이어와 몬스터 거리를 구하기 위해서 
	_vec3				m_vDir;
	//몬스터만 관리하는것을 Engine::struct.h에 넣어서 체력을 넣어주면되지 않을까 
	//api방식 그대로 그냥 가져와주면 되지않을까라는 의문을 가져본다. 

	MONSTERABILITY			m_MonsterState;

	//맵핑 관련 변수입니다.
	_int		m_iCnt = 0;
	CTransform*			m_pMonsterMapping = nullptr;
	list<TCHAR*>		m_listMonsterCnt;
	_bool				m_MappingInit = false;


public:
	static CCubeMonster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free(void);

};

