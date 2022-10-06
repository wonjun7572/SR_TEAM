#include "stdafx.h"
#include "..\Header\ExitButton.h"


CExitButton::CExitButton(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}


CExitButton::~CExitButton()
{
}

HRESULT CExitButton::Ready_Object()
{
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"ExitFont", L"Roboto-Bold", 37, 30, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_pTransformCom->Set_Scale(0.28f, 0.11f, 0.f);
	m_pTransformCom->Set_Pos(0.65f, -0.2f, 0.f);
	m_strEB = L"Exit Game";

	return S_OK;
}

_int CExitButton::Update_Object(const _float & fTimeDelta)
{
	if (PointMouse())
	{
		if (Get_DIMouseState(DIM_LB) & 0x80)
			Mouse_check = true;
	}

	Engine::CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);
	return 0;
}

void CExitButton::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CExitButton::Render_Object(void)
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
	Render_Font(L"ExitFont", m_strEB.c_str(), &_vec2(1150.f, 530.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	End_OrthoProj();


}


HRESULT CExitButton::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pRcTexCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pRcTexCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_ExitButton"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_ExitButton", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	return S_OK;
}

void CExitButton::Begin_OrthoProj()
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

	matView.m[0][0] = 500.f; // 이미지 가로
	matView.m[1][1] = 100.f; // 이미지 세로
	matView.m[2][2] = 1.f;
	matView.m[3][0] = m_pTransformCom->m_vInfo[INFO_POS].x + 550.f;
	matView.m[3][1] = m_pTransformCom->m_vInfo[INFO_POS].y + -100.f;

	D3DXMatrixOrthoLH(&matOrtho, WINCX, WINCY, 0.f, 1.f);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matOrtho);
}

void CExitButton::End_OrthoProj()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

_bool CExitButton::PointMouse(void)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	_long lLeft, lRight, lUp, lDown;

	lLeft = _long((0.5 * WINCX) * (1 + m_pTransformCom->m_vInfo[INFO_POS].x) - (m_pTransformCom->m_vScale.x  * (0.5 * WINCX)));
	lRight = _long((0.5 * WINCX) * (1 + m_pTransformCom->m_vInfo[INFO_POS].x) + (m_pTransformCom->m_vScale.x  * (0.5 * WINCX)));
	lUp = _long((0.5 * WINCY) * (1 - m_pTransformCom->m_vInfo[INFO_POS].y) - (m_pTransformCom->m_vScale.y  * (WINCY * 0.5)));
	lDown = _long((0.5 * WINCY) * (1 - m_pTransformCom->m_vInfo[INFO_POS].y) + (m_pTransformCom->m_vScale.y  * (WINCY * 0.5)));

	RECT rc = { lLeft, lUp, lRight, lDown };

	if (PtInRect(&rc, pt))
	{
		return true;
	}

	return false;
}

CExitButton * CExitButton::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CExitButton* pInsatnce = new CExitButton(pGraphicDev);

	if (FAILED(pInsatnce->Ready_Object()))
	{
		Safe_Release(pInsatnce);
		return nullptr;
	}

	return pInsatnce;
}

void CExitButton::Free(void)
{
	CGameObject::Free();
}