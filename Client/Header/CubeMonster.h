#pragma once
#include "GameObject.h"
#include "Export_Function.h"
<<<<<<< Updated upstream
=======
#include "Engine_Include.h"
#include "CubePlayer.h"
#include "MonsterMapping.h"
namespace CurrentState
{
	enum MONSTERID { MONSTER_IDLE, MONSTER_COMEBACK, MONSTER_ATTACK, MONSTER_DEATH, MONSTER_END };
}

>>>>>>> Stashed changes

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

private:
	map<const _tchar*, CGameObject*>	m_mapMonsterBody;

private:

	void	Set_OnTerrain(void);
	void			Assemble(void);
	HRESULT			Get_BodyTransform(void);

private:
	HRESULT  Add_Component(void);

	CTransform*			m_pTransform = nullptr;
	//팔
	CTransform*			m_pMleftArm = nullptr;
	CTransform*			m_pMrightArm = nullptr;
	//몸통
	CTransform*			m_pMbody = nullptr;

	//뚝배기
	CTransform*			m_pMhead = nullptr;

	CCalculator*		m_pCalculator = nullptr;


<<<<<<< Updated upstream
=======
			

//test
private:

	_int		Attack(_float fTimeDelta);
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
	//몬스터 상태를 확인해주기위해서 사용해보려고한다. 이게 가능하냐?
	CurrentState::MONSTERID		m_eCurrentState;
	CurrentState::MONSTERID		m_ePreviousState;


	//공격이 필요할것이고 멈추는상태도 필요하고 
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

	MONSTERABILITY					m_MonsterState;
	FRAME							m_tFrame;


	//맵핑넘버
	_int		m_iCnt = 0;
	CTransform*			m_pMonsterMapping = nullptr;
	list<TCHAR*>		m_listMonsterCnt;
	_bool				m_MappingInit = false;


>>>>>>> Stashed changes

public:
	static CCubeMonster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free(void);

};

