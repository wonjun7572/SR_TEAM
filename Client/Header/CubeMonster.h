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
	//HP���� ������ ���������� death�� �������� ��Ÿ ����ҵ��� �ȿ��ٰ� �־��ִ� ����
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

	//���� 

	CTransform*			m_pMTransform = nullptr;
	//��
	CTransform*			m_pMleftArm = nullptr;
	CTransform*			m_pMrightArm = nullptr;

	//����
	CTransform*			m_pMbody = nullptr;

	//�ҹ��
	CTransform*			m_pMhead = nullptr;

	CTexture*			m_pTextureCom = nullptr;

	//�÷��̾� 
	CTransform*		pPlayerTransformCom = nullptr;

	CCalculator*		m_pCalculator = nullptr;

	//test
private:

	_int		ComeBack(_float fTimeDelta);


private:

	//Ž�������� �ٰ��̴�. 
	_float			m_fDetectRange;
	_float			m_fAttackRange;
	_float			m_fLengthRange;
	_float			m_fMinLenghtRange;


	_float			m_fSpeed;
	_float			m_fTimeDelta;
	_float			m_fAngle = 0;
	_float			m_floatAngle = 0;

	_float			m_iInterval;
	//���� ���¸� Ȯ�����ֱ����ؼ� ����غ������Ѵ�. �̰� �����ϳ�?
	CurrentState::MONSTERID		m_eCurrentState;
	CurrentState::MONSTERID		m_ePreviousState;


	//������ �ʿ��Ұ��̰� ���ߴ»��µ� �ʿ��ϰ� 
	_bool				m_bAttack = false;
	_bool				m_bDeath = false;
	_float				m_bShoot;
	_float				m_fInterval;



	_vec3	m_vEye, m_vAt;
	_float m_fDistance = 13.f;


	// ���� �ڱ��ڽ�
	_vec3				m_vPos;
	_vec3				 BodyPos;
	//�÷��̾� �������ҷ���������(��)
	_vec3			vPlayerPos;
	//�÷��̾�� ���� �Ÿ��� ���ϱ� ���ؼ� 
	_vec3				m_vDir;

	_vec3				m_vDirection = { 0.f, 0.f, 0.f };
	//���͸� �����ϴ°��� Engine::struct.h�� �־ ü���� �־��ָ���� ������ 
	//api��� �״�� �׳� �������ָ� ������������ �ǹ��� ��������. 

	MONSTERABILITY					m_MonsterState;

	//���� ���� �����Դϴ�.
	_int		m_iCnt = 0;
	CTransform*			m_pMonsterMapping = nullptr;
	list<TCHAR*>		m_listMonsterCnt;
	_bool				m_MappingInit = false;


public:
	static CCubeMonster*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free(void);

};

