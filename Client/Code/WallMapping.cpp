#include "stdafx.h"
#include "..\Header\WallMapping.h"


CWallMapping::CWallMapping(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CWallMapping::~CWallMapping()
{
}

HRESULT CWallMapping::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_pTransform->Set_Scale(0.5f, 0.5f, 0.5f);
	return S_OK;
}

_int CWallMapping::Update_Object(const _float & fTimeDelta)
{
	if (!m_bMapChange)
	{
		Add_RenderGroup(RENDER_MINIMAP, this);
	}
	if (m_bMapChange)
	{
		Add_RenderGroup(RENDER_MAPVIEW, this);
	}
	WorldMap();

	CGameObject::Update_Object(fTimeDelta);

	return 0;
}

void CWallMapping::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CWallMapping::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	m_pTexture->Set_Texture(47);
	m_pCube->Render_Buffer();
}

void CWallMapping::WorldMap(void)
{
	if (Get_DIKeyState(DIK_9))
	{
		m_bMapChange = false;
	}
	if (Get_DIKeyState(DIK_0))
	{
		m_bMapChange = true;
	}
}

HRESULT CWallMapping::Add_Component(void)
{
	CComponent* pInstance = nullptr;

	pInstance = m_pCube = dynamic_cast<CCubeTex*>(Engine::Clone_Proto(L"Proto_CubeTexCom"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubeTexCom", pInstance });

	pInstance = m_pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_CubePlayerTexture"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubePlayerTexture", pInstance });

	pInstance = m_pTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pInstance });


	return S_OK;
}

CWallMapping * CWallMapping::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWallMapping* pInstance = new CWallMapping(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);


	return pInstance;
}

void CWallMapping::Free(void)
{
	CGameObject::Free();
}


