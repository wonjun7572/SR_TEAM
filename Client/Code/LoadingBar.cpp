#include "stdafx.h"
#include "..\Header\LoadingBar.h"


CLoadingBar::CLoadingBar(LPDIRECT3DDEVICE9 pGraphicDev, wstring wstrTex, _vec3 vPos, _float fScale, _int iPivot, _float fLoad)\
	:Engine::CGameObject(pGraphicDev),
	m_vPos(vPos),
	m_fScale(fScale),
	m_iPivot(iPivot),
	m_wstrTexture(wstrTex),
	m_fLoad(fLoad)
{
	D3DXMatrixIdentity(&m_MatWorld);
	D3DXMatrixIdentity(&m_MatView);
}


CLoadingBar::~CLoadingBar()
{
}

void CLoadingBar::Set_Load(const float & fLoad)
{
	m_fLoad = fLoad;
}

HRESULT CLoadingBar::Ready_Object()
{

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	CalculateTransform();

	return S_OK;
}

_int CLoadingBar::Update_Object(const _float & fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	m_pRendererCom->Add_RenderGroup(Engine::RENDER_UI, this);




	return 0;
}

void CLoadingBar::Render_Object(void)
{

	_matrix mat_OldWolrd, mat_OldView, mat_Perpective;
	//const Engine::_matrix* mat_Oroth = dynamic_cast<Engine::CCamera*>(m_pCamera)->Get_Ortho();

	////Back up Preivous Value
	m_pGraphicDev->GetTransform(D3DTS_WORLD, &mat_OldWolrd);
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &mat_OldView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &mat_Perpective);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_MatView);

	//Set Alpha Test
	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//Render UI
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pTextureCom->Render_Texture();
	m_pBufferCom->SendToClient(0.0f, m_fLoad, 0.0f, 1.0f);
	//m_pBufferCom->SendToClient();
	m_pBufferCom->Render_Buffer();


	//Revert Previous Value
	m_pBufferCom->SendToClient(0.0f, 1.0f, 0.0f, 1.0f);


	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &mat_OldWolrd);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &mat_OldView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &mat_Perpective);


}

HRESULT CLoadingBar::Add_Component(void)
{
	return S_OK;
}

void CLoadingBar::CalculateTransform()
{
}

void CLoadingBar::SetPivot()
{
}

void CLoadingBar::SetScale()
{
}

void CLoadingBar::SetPos()
{
}

CLoadingBar * CLoadingBar::Create(LPDIRECT3DDEVICE9 pGraphicDev, wstring wstrTex, _vec3 vPos, _float fScale, _int iPivot, _float Load)
{
	return nullptr;
}

void CLoadingBar::Free(void)
{
}
