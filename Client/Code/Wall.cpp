#include "stdafx.h"
#include "..\Header\Wall.h"
#include "Export_Function.h"

USING(Engine)

CWall::CWall(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
	, m_dwWallTextureNum(0)
{
}

CWall::~CWall()
{
}

HRESULT CWall::Ready_Object(_ulong Texture, _vec3 * Position)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_dwWallTextureNum = Texture;
	m_pTransform->Set_Pos(Position->x, 0.5f, Position->z);

	return S_OK;
}

_int CWall::Update_Object(const _float & fTimeDelta)
{
	Add_RenderGroup(RENDER_NONALPHA, this);

	_uint iResult = CGameObject::Update_Object(fTimeDelta);

	return iResult;
}

void CWall::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CWall::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	m_pTexture->Set_Texture(m_dwWallTextureNum);
	m_pCubeTex->Render_Buffer();
}

HRESULT CWall::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	pComponent = m_pCubeTex = dynamic_cast<CCubeTex*>(Engine::Clone_Proto(L"Proto_CubeTexCom"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubeTexCom", pComponent });

	pComponent = m_pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_CubePlayerTexture"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubePlayerTexture", pComponent });

	return S_OK;
}

CWall * CWall::Create(LPDIRECT3DDEVICE9 pGraphicDev, _ulong Texture, _vec3 * Position)
{
	CWall*	pInstance = new CWall(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(Texture, Position)))
	{
		MSG_BOX("Wall Object Create Fail");
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CWall::Free(void)
{
	CGameObject::Free();
}
