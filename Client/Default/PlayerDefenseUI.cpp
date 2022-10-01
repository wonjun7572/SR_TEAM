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
	//FONT
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"DEFENSE", L"Electronic Highway Sign", 5, 10, FW_NORMAL), E_FAIL);
	return S_OK;
}

_int CPlayerDefenseUI::Update_Object(const _float & fTimeDelta)
{
	_int iResult = CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);
	if (m_pPlayer == nullptr)
		m_pPlayer = Engine::Get_GameObject(L"Layer_Character", L"PLAYER");

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
	Begin_OrthoProj();
	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Resize_Buffer(m_iDefense * 0.01f);
	m_pBufferCom->Render_Buffer();
	End_OrthoProj();
	Render_Font(L"HP", m_strDefense.c_str(), &(_vec2(182.f, 832.f)), D3DXCOLOR(0.5f, 0.5f, 0.3f, 1.f));
}

void CPlayerDefenseUI::Begin_OrthoProj()
{
	_matrix matWorld, matView, matProj, matOrtho;
	m_pGraphicDev->GetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	memcpy(&m_matWorld, &matWorld, sizeof(_matrix));
	memcpy(&m_matView, &matView, sizeof(_matrix));
	memcpy(&m_matProj, &matProj, sizeof(_matrix));

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	matView.m[0][0] = 85.f; // 이미지 가로
	matView.m[1][1] = 9.f;   // 이미지 세로
	matView.m[2][2] = 1.f;
	matView.m[3][0] = m_pTransCom->m_vInfo[INFO_POS].x - 460.f;
	matView.m[3][1] = m_pTransCom->m_vInfo[INFO_POS].y - 390.f;

	D3DXMatrixOrthoLH(&matOrtho, WINCX, WINCY, 0.f, 1.f);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matOrtho);
}

void CPlayerDefenseUI::End_OrthoProj()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
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
	CPlayerDefenseUI*	pInstance = new CPlayerDefenseUI(pGraphicDev);

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
