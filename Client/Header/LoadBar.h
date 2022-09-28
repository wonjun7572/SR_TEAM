#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;

END

class CLoadBar : public CGameObject
{
public:
	CLoadBar(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLoadBar();

public:
	virtual HRESULT Ready_Object() override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void LateUpdate_Object(void) override;
	virtual void Render_Object(void) override;

private:
	HRESULT		Add_Component(void);

public:
	CRcTex*			m_pRcTexCom = nullptr;
	CTexture*		m_pTextureCom = nullptr;
	CTransform*		m_pTransformCom = nullptr;

private:
	_float CurrentLoading;
	_float OriginLoading;
	//로딩 비율 
	_float LoadingRate;
	_float LoadingBar;

	_bool	firstLoading = true;			//첫번쨰 로딩 시작시 

	_float m_fNewHeight;
	
	RECT		m_tRect;

public:
	static CLoadBar* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

