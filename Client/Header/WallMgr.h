#pragma once
#include "Base.h"
#include "Wall.h"
#include "Engine_Include.h"

class CWallMgr :	public CBase
{
	DECLARE_SINGLETON(CWallMgr)

private:
	explicit CWallMgr();
	virtual ~CWallMgr();

public:
	HRESULT	Ready_Wall(LPDIRECT3DDEVICE9 pGraphicDev, _ulong Texture, _vec3* Position);

private:
	list<CWall*>	m_WallList;

public:
	virtual void Free(void);
};

