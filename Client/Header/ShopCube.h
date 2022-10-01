#pragma once
#include "GameObject.h"

class CShopCube : public CGameObject
{
private:
	explicit CShopCube(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CShopCube();

public:
	HRESULT Ready_Object(void) override;
	_int Update_Object(const _float& fTimeDelta) override;
	void LateUpdate_Object(void) override;
	void Render_Object(void) override;

private:
	HRESULT				Add_Component(void);

	CCubeTex*		m_pBufferCom = nullptr;
	CTransform*		m_pTransCom = nullptr;
	CTexture*		m_pTextureCom = nullptr;

public:
	static CShopCube* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	void Free(void) override;
};

