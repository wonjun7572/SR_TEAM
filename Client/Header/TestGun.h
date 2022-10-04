#pragma once
#include "GameObject.h"

class CTestGun : public CGameObject
{
private:
	explicit CTestGun(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTestGun();

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
	static CTestGun*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void	Free(void);
};

