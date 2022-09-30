#pragma once
#include "GameObject.h"

namespace Engine
{
	class CCubeTex;
	class CTexture;
	class CTransform;
}

class CWall : public CGameObject
{

	enum WALLID { WALL_TERRAIN, WALL_END, };

protected:
	explicit CWall(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWall();

public:
	virtual		HRESULT		Ready_Object(_ulong Texture, _vec3 * Position);
	virtual		_int		Update_Object(const _float& fTimeDelta);
	virtual		void		LateUpdate_Object(void);
	virtual		void		Render_Object(void);

private:
	HRESULT					Add_Component(void);
	CCubeTex*				m_pCubeTex = nullptr;
	CTexture*				m_pTexture = nullptr;
	CTransform*				m_pTransform = nullptr;

private:
	_ulong					m_dwWallTextureNum;

public:
	static CWall*	Create(LPDIRECT3DDEVICE9 pGraphicDev, _ulong Texture, _vec3 * Position);
	virtual void	Free(void);

};

