#pragma once
#include "GameObject.h"

namespace Engine
{
	class CTransform;
	class CRcTex;
	class CTexture;
	class CCubeTex;
}

class CBullet : public CGameObject
{
public:
	explicit CBullet(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBullet();

public:
	virtual HRESULT Ready_Object(const _vec3* pPos, const _vec3* pDir);
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

public:
	HRESULT			Add_Component(void);

private:
	CRcTex*				m_pBufferCom = nullptr;
	CTransform*			m_pTransCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CCubeTex*			m_pCubetexCom = nullptr;
	_vec3				m_vDirection = _vec3(0.f, 0.f, 0.f);
	_float				m_fSpeed = 10.f;
	_float				fTimeDelta = 1.f;

public:
	static CBullet*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3* pPos, const _vec3* pDir);
	virtual void		Free(void);
};

