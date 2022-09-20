#include "..\..\Header\LightMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CLightMgr)

CLightMgr::CLightMgr()
{
}

CLightMgr::~CLightMgr()
{
	Free();
}

HRESULT CLightMgr::Ready_Light(LPDIRECT3DDEVICE9 pGraphicDev, const D3DLIGHT9 * tLightInfo, const _uint & iIndex)
{
	CLight*	pInstance = CLight::Create(pGraphicDev, tLightInfo, iIndex);
	NULL_CHECK_RETURN(pInstance, E_FAIL);

	m_LightList.push_back(pInstance);

	return S_OK;
}

void CLightMgr::Free(void)
{
	for_each(m_LightList.begin(), m_LightList.end(), CDeleteObj());
	m_LightList.clear();
}
