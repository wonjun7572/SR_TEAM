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
	void			Get_HitboxMin(_vec3* vMin, _vec3* vMax) 
	{
		D3DXVec3TransformCoord(vMin, &m_vMin, m_pTransform->Get_WorldMatrixPointer());
		D3DXVec3TransformCoord(vMax, &m_vMax, m_pTransform->Get_WorldMatrixPointer());

		//cout << vMin->x << " " << vMin->y << " " << vMin->z << "     " << vMax->x << " " << vMax->y << " " << vMax->z << endl;
	}
	void			Get_Angle(_float& fLook, _float& fLeftArm, _float& fRightArm, _float& fHandAngle)
	{
		fLook = m_fLookAngle;
		fLeftArm = m_fLeftArmAngle;
		fRightArm = m_fRightArmAngle;
		fHandAngle = m_fHandAngle;
	}

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

public:
	ABILITY*		Get_Ability() { return m_tAbility; }
	void			Set_Damaged(_int iDamage) { m_tAbility->iHp -= iDamage; }

private:
	map<const _tchar*, CGameObject*>	m_mapPlayerBody;

private:
	HRESULT			Get_BodyTransform(void);

	void			Key_Input(const _float& fTimeDelta);		//	키 입력
	void			Set_OnTerrain(void);						//	지형 타기
	void			Assemble(void);								//	몸체 조립

	void			Animation(void);							//	걷는 모션
	void			TransAxis(void);							//	월드행렬 작동

	void			Move(void);									//	실제 이동

	void			Look_Direction(void);						//	바라보는 방향 변경

	void			Fire_Bullet(void);

private:
	void			Jump(void);
	_bool			m_bJump = false;
	_bool			m_bFirst = true;

private:
	HRESULT			Add_Component(void);
	ABILITY*		m_tAbility = nullptr;
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

	CCollision*		m_pCollision = nullptr;

	CHitBox*		m_pHitBox = nullptr;

private:
	_float			m_fLookAngle = 0.f;	//	Y축 회전값
	_float			m_fArmAngle = 0.f;
	_float			m_fHandAngle = 0.f;
	_float			m_fLegAngle = 0.f;
	_float			m_fFootAngle = 0.f;

	_float			m_fDownAngle = 0.f;

	_float			m_fLeftArmAngle = 0.f;
	_float			m_fRightArmAngle = 0.f;

	_float			m_fLeftLegAngle = 0.f;
	_float			m_fRightLegAngle = 0.f;

	//_float			m_fAngle = 0.f;		//	팔다리 X회전값
	//_float			m_fLegAngle = 0.f;

	//_float			m_fArmAngle = 0.f;	//	손발 X회전값

	_bool			m_bWalkAngle = true;
	_bool			m_bWalkAngle_Leg = true;

	_float			m_fTimeDelta = 0.f;

	_vec3			m_vMin = { 0,0,0 };
	_vec3			m_vMax = { 0,0,0 };

	_vec3			vT1 = { 0,0,0 };
	_vec3			vT2 = { 0,0,0 };

public:
	static CCubePlayer*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free(void);
};

