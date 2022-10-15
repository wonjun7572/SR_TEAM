#pragma once
#include "GameObject.h"
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

private:
	HRESULT			Build(void);

	_vec3			m_vDirection;
	_vec3			m_vAngle;

	int iA = 0;

	vector<_vec3>	m_ShufflePos;

	_float			m_fTimeDelta = 0.f;
	_bool			m_bFirst = true;
	_float			m_AnimationTime = 0.f;

	CLayer*			pMyLayer;
	_tchar*			m_RocketName;

	list<_tchar*>	m_TcharList;

public:
	static CFlight*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos, const _vec3 & vDir, _tchar* Name);
	virtual void		Free(void);
};

