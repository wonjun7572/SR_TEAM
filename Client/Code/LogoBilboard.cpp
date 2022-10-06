#include "stdafx.h"
#include "..\Header\LogoBilboard.h"


CLogoBilboard::CLogoBilboard(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}


CLogoBilboard::~CLogoBilboard()
{
}

HRESULT CLogoBilboard::Ready_Object(const _vec3& vPos)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransCom->Set_Scale(2.3f, 5.6f, 0.f);
	m_pTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);

	return S_OK;
}

_int CLogoBilboard::Update_Object(const _float & fTimeDelta)
{
	m_pTransCom->Billboard_Transform(fTimeDelta);

	Engine::CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CLogoBilboard::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();

}

void CLogoBilboard::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0xcc);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

HRESULT CLogoBilboard::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(RCTEX_COMP));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ RCTEX_COMP, pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_LogoBil"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_LogoBil", pComponent });

	return S_OK;
}

CLogoBilboard * CLogoBilboard::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos)
{
	CLogoBilboard* pInstance = new CLogoBilboard(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CLogoBilboard::Free(void)
{
	CGameObject::Free();
}
