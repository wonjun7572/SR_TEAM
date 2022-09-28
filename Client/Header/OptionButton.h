#pragma once
#include "GameObject.h"
BEGIN(Engine)

class CRcTex;
class CTransform;
class CTexture;
END

class COptionButton :
	public CGameObject
{
public:
	explicit COptionButton(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~COptionButton();

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void LateUpdate_Object(void) override;
	virtual void Render_Object(void) override;

private:
	CRcTex*			m_pRcTexCom = nullptr;
	CTransform*     m_pTransformCom = nullptr;
	CTexture*		m_pTextureCom = nullptr;

private:
	HRESULT		Add_Component(void);

	_bool		PointMouse(void);
	_bool		Mouse_check = false;
public:
	static COptionButton* Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	virtual void Free(void);
};

