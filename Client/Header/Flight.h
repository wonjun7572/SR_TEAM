#pragma once
#include "GameObject.h"

class CFlightBulletParticle;

class CFlight :
	public CGameObject
{
private:
	explicit CFlight(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CFlight();

public:
	virtual HRESULT Ready_Object(const _vec3 & vPos, const _vec3 & vDir, _tchar * Name);
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

private:
	HRESULT			Add_Component(void);
	CTransform*		m_pTransform = nullptr;

public:
	void			Replace(const _vec3& vPos, const _vec3& vAngle, const _vec3& vDir)
	{
		m_pTransform->Set_Pos(vPos.x, vPos.y, vPos.z);
		m_vAngle = vAngle;
		m_vDirection = vDir;
	}

	void			Set_Control() { m_bControl = !m_bControl; }
	_bool			Get_Control() { return m_bControl; }
	_bool			Get_Shoot() { return m_bShoot; }
	void			Set_Shoot(_bool bShoot) { m_bShoot = bShoot; }
private:
	HRESULT			Build(void);
	void			Key_Input(const _float& fTimeDelta);
	void			Look_Direction();
	void			Fire_Bullet();


	_vec3			m_vDirection;
	_vec3			m_vAngle;

	int iA = 0;

	vector<_vec3>	m_ShufflePos;

	_int			m_iPosSet = -1;

	_float			m_fTimeDelta = 0.f;
	_bool			m_bFirst = true;
	_float			m_AnimationTime = 0.f;

	CLayer*			pMyLayer;
	_tchar*			m_RocketName;

	_bool			m_bControl = false;
	_bool			m_bShoot = false;
	_float			m_fBulletTime = 0.f;
	CFlightBulletParticle * m_pBulletParicle = nullptr;
	
	list<_tchar*>	m_TcharList;

public:
	static CFlight*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, const _vec3 & vDir, _tchar* Name);
	virtual void		Free(void);
};

