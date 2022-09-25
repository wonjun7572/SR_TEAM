#pragma once
#include "GameObject.h"
#include "Export_Function.h"

USING(Engine)
class CCubeMonsterBody : public CGameObject
{
public:
	explicit	CCubeMonsterBody(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCubeMonsterBody();


public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;




private:
	HRESULT		Add_component(void);
	CTransform*		m_pTransform = nullptr;
	CTexture*		m_pTexture = nullptr;
	CCubeTex*		m_pCubeTexture = nullptr;

public:
	static CCubeMonsterBody*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void Free(void);


};

