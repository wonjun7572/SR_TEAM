#pragma once
#include "GameObject.h"
#include "PlayButton.h"
class CLogoUI :
	public CGameObject
{
public:
	explicit CLogoUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLogoUI();


public:
	HRESULT Ready_Object(void) override;
	_int Update_Object(const _float& fTimeDelta) override;
	void LateUpdate_Object(void) override;
	void Render_Object(void) override;

private:
	void		Begin_OrthoProj();
	void		End_OrthoProj();

private:
	HRESULT		Add_component();

private:
	CRcTex*		m_pRcTexCom = nullptr;
	CTransform*	m_pTransCom = nullptr;
	CTexture*	m_pTextureCom = nullptr;

	_matrix	m_matWorld;
	_matrix m_matView;
	_matrix m_matProj;

public:
	static	CLogoUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	void	Free(void) override;
};

