#pragma once
#include "Export_Function.h"
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
	void		WorldMap(void);
private:
	CTransform*		m_pTransformPlayer = nullptr;
	CTransform*		m_pTransform = nullptr;
	CTexture*		m_pTexture = nullptr;
	CCubeTex*		m_pCube = nullptr;
	CRcTex*			m_pBufferCom = nullptr;
	
	_bool	m_bMapSwitch = false;
	_bool	m_bMapChange = true;
	_matrix m_matWorld;
	_matrix m_matView;
	_matrix m_matProj;

public:
	static CPlayerMapping*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void		Free(void);
};

