#pragma once
#include "C:\Users\beoms\OneDrive\¹®¼­\GitHub\SR_TEAM\Reference\Header\GameObject.h"
#include "Engine_Include.h"
BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;
class CRenderer;
class CCalculator;

END



class CLoadingBar :
	public CGameObject
{
public:
public:
	explicit CLoadingBar(LPDIRECT3DDEVICE9 pGraphicDev, wstring wstrTex, _vec3 vPos, _float fScale, _int iPivot, _float fLoad);
	virtual ~CLoadingBar(void);
public:
	void     Set_Load(const float& fLoad);
public:
	virtual HRESULT Ready_Object() override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void Render_Object(void) override;

private:
	HRESULT		Add_Component(void);
	void		CalculateTransform();
	void		SetPivot();
	void		SetScale();
	void		SetPos();

private:
	Engine::CRcTex*			m_pBufferCom = nullptr;
	Engine::CTexture*		m_pTextureCom = nullptr;
	Engine::CRenderer*		m_pRendererCom = nullptr;
	Engine::CCalculator*	m_pCalculatorCom = nullptr;

	wstring					m_wstrTexture = L"";
	_matrix					m_MatWorld;
	_matrix					m_MatView;
	_vec3					m_vPos;
	_int					m_iPivot;
	_float					m_fScale;
	_float                  m_fLoad;

public:
	static CLoadingBar*		Create(LPDIRECT3DDEVICE9 pGraphicDev, wstring wstrTex, _vec3 vPos, _float fScale = 1.0f, _int iPivot = 3, _float Load = 0.f);

private:
	virtual void Free(void) override;
};

