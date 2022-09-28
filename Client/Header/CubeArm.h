#pragma once
#include "GameObject.h"
#include "Export_Function.h"

USING(Engine)

class CCubeArm : public CGameObject
{
private:
	explicit CCubeArm(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCubeArm();

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

private:
	HRESULT			Add_Component(void);
	CTransform*		m_pTransform = nullptr;
	CTexture*		m_pTexture = nullptr;
	CCubeTex*		m_pCube = nullptr;

public:
	static CCubeArm*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void		Free(void);
};

