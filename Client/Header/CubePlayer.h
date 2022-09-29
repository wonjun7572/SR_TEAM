#pragma once
#include "GameObject.h"
#include "Export_Function.h"
#include "Weapon.h"

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
	}
	void			Get_Angle(_float& fLook, _float& fLeftArm, _float& fRightArm, _float& fHandAngle)
	{
		fLook = m_fLookAngle;
		fLeftArm = m_fLeftArmAngle;
		fRightArm = m_fRightArmAngle;
		fHandAngle = m_fHandAngle;
	}
	//void			Get_Direction(_vec3* vDir) { memcpy(vDir, m_vDirection, sizeof(_vec3)); }

public:
	ABILITY*      Get_Ability() { return m_tAbility; }
	void         Set_Damaged(_int iDamage) { m_tAbility->iHp -= iDamage; }

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

public:
	CWeapon*		Get_Weapon() { return m_Weapon; }

private:
	map<const _tchar*, CGameObject*>	m_mapPlayerBody;

private:
	HRESULT			Get_BodyTransform(void);

	void			Key_Input(const _float& fTimeDelta);
	void			Set_OnTerrain(void);
	void			Assemble(void);

	void			Animation(void);
	void			TransAxis(void);

	void			Move(void);

	void			Look_Direction(void);

	void			Fire_Bullet(void);

	void			Gun_Check(void);

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
	CCollision*		m_pCollision = nullptr;

	CHitBox*		m_pHitBox = nullptr;

	ABILITY*		m_tAbility = nullptr;

private:
	_float			m_fLookAngle = 0.f;
	_float			m_fDownAngle = 0.f;

	_float			m_fLeftArmAngle = 0.f;
	_float			m_fRightArmAngle = 0.f;
	_float			m_fLeftLegAngle = 0.f;
	_float			m_fRightLegAngle = 0.f;
	_float			m_fHandAngle = 0.f;

	_bool			m_bWalkAngle = true;
	_bool			m_bWalkAngle_Leg = true;

	_float			m_fTimeDelta = 0.f;

	_vec3			m_vMin = { 0.f, 0.f, 0.f };
	_vec3			m_vMax = { 0.f, 0.f, 0.f };

	_float			m_fSpeed = 10.f;

	CWeapon*		m_Weapon = nullptr;

	_bool			m_bUzi = true;

	vector<CWeapon*> m_vecWeapon;

public:
	static CCubePlayer*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free(void);
};

