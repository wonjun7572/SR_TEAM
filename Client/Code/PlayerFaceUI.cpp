#include "stdafx.h"
#include "PlayerFaceUI.h"

#include "Export_Function.h"
#include "CubePlayer.h"

CPlayerFaceUI::CPlayerFaceUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}


CPlayerFaceUI::~CPlayerFaceUI()
{
}

HRESULT CPlayerFaceUI::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	if (m_pPlayer == nullptr)
		m_pPlayer = Engine::Get_GameObject(STAGE_CHARACTER,L"PLAYER");

	return S_OK;
}

_int CPlayerFaceUI::Update_Object(const _float & fTimeDelta)
{
	if (m_pPlayer == nullptr)
		m_pPlayer = Engine::Get_GameObject(STAGE_CHARACTER, L"PLAYER");
	
	m_fFrame += 5.f * fTimeDelta * 0.2f;

	if (m_fFrame >= 5.f)
		m_fFrame = 0.f;

	_int iResult = CGameObject::Update_Object(fTimeDelta);

	Add_RenderGroup(RENDER_UI, this);

	return iResult;
}

void CPlayerFaceUI::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CPlayerFaceUI::Render_Object(void)
{
	Begin_OrthoProj();
	
	if (dynamic_cast<CCubePlayer*>(m_pPlayer)->Get_Ability()->iHp > 75)
	{
		m_pTexture_100->Set_Texture((_ulong)m_fFrame);
	}
	else if (dynamic_cast<CCubePlayer*>(m_pPlayer)->Get_Ability()->iHp <= 75 &&
		dynamic_cast<CCubePlayer*>(m_pPlayer)->Get_Ability()->iHp > 50)
	{
		m_pTexture_75->Set_Texture((_ulong)m_fFrame);
	}
	else if (dynamic_cast<CCubePlayer*>(m_pPlayer)->Get_Ability()->iHp <= 50 &&
		dynamic_cast<CCubePlayer*>(m_pPlayer)->Get_Ability()->iHp > 25)
	{
		m_pTexture_50->Set_Texture((_ulong)m_fFrame);
	}
	else if (dynamic_cast<CCubePlayer*>(m_pPlayer)->Get_Ability()->iHp <= 25 &&
		dynamic_cast<CCubePlayer*>(m_pPlayer)->Get_Ability()->iHp > 1)
	{
		m_pTexture_25->Set_Texture((_ulong)m_fFrame);
	}
	else if (dynamic_cast<CCubePlayer*>(m_pPlayer)->Get_Ability()->iHp <= 0)
	{
		m_pTexture_0->Set_Texture(0);
	}

	m_pBufferCom->Render_Buffer();
	End_OrthoProj();
}

void CPlayerFaceUI::Begin_OrthoProj()
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

	matView.m[0][0] = 75.f; // 이미지 가로
	matView.m[1][1] = 75.f; // 이미지 세로
	matView.m[2][2] = 1.f;
	matView.m[3][0] = m_pTransCom->m_vInfo[INFO_POS].x - 730.f;
	matView.m[3][1] = m_pTransCom->m_vInfo[INFO_POS].y - 375.f;

	D3DXMatrixOrthoLH(&matOrtho, WINCX, WINCY, 0.f, 1.f);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matOrtho);
}

void CPlayerFaceUI::End_OrthoProj()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

HRESULT CPlayerFaceUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pTexture_100 = dynamic_cast<CTexture*>(Clone_Proto(L"HP_100_Face"));
	NULL_CHECK_RETURN(m_pTexture_100, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"HP_100_Face", pComponent });

	pComponent = m_pTexture_75 = dynamic_cast<CTexture*>(Clone_Proto(L"HP_75_Face"));
	NULL_CHECK_RETURN(m_pTexture_75, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"HP_75_Face", pComponent });

	pComponent = m_pTexture_50 = dynamic_cast<CTexture*>(Clone_Proto(L"HP_50_Face"));
	NULL_CHECK_RETURN(m_pTexture_50, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"HP_50_Face", pComponent });

	pComponent = m_pTexture_25 = dynamic_cast<CTexture*>(Clone_Proto(L"HP_25_Face"));
	NULL_CHECK_RETURN(m_pTexture_25, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"HP_25_Face", pComponent });

	pComponent = m_pTexture_0 = dynamic_cast<CTexture*>(Clone_Proto(L"HP_0_Face"));
	NULL_CHECK_RETURN(m_pTexture_0, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"HP_0_Face", pComponent });

	return S_OK;
}

CPlayerFaceUI * CPlayerFaceUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayerFaceUI *	pInstance = new CPlayerFaceUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CPlayerFaceUI::Free(void)
{
	CGameObject::Free();
}
