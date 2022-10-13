#pragma once
#include "GameObject.h"
class CLogoBilboard : public CGameObject
{
private:
	explicit CLogoBilboard(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLogoBilboard();

public:
	HRESULT Ready_Object(const _vec3 & vPos);
	_int	Update_Object(const _float& fTimeDelta) override;
	void	LateUpdate_Object(void) override;
	void	Render_Object(void) override;

private:
	HRESULT Add_Component();

private:
	CRcTex*	m_pBufferCom = nullptr;
	CTransform* m_pTransCom = nullptr;
	CTexture* m_pTextureCom = nullptr;

public:
	static CLogoBilboard*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
	void Free(void) override;
};

