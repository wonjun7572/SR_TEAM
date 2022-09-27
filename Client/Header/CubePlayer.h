#pragma once
#include "GameObject.h"
#include "Export_Function.h"

USING(Engine)


class CCubePlayer : public CGameObject
{
private:
	explicit CCubePlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCubePlayer();

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;
	
	ABILITY*		Get_Ability() { return m_tAbility; }
	void			Set_Damaged(_int iDamage) { m_tAbility->iHp -= iDamage; }

private:
	map<const _tchar*, CGameObject*>	m_mapPlayerBody;

private:
	HRESULT			Get_BodyTransform(void);

	void			Key_Input(const _float& fTimeDelta);		//	키 입력
	void			Set_OnTerrain(void);						//	지형 타기
	void			Assemble(void);								//	몸체 조립

	void			Walk_Animation(void);						//	걷는 모션
	void			Move(void);									//	실제 이동

	void			TransAxis(void);							//	월드행렬 작동

	void			Look_Direction(void);						//	바라보는 방향 변경
	
private:
	void			Jump(void);
	_bool			m_bJump = false;
	_bool			m_bFirst = true;

private:
	HRESULT			Add_Component(void);
	CTransform*		m_pTransform = nullptr;

	CTransform*		m_pHeadWorld = nullptr;

	CTransform*		m_pBodyWorld = nullptr;

	CTransform*		m_pLeftArmWorld = nullptr;
	CTransform*		m_pRightArmWorld = nullptr;

	CTransform*		m_pLeftLegWorld = nullptr;
	CTransform*		m_pRightLegWorld = nullptr;

	CTransform*		m_pLeftHandWorld = nullptr;
	CTransform*		m_pRightHandWorld = nullptr;

	CTransform*		m_pLeftFootWorld = nullptr;
	CTransform*		m_pRightFootWorld = nullptr;

	CCalculator*	m_pCalculatorCom = nullptr;

	CHitBox*		m_pHitBox = nullptr;

private:
	ABILITY*		m_tAbility = nullptr;

	_float			m_fLookAngle = 0.f;

	_float			m_fAngle = 0.f;
	_bool			m_bWalkAngle = true;

	_float			m_fTimeDelta = 0.f;

public:
	static CCubePlayer*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free(void);
};

