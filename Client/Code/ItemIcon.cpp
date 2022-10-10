#include "stdafx.h"
#include "Inventory.h"
#include "Shop.h"
#include "..\Header\ItemIcon.h"

static _int iIconCnt = 0;

CItemIcon::CItemIcon(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CItemIcon::~CItemIcon()
{

}

HRESULT CItemIcon::Ready_Object(_int iIndex)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_iNumber = iIndex;
	wsprintf(szCntName, L"Contents_%d", iIconCnt);
	iIconCnt++;

	return S_OK;
}

_int CItemIcon::Update_Object(const _float & fTimeDelta)
{
	if (m_bDead)
	{
		return -1;
	}
	CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);

	Index();
	FixOnCursor();
	return 0;
}

void CItemIcon::LateUpdate_Object(void)
{

}

void CItemIcon::Render_Object(void)
{
	if (dynamic_cast<CInventory*>(Engine::Get_GameObject(STAGE_UI, L"InventoryUI"))->Get_Switch() && m_iNumber != 0)
	{
		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		m_pTextureCom->Set_Texture(m_iTexIndex);

		Begin_OrthoProj();
		m_pRcTexCom->Render_Buffer();
		End_OrthoProj();

		m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	}
	if (m_iNumber == 0)
	{
		if (dynamic_cast<CInventory*>(Engine::Get_GameObject(STAGE_UI, L"InventoryUI"))->Get_Switch() || dynamic_cast<CShop*>(Engine::Get_GameObject(STAGE_UI, L"Shop"))->Get_Switch())
		{
			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

			if (m_iNumber == 0)
				m_pTextureCom->Set_Texture(0);
			Begin_OrthoProj();
			m_pRcTexCom->Render_Buffer();
			End_OrthoProj();

			m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		}
	}
}


HRESULT CItemIcon::Add_Component()
{
	CComponent* pComponent = nullptr;


	pComponent = m_pRcTexCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pRcTexCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_ItemIconTexture"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_ItemIconTexture", pComponent });

	return S_OK;
}

void CItemIcon::Begin_OrthoProj()
{

	m_pTransformCom->Get_Info(INFO_POS, &m_vIconPos);

	_matrix matWorld, matView, matProj, matOrtho;
	m_pGraphicDev->GetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	memcpy(&m_matWorld, &matWorld, sizeof(_matrix));
	memcpy(&m_matView, &matView, sizeof(_matrix));
	memcpy(&m_matProj, &matProj, sizeof(_matrix));

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	matView.m[0][0] = m_fImgX * WINCX / WINCY; // 이미지 가로
	matView.m[1][1] = m_fImgY * WINCY / WINCY;   // 이미지 세로
	matView.m[2][2] = 1.f;
	matView.m[3][0] = m_vBlockPos.x * (WINCX / WINCY);
	matView.m[3][1] = m_vBlockPos.y * (WINCX / WINCY);
	matView.m[3][2] = m_fImgZ;


	D3DXMatrixOrthoLH(&matOrtho, WINCX, WINCY, 0.f, 1.f);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matOrtho);
}

void CItemIcon::End_OrthoProj()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void CItemIcon::Index()
{
	if (m_iNumber == 0)				//커서
	{
		m_iTexIndex = m_iNumber;
		m_fImgX = 30.f;
		m_fImgY = 50.f;
		m_fImgZ = 0.f;
		cout << iIconCnt << " " << endl;
	}
	if (m_iNumber == 1)				 //아이템
	{
		m_iTexIndex = m_iNumber;
		m_fImgX = 20.f;
		m_fImgY = 60.f;
	}

	if (m_iNumber == 2)				//uzi
	{
		m_iTexIndex = m_iNumber;
		m_fImgX = 20.f;
		m_fImgY = 60.f;
	}
	if (m_iNumber == 3)				//Shotgun
	{
		m_iTexIndex = m_iNumber;
		m_fImgX = 20.f;
		m_fImgY = 60.f;
	}

	if (m_iNumber == 4)				//Sniper
	{
		m_iTexIndex = m_iNumber;
		m_fImgX = 20.f;
		m_fImgY = 60.f;
	}
	if (m_iNumber == 5)			//두번째 버튼
	{
		m_iTexIndex = m_iNumber;
		m_fImgX = 20.f;
		m_fImgY = 60.f;

	}
	if(m_iNumber == 6)			//세번째 버튼
	{
		m_iTexIndex = m_iNumber;
		m_fImgX = 20.f;
		m_fImgY = 60.f;
	}
	if(m_iNumber == 7)			//네번쨰 버튼 
	{
		m_iTexIndex = m_iNumber;
		m_fImgX = 20.f;
		m_fImgY = 60.f;
	}
}

void CItemIcon::FixOnCursor()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	if (m_bFix)
	{
		m_vBlockPos.x = -WINCX / 2 + pt.x;//(double)( 1.75*(-450 +(pt.x*WINCY/WINCX)));
		m_vBlockPos.y = WINCY / 2 - pt.y;// (double)(1.75 * (250 - (pt.y*WINCY / WINCX)));
	}
	if (m_iNumber == 0)
	{
		m_vBlockPos.x = 15.f - WINCX / 2 + pt.x;//(double)( 1.75*(-450 +(pt.x*WINCY/WINCX)));
		m_vBlockPos.y = -25.f + WINCY / 2 - pt.y;// (double)(1.75 * (250 - (pt.y*WINCY / WINCX)));
	}
}

CItemIcon * CItemIcon::Create(LPDIRECT3DDEVICE9 pGraphicDev, _int iIndex)
{
	CItemIcon*   pInstance = new CItemIcon(pGraphicDev);
	if (FAILED(pInstance->Ready_Object(iIndex)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	pInstance->Maker(pInstance);
	return pInstance;
}

void CItemIcon::Free(void)
{
	CGameObject::Free();
}