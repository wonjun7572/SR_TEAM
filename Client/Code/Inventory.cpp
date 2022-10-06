#include "stdafx.h"
#include "..\Header\Inventory.h"


CInventory::CInventory(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CInventory::~CInventory()
{
}

HRESULT CInventory::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_iItemCnt = 0;
	m_vecContents.reserve(25);
	for (_int i = 0; i < 25; i++)
	{
		m_vecContents.push_back(nullptr);
		m_vecContents[i] = nullptr;
	}
	m_vecEquipments.reserve(5);
	for (_int i = 0 ; i < 5; i++)
	{
		m_vecEquipments.push_back(nullptr);
		m_vecEquipments[i] = nullptr;
	}

	return S_OK;
}

_int CInventory::Update_Object(const _float & fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);
	Sorting();
	Mouse();
	Key_Input();
	Equipment();
	return 0;
}

void CInventory::LateUpdate_Object(void)
{	
	if (!m_bInit)
	{
		m_bInit = true;
		CItemIcon* pGameObject = CItemIcon::Create(m_pGraphicDev, 0);
	}

}

void CInventory::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrixPointer());

	if (m_bInvSwitch)
	{
		m_pTextureCom->Set_Texture(0);

		Begin_OrthoProj();
		m_pRcTexCom->Render_Buffer();
		End_OrthoProj();
	}
}

HRESULT CInventory::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pRcTexCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pRcTexCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_InventoryTexture"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_InventoryTexture", pComponent });
		
	return S_OK;
}

void CInventory::Begin_OrthoProj()
{
	_float InvPosX = 400.f;
	_float InvPosY = 50.f;
	_matrix matWorld, matView, matProj, matOrtho;
	m_pGraphicDev->GetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	memcpy(&m_matWorld, &matWorld, sizeof(_matrix));
	memcpy(&m_matView, &matView, sizeof(_matrix));
	memcpy(&m_matProj, &matProj, sizeof(_matrix));

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	matView.m[0][0] = WINCX/3.f; // 이미지 가로
	matView.m[1][1] = WINCY/1.75f;   // 이미지 세로
	matView.m[2][2] = 1.f;
	matView.m[3][0] = InvPosX; //* (WINCX / WINCY);
	matView.m[3][1] = InvPosY; //* (WINCX / WINCY);
	matView.m[3][2] = 0.003f;
	D3DXMatrixOrthoLH(&matOrtho, WINCX, WINCY, 0.f, 1.f);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matOrtho);
}

void CInventory::End_OrthoProj()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
}


void CInventory::Get_Item()
{
}
void CInventory::Sorting()
{
	//m_vecContents.shrink_to_fit();
	if (Get_DIKeyState(DIK_V) && m_iItemCnt<27)
	{
		//생성
		m_pItemIcon = CItemIcon::Create(m_pGraphicDev, 1);
		m_vecContents.push_back(m_pItemIcon);
		m_iItemCnt++;
		m_bSorting = true;
		m_bNullSorting = true;
		//제거
		//dynamic_cast<CItemIcon*>(iter)->Kill_Obj();
		//iter = nullptr;
		//인덱스변경
		//dynamic_cast<CItemIcon*>(iter)->Set_Texture(0);
	}
	
	_vec3	vPos;
	_int	iCnt = 0;
	CGameObject* pGameObject = nullptr;
	if (m_bSorting)
	{
		for (auto& iter : m_vecContents)
		{
			if (iter != nullptr ) // 위치 지정
			{
				_float fDefaultX = 175.f;
				_float fDefaultY = 75.f;
				_float fIntervalX = (50.f) * (iCnt % 9);
				_float fIntervalY = (67.5f) * (iCnt / 9);
				dynamic_cast<CItemIcon*>(iter)->Set_block(fDefaultX + fIntervalX, fDefaultY - fIntervalY, 0.f);
			}
			
			if (m_bNullSorting&& iter != m_vecContents.back() && iter == nullptr && m_vecContents.back() != nullptr) // 빈곳부터 채우기
			{
				iter = m_vecContents.back();
				m_bNull = true;
				m_bNullSorting = false;
				break;
			}
			iCnt++;
			iCnt %= 27;
		}
	}
	if (m_bNull)
	{
		m_vecContents.pop_back();
		m_bNull = false;		
	}
}


