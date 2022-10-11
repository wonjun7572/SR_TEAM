#pragma once
#include "GameObject.h"

class COptionButton : public CGameObject
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
	void		Begin_OrthoProj();
	void		End_OrthoProj();

public:
	_bool	Get_MouseCheck(void) { return Mouse_check; }

private:
	_bool		PointMouse(void);
	_bool		Mouse_check = false;
	_bool		Checking = false;

	_matrix m_matWorld;
	_matrix m_matView;
	_matrix m_matProj;

	wstring m_strOB;
	_int	m_iIndex = 0;

public:
	static COptionButton* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void);
};

