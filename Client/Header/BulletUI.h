#pragma once
#include "GameObject.h"

class CBulletUI : public CGameObject
{
private:
	explicit CBulletUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBulletUI();

public:
	HRESULT Ready_Object(void) override;
	_int	Update_Object(const _float& fTimeDelta) override;
	void	LateUpdate_Object(void) override;
	void	Render_Object(void) override;

private:
	void		Begin_OrthoProj();
	void		End_OrthoProj();

private:
	HRESULT Add_Component();

private:
	CRcTex*		m_pBufferCom = nullptr;
	CTransform* m_pTransCom = nullptr;
	CTexture*	m_pTextureCom = nullptr;

	_matrix m_matWorld;
	_matrix m_matView;
	_matrix m_matProj;

	CGameObject* m_pPlayer = nullptr;
	_float		 m_fRemainBullet = 0;
	_float		 m_fTotalBullet = 0;
	wstring		 m_strReminaBullet = L"";
	wstring		 m_strTotalBullet = L"";

public:
	static CBulletUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	void Free(void) override;
};

