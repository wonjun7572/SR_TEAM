#pragma once
#include "GameObject.h"

class CPlayerFaceUI : public CGameObject
{
private:
	explicit CPlayerFaceUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayerFaceUI();

public:
	HRESULT Ready_Object(void) override;
	_int Update_Object(const _float& fTimeDelta) override;
	void LateUpdate_Object(void) override;
	void Render_Object(void) override;

private:
	void		Begin_OrthoProj();
	void		End_OrthoProj();

private:
	HRESULT Add_Component();

private:
	CGameObject* m_pPlayer = nullptr;

	CRcTex*		m_pBufferCom = nullptr;
	CTransform* m_pTransCom = nullptr;

	CTexture*	m_pTexture_100 = nullptr;
	CTexture*	m_pTexture_75 = nullptr;
	CTexture*	m_pTexture_50 = nullptr;
	CTexture*	m_pTexture_25 = nullptr;
	CTexture*	m_pTexture_0 = nullptr;

	_matrix m_matWorld;
	_matrix m_matView;
	_matrix m_matProj;

	_float m_fFrame = 0.f;

public:
	static CPlayerFaceUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	void Free(void) override;
};

