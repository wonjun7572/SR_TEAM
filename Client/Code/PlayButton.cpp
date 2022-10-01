#include "stdafx.h"
#include "..\Header\PlayButton.h"

#include "Export_Function.h"
#include "Stage.h"
 
CPlayButton::CPlayButton(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CPlayButton::~CPlayButton()
{
}

HRESULT CPlayButton::Ready_Object()
{
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"PlayButtontFont", L"Roboto-Bold", 36, 30, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_TranformCom->Set_Scale(0.28f, 0.1f, 0.f);
	m_TranformCom->Set_Pos(0.65f, 0.45f, 0.f);
	m_strPB = L"New Game";

	return S_OK;
}

_int CPlayButton::Update_Object(const _float & fTimeDelta)
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

void CPlayButton::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CPlayButton::Render_Object(void)
{
	Begin_OrthoProj();
	m_iIndex = 0;
	m_TextureCom->Set_Texture(m_iIndex);

	if (PointMouse())
	{
		{
			if (Checking = true)
			{
				m_iIndex = 1;
				m_TextureCom->Set_Texture(m_iIndex);
			}
		}
	}
	m_RcTexCom->Render_Buffer();
	Render_Font(L"PlayButtontFont", m_strPB.c_str(), &_vec2(1150.f, 230.f), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	End_OrthoProj();
}

HRESULT CPlayButton::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_RcTexCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_RcTexCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pComponent });

	pComponent = m_TextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_ButtonPlayTexture"));
	NULL_CHECK_RETURN(m_TextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_ButtonPlayTexture", pComponent });


	//pComponent = m_CheckTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_CheckPlayTexture"));
	//NULL_CHECK_RETURN(m_CheckTextureCom, E_FAIL);
	//m_mapComponent[ID_STATIC].insert({ L"Proto_CheckPlayTexture", pComponent });

	pComponent = m_TranformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_TranformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	return S_OK;
}

void CPlayButton::Begin_OrthoProj()
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
	matView.m[3][0] = m_TranformCom->m_vInfo[INFO_POS].x + 550.f;
	matView.m[3][1] = m_TranformCom->m_vInfo[INFO_POS].y + 200.f;

	D3DXMatrixOrthoLH(&matOrtho, WINCX, WINCY, 0.f, 1.f);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matOrtho);
}

void CPlayButton::End_OrthoProj()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

CPlayButton * CPlayButton::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayButton* pInsatnce = new CPlayButton(pGraphicDev);

	if (FAILED(pInsatnce->Ready_Object()))
	{
		Safe_Release(pInsatnce);
		return nullptr;
	}

	return pInsatnce;
}

_bool CPlayButton::PointMouse(void)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	_long lLeft, lRight, lUp, lDown;

	lLeft  = _long((0.5 * WINCX) * (1 + m_TranformCom->m_vInfo[INFO_POS].x) - (m_TranformCom->m_vScale.x  * (0.5 * WINCX)));
	lRight = _long((0.5 * WINCX) * (1 + m_TranformCom->m_vInfo[INFO_POS].x) + (m_TranformCom->m_vScale.x  * (0.5 * WINCX)));
	lUp    = _long((0.5 * WINCY) * (1 - m_TranformCom->m_vInfo[INFO_POS].y) - (m_TranformCom->m_vScale.y  * (WINCY * 0.5)));
	lDown  = _long((0.5 * WINCY) * (1 - m_TranformCom->m_vInfo[INFO_POS].y) + (m_TranformCom->m_vScale.y  * (WINCY * 0.5)));

	RECT rc = { lLeft, lUp, lRight, lDown };

	if (PtInRect(&rc, pt))
	{
		return true;
	}

	return false;
}

void CPlayButton::Free(void)
{
	CGameObject::Free();
}
