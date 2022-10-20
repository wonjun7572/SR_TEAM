#pragma once
#include "GameObject.h"

class CNpc : public CGameObject
{
private:
	explicit CNpc(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CNpc();

public:
	HRESULT				Ready_Object(const _vec3& vPos);
	virtual HRESULT		Set_Material()override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		Render_Object(void) override;

private:
	HRESULT				Add_Component(void);

private:
	CCubeTex*			m_pBufferCom = nullptr;
	CTransform*			m_pTransCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;

public:
	static	CNpc*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);

protected:
	virtual void Free();
};