void CInventory::Key_Input()
{	
	if (Get_DIKeyState(DIK_I))
	{
		if (m_bKeyDown)
		{
			m_bKeyDown = false;
			if (true == m_bInvSwitch)
			{
				m_bInvSwitch = false;				
			}
			else if (false == m_bInvSwitch)
			{
				m_bInvSwitch = true;
			}
		}
	}
	if (!(Get_DIKeyState(DIK_I)))
		m_bKeyDown = true;
}

void CInventory::Mouse()
{
	
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	
	_float DefaultX = 955.f;
	_float DefaultY = 345.f;
	_float SizeX = 45.f;
	_float SizeY = 60.f;
	_float IntervalX = 50.f;
	_float IntervalY = 67.5f;
	//1405,565	~	1450 630 << 나가기버튼
	if (1405 < pt.x && pt.x < 1450 && 565 < pt.y && pt.y < 630 && m_bInvSwitch && Get_DIMouseState(DIM_LB))
	{
		m_bInvSwitch = false;
	}

	for (_int i = 0; i < 9; ++i)
	{
		for (_int j = 0; j < 9; ++j)
		{
			for (auto& iter : m_vecContents)
			{
				if (DefaultX + IntervalX*j < pt.x && pt.x < DefaultX + SizeX + IntervalX*j)
				{
					if (DefaultY + IntervalY*i < pt.y && pt.y < DefaultY + SizeY + IntervalY*i)
					{
						if (Get_DIMouseState(DIM_RB) && m_bRBDown)
						{
							if (m_vecContents.size() > 9 * i + j && iter == m_vecContents[9 * i + j] && iter != nullptr)
							{

								m_bRBDown = false;
								iter->Kill_Obj();
								iter = nullptr;

								m_iItemCnt--;
							}
						}
						if (m_vecContents.size() > 9 * i + j && iter == m_vecContents[9 * i + j] && iter != nullptr)
						{
							if (m_pIconGrab == nullptr&& Get_DIMouseState(DIM_LB) && m_bLBDown)
							{
								iVectorNumb = 9 * i + j;

								m_bLBDown = false;
								m_pIconGrab = dynamic_cast<CItemIcon*>(iter);
								m_pIconGrab->Cursor_fix();
							}
						}
					}
				}

				if (iter != nullptr&& iter == m_vecContents[iVectorNumb] && m_pIconGrab != nullptr && Get_DIMouseState(DIM_LB) && m_bLBDown)
				{
					m_bLBDown = false;
					m_pIconGrab->Cursor_free();
					if (1025 < pt.x && pt.x < 1075 && 215 < pt.y && pt.y < 280) // 맨왼쪽인벤토리
					{
						if (m_vecEquipments[0] == nullptr)
						{
							m_pIconGrab->Set_block(435.f *WINCY / WINCX, 365.f*WINCY / WINCX, 0.1f);
							m_vecEquipments[0] = m_pIconGrab;
							iter = nullptr;
							m_pIconGrab = nullptr;
							m_iItemCnt--;
						}
					}
					if (1080 < pt.x && pt.x < 1125 && 160 < pt.y && pt.y < 225) // 0,0
					{
						if (m_vecEquipments[1] == nullptr)
						{
							m_pIconGrab->Set_block(535.f *WINCY / WINCX, 455.f*WINCY / WINCX, 0.1f);
							m_vecEquipments[1] = m_pIconGrab;
							iter = nullptr;
							m_pIconGrab = nullptr;
							m_iItemCnt--;
						}
					}
					if (1080 < pt.x && pt.x < 1125 && 265 < pt.y && pt.y < 330) // 0,1
					{
						if (m_vecEquipments[2] == nullptr)
						{
							m_pIconGrab->Set_block(535.f *WINCY / WINCX, 275.f*WINCY / WINCX, 0.1f);
							m_vecEquipments[2] = m_pIconGrab;
							iter = nullptr;
							m_pIconGrab = nullptr;
							m_iItemCnt--;
						}
					}
					if (1230 < pt.x && pt.x < 1275 && 160 < pt.y && pt.y < 225) // 1,0
					{
						if (m_vecEquipments[3] == nullptr)
						{
							m_pIconGrab->Set_block(800.f *WINCY / WINCX, 465.f*WINCY / WINCX, 0.1f);
							m_vecEquipments[3] = m_pIconGrab;
							iter = nullptr;
							m_pIconGrab = nullptr;
							m_iItemCnt--;
						}
					}
					if (1230 < pt.x && pt.x < 1275 && 265 < pt.y && pt.y < 330) // 1,1
					{
						if (m_vecEquipments[4] == nullptr)
						{
							m_pIconGrab->Set_block(800.f *WINCY / WINCX, 275.f*WINCY / WINCX, 0.1f);
							m_vecEquipments[4] = m_pIconGrab;
							iter = nullptr;
							m_pIconGrab = nullptr;
							m_iItemCnt--;
						}
					}
					m_pIconGrab = nullptr;
					m_bNullSorting = false;
					m_bSorting = true;
				}
			}

			if (m_iItemCnt < 27)
			{
				if (1025 < pt.x && pt.x < 1075 && 215 < pt.y && pt.y < 280) // 맨왼쪽인벤토리
				{
					if (m_vecEquipments[0] != nullptr && Get_DIMouseState(DIM_LB) && m_bLBDown)
					{
						m_bLBDown = false;
						if (m_vecEquipments[0] != nullptr)
						{
							m_iItemCnt++;
							m_vecContents.push_back(m_vecEquipments[0]);
							m_vecEquipments[0] = nullptr;
							m_bNullSorting = true;
							m_bSorting = true;
						}
					}
				}
				if (1080 < pt.x && pt.x < 1125 && 160 < pt.y && pt.y < 225) // 0,0
				{
					if (m_vecEquipments[1] != nullptr && Get_DIMouseState(DIM_LB) && m_bLBDown)
					{
						m_bLBDown = false;
						if (m_vecEquipments[1] != nullptr)
						{
							m_iItemCnt++;
							m_vecContents.push_back(m_vecEquipments[1]);
							m_vecEquipments[1] = nullptr;
							m_bNullSorting = true;
							m_bSorting = true;
						}
					}
				}
				if (1080 < pt.x && pt.x < 1125 && 265 < pt.y && pt.y < 330) // 0,1
				{
					if (m_vecEquipments[2] != nullptr && Get_DIMouseState(DIM_LB) && m_bLBDown)
					{
						m_bLBDown = false;
						if (m_vecEquipments[2] != nullptr)
						{
							m_iItemCnt++;
							m_vecContents.push_back(m_vecEquipments[2]);
							m_vecEquipments[2] = nullptr;
							m_bNullSorting = true;
							m_bSorting = true;
						}
					}
				}
				if (1230 < pt.x && pt.x < 1275 && 160 < pt.y && pt.y < 225) // 1,0
				{
					if (m_vecEquipments[3] != nullptr && Get_DIMouseState(DIM_LB) && m_bLBDown)
					{
						m_bLBDown = false;
						if (m_vecEquipments[3] != nullptr)
						{
							m_iItemCnt++;
							m_vecContents.push_back(m_vecEquipments[3]);
							m_vecEquipments[3] = nullptr;
							m_bNullSorting = true;
							m_bSorting = true;
						}
					}
				}
				if (1230 < pt.x && pt.x < 1275 && 265 < pt.y && pt.y < 330) // 1,1
				{
					if (m_vecEquipments[4] != nullptr && Get_DIMouseState(DIM_LB) && m_bLBDown)
					{
						m_bLBDown = false;
						if (m_vecEquipments[4] != nullptr)
						{
							m_iItemCnt++;
							m_vecContents.push_back(m_vecEquipments[4]);
							m_vecEquipments[4] = nullptr;
							m_bNullSorting = true;
							m_bSorting = true;

						}
					}
				}
			}
		}
	}
	
	if (!Get_DIMouseState(DIM_RB))
	{
		m_bRBDown = true;		
	}	
	if (!Get_DIMouseState(DIM_LB))
	{
		m_bLBDown = true;
	}
	if (m_bRBDown && Get_DIMouseState(DIM_RB))
	{
		m_bRBDown = false;
	}
	if (m_bLBDown && Get_DIMouseState(DIM_LB))
	{
		m_bLBDown = false;
	}
}

void CInventory::Equipment()
{	
}

CInventory * CInventory::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CInventory*	pInstance = new CInventory(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CInventory::Free(void)
{
//	for_each(m_vecContents.begin(), m_vecContents.end(), CDeleteObj());
//	m_vecContents.clear();

	CGameObject::Free();
}
