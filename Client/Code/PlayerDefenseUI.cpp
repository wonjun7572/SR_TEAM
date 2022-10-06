#include "stdafx.h"
#include "PlayerDefenseUI.h"

#include "Export_Function.h"
#include "CubePlayer.h"

CPlayerDefenseUI::CPlayerDefenseUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CPlayerDefenseUI::~CPlayerDefenseUI()
{
}

HRESULT CPlayerDefenseUI::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	D3DXMatrixOrthoLH(&m_ProjMatrix, WINCX, WINCY, 0.f, 1.f);

	m_fX = -492.f;
	m_fY = 386.f;
	m_fSizeX = 115.8f;
	m_fSizeY = 20.4f;

	//FONT
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"DEFENSE", L"Electronic Highway Sign", 15, 20, FW_NORMAL), E_FAIL);
	return S_OK;
}

_int CPlayerDefenseUI::Update_Object(const _float & fTimeDelta)
{
	m_pTransCom->Set_Scale(m_fSizeX, m_fSizeY, 1.f);
	m_pTransCom->Set_Pos(m_fX, -m_fY, 0.f);
	_int iResult = CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);
	if (m_pPlayer == nullptr)
		m_pPlayer = Engine::Get_GameObject(STAGE_CHARACTER, L"PLAYER");

	if (m_pPlayer != nullptr)
	{
		m_iDefense = dynamic_cast<CCubePlayer*>(m_pPlayer)->Get_Ability()->iDefence;
		m_strDefense = to_wstring(m_iDefense);
	}

	return iResult;
}

void CPlayerDefenseUI::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CPlayerDefenseUI::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	_matrix      OldViewMatrix, OldProjMatrix;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &OldViewMatrix);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &OldProjMatrix);

	_matrix      ViewMatrix;

	ViewMatrix = *D3DXMatrixIdentity(&ViewMatrix);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &ViewMatrix);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Resize_Buffer(m_iDefense * 0.01f);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &OldViewMatrix);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &OldProjMatrix);

	Render_Font(L"HP", m_strDefense.c_str(), &(_vec2(176.5f, 827.2f)), D3DXCOLOR(0.5f, 0.5f, 0.3f, 1.f));
}



HRESULT CPlayerDefenseUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"RcTex_Defense"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"RcTex_Defense", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"DEFENSE_Gage"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"DEFENSE_Gage", pComponent });

	return S_OK;
}

CPlayerDefenseUI * CPlayerDefenseUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayerDefenseUI*   pInstance = new CPlayerDefenseUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CPlayerDefenseUI::Free(void)
{
	CGameObject::Free();
}