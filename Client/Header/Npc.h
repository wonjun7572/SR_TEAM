#pragma once
#include "GameObject.h"

class CNpc : public CGameObject
{
private:
	explicit CNpc(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CNpc();

public:
	HRESULT				Ready_Object(const _vec3& vPos);
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		Render_Object(void) override;

private:
	HRESULT				Add_Component(void);

private:
	CRcTex*				m_pBufferCom = nullptr;
	CTransform*			m_pTransCom = nullptr;
	
	CTexture*			m_pQuest1TexCom = nullptr; // 52 ¿Â
	CTexture*			m_pQuest2TexCom = nullptr; // 61 ¿Â
	CTexture*			m_pQuest3TexCom = nullptr; // 36 ¿Â

	CShader*			m_pShaderCom = nullptr;

	_vec3				m_vScale = _vec3(10.f, 5.f, 1.f);
	_float				m_fFrame = 0.f;
	_vec3				m_vDir = _vec3(0.f, 0.f, 0.f);
	_vec3				m_vPlayerPos = _vec3(0.f, 0.f, 0.f);
	_float				m_fSpeed = 10.f;
	_bool				m_bInit = false;

	_float				m_fTexFrame = 0.f;

public:
	static	CNpc*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);

protected:
	virtual void Free();
};

