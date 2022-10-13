#include "stdafx.h"
#include "..\Header\Terrain.h"

#include "Export_Function.h"

CTerrain::CTerrain(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev), m_vDirection({ 0.f, 0.f, 1.f })
{
}

CTerrain::~CTerrain()
{
}

HRESULT CTerrain::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	SetCheckFrustum(false);
	return S_OK;
}

_int CTerrain::Update_Object(const _float & fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);

	Add_RenderGroup(RENDER_PRIORITY, this);

	return 0;
}

void CTerrain::LateUpdate_Object(void)
{
	Engine::CGameObject::LateUpdate_Object();
}

void CTerrain::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());

	//m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);

	if (m_bWireFrame)
		m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//////////////////////////////////	클라이언트<->툴 변경작업 ///////////////////////////////////////////////////////
	if (nullptr == m_pTextureCom_Tool)
		m_pTextureCom->Set_Texture(m_iTerrainIdx);	// 텍스처 정보 세팅을 우선적으로 한다.
	else
		m_pTextureCom_Tool->Set_Texture(m_iTerrainIdx);
	//////////////////////////////////	클라이언트<->툴 변경작업 ///////////////////////////////////////////////////////

	FAILED_CHECK_RETURN(Set_Material(), );

	m_pBufferCom->Render_Buffer();

	if (m_bWireFrame)
		m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
}

HRESULT CTerrain::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CTerrainTex*>(Clone_Proto(L"Proto_TerrainTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_TerrainTexCom", pComponent });

	//////////////////////////////////	클라이언트<->툴 변경작업 ///////////////////////////////////////////////////////
	try
	{	//// 맵툴 사용시 해당 컴포넌트 추가
		pComponent = m_pTextureCom_Tool = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_TerrainTexCom_MapTool"));
		if (nullptr == pComponent)
			throw - 1;
		m_mapComponent[ID_STATIC].insert({ L"Proto_TerrainTexCom_MapTool", pComponent });
	}
	catch (int expn)
	{
		/*pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_TerrainTexture_Stage_1"));
		NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
		m_mapComponent[ID_STATIC].insert({ L"Proto_TerrainTexture_Stage_1", pComponent });*/

		pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_TerrainTexture_Stage_1"));
		NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
		m_mapComponent[ID_STATIC].insert({ L"Proto_TerrainTexture_Stage_1", pComponent });
	}
	//////////////////////////////////	클라이언트<->툴 변경작업 ///////////////////////////////////////////////////////

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	return S_OK;
}

HRESULT CTerrain::Set_Material(void)
{
	D3DMATERIAL9 Material;
	ZeroMemory(&Material, sizeof(D3DMATERIAL9));

	Material.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	Material.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	Material.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.f);
	Material.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
	Material.Power = 0.f;

	m_pGraphicDev->SetMaterial(&Material);

	return S_OK;
}

CTerrain * CTerrain::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerrain *	pInstance = new CTerrain(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CTerrain::Free(void)
{
	CGameObject::Free();
}
