#pragma once
#include "GameObject.h"

class CPlayerHpUI :	public CGameObject
{
private:
	explicit CPlayerHpUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayerHpUI();

public:
	HRESULT Ready_Object(void) override;
	_int	Update_Object(const _float& fTimeDelta) override;
	void	LateUpdate_Object(void) override;
	void	Render_Object(void) override;

private:
	void		Begin_OrthoProj();
	void		End_OrthoProj();

	void		TestUIForSetting();

private:
	HRESULT Add_Component();

private:
	CRcTex*	m_pBufferCom = nullptr;
	CTransform* m_pTransCom = nullptr;
	CTexture* m_pTextureCom = nullptr;

	_matrix m_matWorld;
	_matrix m_matView;
	_matrix m_matProj;

	CGameObject* m_pPlayer = nullptr;
	_int	m_iHp;
	wstring m_strHp;

	_float testCX = 0.f;
	_float testCY = 0.f;
	_float testX = 0.f;
	_float testY = 0.f;

public:
	static CPlayerHpUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	void Free(void) override;
};

