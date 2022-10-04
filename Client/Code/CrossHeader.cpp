#include "stdafx.h"
#include "..\Header\CrossHeader.h"
#include "CubePlayer.h"

CCrossHeader::CCrossHeader(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CCrossHeader::~CCrossHeader()
{
}

HRESULT CCrossHeader::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CCrossHeader::Update_Object(const _float & fTimeDelta)
{
	_int iResult = CGameObject::Update_Object(fTimeDelta);
	CGameObject* pPlayer = nullptr;
	pPlayer = Engine::Get_GameObject(L"Layer_Character", L"PLAYER");
	NULL_CHECK_RETURN(pPlayer, iResult);

	if (dynamic_cast<CCubePlayer*>(pPlayer)->Get_Weapon() == nullptr)
		return iResult;

	if (dynamic_cast<CCubePlayer*>(pPlayer)->Get_Weapon() == Engine::Get_GameObject(L"Layer_Gun", L"UZI1"))
	{
		m_eGunID = GUN_RIFLE;
	}
	else if (dynamic_cast<CCubePlayer*>(pPlayer)->Get_Weapon() == Engine::Get_GameObject(L"Layer_Gun", L"SHOTGUN"))
	{
		m_eGunID = GUN_SHOTGUN;
	}
	else if (dynamic_cast<CCubePlayer*>(pPlayer)->Get_Weapon() == Engine::Get_GameObject(L"Layer_Gun", L"SNIPER"))
	{
		if(dynamic_cast<CCubePlayer*>(pPlayer)->Get_SniperZoom() == true)
			m_eGunID = GUN_SNIPER_ZOOMIN;
		else
			m_eGunID = GUN_SNIPER_ZOOMOUT;
	}

	Add_RenderGroup(RENDER_UI, this);
	return iResult;
}

void CCrossHeader::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CCrossHeader::Render_Object(void)
{
	Begin_OrthoProj(m_eGunID);

	switch (m_eGunID)
	{
	case CCrossHeader::GUN_RIFLE:
		m_pRifleTextureCom->Set_Texture(0);
		break;
	case CCrossHeader::GUN_SHOTGUN:
		m_pShotGunTextureCom->Set_Texture(0);
		break;
	case CCrossHeader::GUN_SNIPER_ZOOMIN:
		m_pSniperTextureCom->Set_Texture(0);
		break;
	case CCrossHeader::GUN_SNIPER_ZOOMOUT:
		m_pRifleTextureCom->Set_Texture(0);
		break;
	default:
		break;
	}
	
	m_pBufferCom->Render_Buffer();

	End_OrthoProj();
}

void CCrossHeader::Begin_OrthoProj(GUN_ID eID)
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
	
	if (eID == GUN_RIFLE || eID == GUN_SNIPER_ZOOMOUT)
	{
		matView.m[0][0] = 20.f;	  // 이미지 가로
		matView.m[1][1] = 20.f;   // 이미지 세로
		matView.m[2][2] = 0.f;
		matView.m[3][0] = m_pTransCom->m_vInfo[INFO_POS].x;
		matView.m[3][1] = m_pTransCom->m_vInfo[INFO_POS].y;
	}
	else if(eID == GUN_SHOTGUN)
	{
		matView.m[0][0] = 30.f;	  // 이미지 가로
		matView.m[1][1] = 30.f;   // 이미지 세로
		matView.m[2][2] = 0.f;
		matView.m[3][0] = m_pTransCom->m_vInfo[INFO_POS].x;
		matView.m[3][1] = m_pTransCom->m_vInfo[INFO_POS].y;
	}
	else if (eID == GUN_SNIPER_ZOOMIN)
	{
		matView.m[0][0] = 800.f;	  // 이미지 가로
		matView.m[1][1] = 450.f;	  // 이미지 세로
		matView.m[2][2] = 0.f;
		matView.m[3][0] = m_pTransCom->m_vInfo[INFO_POS].x;
		matView.m[3][1] = m_pTransCom->m_vInfo[INFO_POS].y;
	}
	D3DXMatrixOrthoLH(&matOrtho, WINCX, WINCY, 0.f, 1.f);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matOrtho);
}

void CCrossHeader::End_OrthoProj()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

HRESULT CCrossHeader::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({L"Proto_RcTexCom", pComponent});

	pComponent = m_pRifleTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_CrossHeader_Rifle"));
	NULL_CHECK_RETURN(m_pRifleTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CrossHeader_Rifle", pComponent });

	pComponent = m_pShotGunTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_CrossHeader_ShotGun"));
	NULL_CHECK_RETURN(m_pShotGunTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CrossHeader_ShotGun", pComponent });

	pComponent = m_pSniperTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_CrossHeader_Sniper"));
	NULL_CHECK_RETURN(m_pSniperTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CrossHeader_Sniper", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	return S_OK;
}

CCrossHeader * CCrossHeader::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCrossHeader*	pInstance = new CCrossHeader(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CCrossHeader::Free(void)
{
	CGameObject::Free();
}
