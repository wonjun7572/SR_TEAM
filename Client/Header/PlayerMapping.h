#pragma once
#include "Export_Function.h"
#include "BaseMapping.h"

#include "GameObject.h"

USING(Engine)


class CPlayerMapping :
	public CGameObject
{
private:
	explicit CPlayerMapping(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayerMapping();

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;

private:
	HRESULT			Add_Component(void);
	void		Begin_OrthoProj();
	void		End_OrthoProj();
	void		Key_Input(void);
private:
	CTransform*		m_pTransformPlayer = nullptr;
	CTransform*		m_pTransform = nullptr;
	CTexture*		m_pTexture = nullptr;
	CCubeTex*		m_pCube = nullptr;
	CRcTex*			m_pBufferCom = nullptr;
	CBaseMapping*	m_pBaseMapping = nullptr;

	_bool	m_bWorldMap = false;
	_bool	m_bMinimap = false;

	_matrix m_matWorld;
	_matrix m_matView;
	_matrix m_matProj;

public:
	static CPlayerMapping*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void		Free(void);
};

