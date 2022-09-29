#pragma once
#include "Export_Function.h"
#include "GameObject.h"

USING(Engine)


class CWallMapping :
	public CGameObject
{
private:
	explicit CWallMapping(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWallMapping();

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int	Update_Object(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Object(void) override;
	virtual void	Render_Object(void) override;


public:
	CGameObject*			Set_MapPosition(float fX, float fY, float fZ) { m_vPos.x = fX, m_vPos.y = fY, m_vPos.z = fZ; }

private:
	void			WorldMap(void);

	HRESULT			Add_Component(void);

private:
	CTransform*		m_pTransformPlayer = nullptr;
	CTransform*		m_pTransform = nullptr;
	CTexture*		m_pTexture = nullptr;
	CCubeTex*		m_pCube = nullptr;
	_vec3			m_vPos = { 0.f,0.f,0.f };
	_bool			m_bMapChange = true;
public:
	static CWallMapping*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void		Free(void);
};

