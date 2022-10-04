#pragma once
#include "GameObject.h"

class CRifleGun : public CGameObject
{
private:
	explicit	CRifleGun(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual		~CRifleGun();

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

private:
	HRESULT			Add_Component(void);

private:
	CDynamicBuffer*		m_pBufferCom = nullptr;
	CTransform*			m_pTransCom = nullptr;
	CTexture*			m_pTexture = nullptr;

public:
	static CRifleGun*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void	Free(void);
};

