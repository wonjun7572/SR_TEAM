#pragma once
#include "GameObject.h"
class CSpBullet :
	public CGameObject
{
private:
	explicit CSpBullet(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSpBullet();

public:
	virtual HRESULT Ready_Object(const _vec3* pPos, const _vec3* pDir, _float _fDamage, _float _fSpeed);
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

public:
	HRESULT			Add_Component(void);
	void Set_Pos(const _vec3& vPos);
	void MoveToDir(const _vec3& vDir);
	void Before_Update();
	void Set_Dir(const _vec3& vDir) { m_vDirection = vDir; }

private:
	CTransform*			m_pTransCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CSphereTex*			m_pBufferCom = nullptr;

	CCollision*			m_pCollision = nullptr;

	_vec3				m_vDirection = _vec3(0.f, 0.f, 0.f);
	_float				m_fSpeed = 50.f;
	_float				m_fTimeDelta = 0.f;

	_bool				m_bDamage = false;
	_float				m_fDamage = 0.f;

public:
	static CSpBullet*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3* pPos, const _vec3* pDir, _float _fDamage, _float _fSpeed);
	virtual void		Free(void);
};
