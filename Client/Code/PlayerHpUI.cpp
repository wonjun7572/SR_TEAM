#include "stdafx.h"
#include "..\Header\PlayerHpUI.h"

#include "Export_Function.h"
#include "CubePlayer.h"

CPlayerHpUI::CPlayerHpUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CPlayerHpUI::~CPlayerHpUI()
{

}

HRESULT CPlayerHpUI::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	D3DXMatrixOrthoLH(&m_ProjMatrix, WINCX, WINCY, 0.f, 1.f);

	m_fX = -479.f;
	m_fY = 428.f;
	m_fSizeX = 139.8f;
	m_fSizeY = 21.f;

	//FONT
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"HP", L"Electronic Highway Sign", 10, 15, FW_NORMAL), E_FAIL);
	return S_OK;
}

_int CPlayerHpUI::Update_Object(const _float & fTimeDelta)
{

	m_pTransCom->Set_Scale(m_fSizeX, m_fSizeY, 1.f);
	m_pTransCom->Set_Pos(m_fX, -m_fY, 0.f);

	_int iResult = CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);
	if (m_pPlayer == nullptr)
		m_pPlayer = Engine::Get_GameObject(STAGE_CHARACTER, L"PLAYER");

	if (m_pPlayer != nullptr)
	{
		m_iHp = dynamic_cast<CCubePlayer*>(m_pPlayer)->Get_Ability()->iHp;
		m_strHp = to_wstring(m_iHp);
	}

	return iResult;
}

void CPlayerHpUI::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CPlayerHpUI::Render_Object(void)
{

	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());


	_matrix      OldViewMatrix, OldProjMatrix;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &OldViewMatrix);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &OldProjMatrix);

	_matrix      ViewMatrix;

	ViewMatrix = *D3DXMatrixIdentity(&ViewMatrix);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &ViewMatrix);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);
	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Resize_Buffer(m_iHp * 0.01f);
	m_pBufferCom->Render_Buffer();


	m_pGraphicDev->SetTransform(D3DTS_VIEW, &OldViewMatrix);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &OldProjMatrix);

	Render_Font(L"HP", m_strHp.c_str(), &(_vec2(176.5f, 870.f)), D3DXCOLOR(0.5f, 0.5f, 0.3f, 1.f));
}

HRESULT CPlayerHpUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"RcTex_HP"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"RcTex_HP", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"HP_Gage"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"HP_Gage", pComponent });

	return S_OK;
}

CPlayerHpUI * CPlayerHpUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayerHpUI*   pInstance = new CPlayerHpUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CPlayerHpUI::Free(void)
{
	CGameObject::Free();
}