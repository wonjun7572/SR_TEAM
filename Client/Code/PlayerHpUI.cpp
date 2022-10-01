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
	//FONT
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"HP", L"Electronic Highway Sign", 5, 10, FW_NORMAL), E_FAIL);
	return S_OK;
}

_int CPlayerHpUI::Update_Object(const _float & fTimeDelta)
{
	_int iResult = CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);
	if (m_pPlayer == nullptr)
		m_pPlayer = Engine::Get_GameObject(L"Layer_Character", L"PLAYER");

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
	Begin_OrthoProj();
	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Resize_Buffer(m_iHp * 0.01f);
	m_pBufferCom->Render_Buffer();
	End_OrthoProj();
	Render_Font(L"HP", m_strHp.c_str(), &(_vec2(182.f, 872.f)), D3DXCOLOR(0.5f, 0.5f, 0.3f, 1.f));
}

void CPlayerHpUI::Begin_OrthoProj()
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

	matView.m[0][0] = 100.f; // 이미지 가로
	matView.m[1][1] = 8.f;   // 이미지 세로
	matView.m[2][2] = 1.f;
	matView.m[3][0] = m_pTransCom->m_vInfo[INFO_POS].x - 440.f;
	matView.m[3][1] = m_pTransCom->m_vInfo[INFO_POS].y - 425.f;

	D3DXMatrixOrthoLH(&matOrtho, WINCX, WINCY, 0.f, 1.f);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matOrtho);
}

void CPlayerHpUI::End_OrthoProj()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
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
	CPlayerHpUI*	pInstance = new CPlayerHpUI(pGraphicDev);

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
