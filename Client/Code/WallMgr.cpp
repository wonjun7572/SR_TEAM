#include "stdafx.h"
#include "WallMgr.h"
#include "Export_Function.h"

#include "Stage.h"

USING(Engine)

IMPLEMENT_SINGLETON(CWallMgr)

CWallMgr::CWallMgr()
{
}

CWallMgr::~CWallMgr()
{
	Free();
}

HRESULT CWallMgr::Ready_Wall(LPDIRECT3DDEVICE9 pGraphicDev, _ulong Texture, _vec3 * Position)
{
	CWall*	pWall = CWall::Create(pGraphicDev, Texture, Position);
	NULL_CHECK_RETURN(pWall, E_FAIL);

	m_WallList.push_back(pWall);

	return S_OK;
}

void CWallMgr::Free(void)
{
	for_each(m_WallList.begin(), m_WallList.end(), CDeleteObj());
	m_WallList.clear();

	this->GetInstance()->DestroyInstance();
}
