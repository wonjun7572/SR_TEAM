#include "stdafx.h"
#include "..\Header\OptionButton.h"
#include "Export_Function.h"
#include "ToolScene.h"

COptionButton::COptionButton(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

COptionButton::~COptionButton()
{
}

HRESULT COptionButton::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"OptionButton", L"Roboto-Bold", 30, 30, FW_NORMAL), E_FAIL);
	m_strOB = L"Option Button";

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_pTransformCom->Set_Scale(0.28f, 0.12f, 0.f);
	m_pTransformCom->Set_Pos(0.65f, 0.12f, 0.f);
	return S_OK;
}

_int COptionButton::Update_Object(const _float & fTimeDelta)
{
	if (PointMouse())
	{
		if (Get_DIMouseState(DIM_LB) & 0x80)
		{
			Mouse_check = true;
			return 0;
		}
	}

	Engine::CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);

	return 0;
}

void COptionButton::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void COptionButton::Render_Object(void)
{
	
	Begin_OrthoProj();
	m_iIndex = 0;
	m_pTextureCom->Set_Texture(m_iIndex);

	if (PointMouse())
	{
		{
			if (Checking = true)
			{
				m_iIndex = 1;
				m_pTextureCom->Set_Texture(m_iIndex);
			}
		}
	}


	m_pRcTexCom->Render_Buffer();

	Render_Font(L"OptionButton", m_strOB.c_str(), &_vec2(1130.f, 380.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	End_OrthoProj();
}

HRESULT COptionButton::Add_Component(void)
{
	CComponent* pComponent = nullptr;
	
	pComponent = m_pRcTexCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pRcTexCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_OptionButton"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_OptionButton", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	return S_OK;
}

void COptionButton::Begin_OrthoProj()
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

	matView.m[0][0] = 250.f; // 이미지 가로
	matView.m[1][1] = 50.f; // 이미지 세로
	matView.m[2][2] = 1.f;
	matView.m[3][0] = m_pTransformCom->m_vInfo[INFO_POS].x + 550.f;
	matView.m[3][1] = m_pTransformCom->m_vInfo[INFO_POS].y + 50.f;

	D3DXMatrixOrthoLH(&matOrtho, WINCX, WINCY, 0.f, 1.f);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matOrtho);
}

void COptionButton::End_OrthoProj()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

COptionButton * COptionButton::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	COptionButton* pInstance = new COptionButton(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

_bool COptionButton::PointMouse(void)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	_long lLeft, lRight, lUp, lDown;

	lLeft  = _long((0.5 * WINCX) * (1 + m_pTransformCom->m_vInfo[INFO_POS].x) - (m_pTransformCom->m_vScale.x * (0.5 * WINCX)));
	lRight = _long((0.5 * WINCX) * (1 + m_pTransformCom->m_vInfo[INFO_POS].x) + (m_pTransformCom->m_vScale.x * (0.5 * WINCX)));
	lUp    = _long((0.5 * WINCY) * (1 - m_pTransformCom->m_vInfo[INFO_POS].y) - (m_pTransformCom->m_vScale.y * (WINCY * 0.5)));
	lDown  = _long((0.5 * WINCY) * (1 - m_pTransformCom->m_vInfo[INFO_POS].y) + (m_pTransformCom->m_vScale.y * (WINCY * 0.5)));

	RECT rc = { lLeft, lUp, lRight, lDown };

	if (PtInRect(&rc, pt))
	{
		return true;
	}

	return false;
}

void COptionButton::Free(void)
{
	CGameObject::Free();
}
