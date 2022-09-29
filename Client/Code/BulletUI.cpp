#include "stdafx.h"
#include "..\Header\BulletUI.h"

#include "Export_Function.h"
#include "CubePlayer.h"

CBulletUI::CBulletUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CBulletUI::~CBulletUI()
{
}

HRESULT CBulletUI::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	//FONT
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"REMAINBULLET", L"Electronic Highway Sign", 8, 12, FW_NORMAL), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"TOTALBULLET", L"Electronic Highway Sign", 8, 10, FW_NORMAL), E_FAIL);
	
	return S_OK;
}

_int CBulletUI::Update_Object(const _float & fTimeDelta)
{
	_int iResult = CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);
	if (m_pPlayer == nullptr)
		m_pPlayer = Engine::Get_GameObject(L"Layer_Character", L"PLAYER");

	if (m_pPlayer != nullptr)
	{
		if (dynamic_cast<CCubePlayer*>(m_pPlayer)->Get_Weapon() != nullptr)
		{
			m_fTotalBullet = dynamic_cast<CCubePlayer*>(m_pPlayer)->Get_Weapon()->Get_Ability()->fBulletCount;
			m_fRemainBullet = dynamic_cast<CCubePlayer*>(m_pPlayer)->Get_Weapon()->Get_Ability()->fRemainBulletCnt;
			m_strTotalBullet = L"/" + to_wstring(_int(m_fTotalBullet));
			m_strReminaBullet =  to_wstring(_int(m_fRemainBullet));
		}
	}

	return iResult;
}

void CBulletUI::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CBulletUI::Render_Object(void)
{
	Begin_OrthoProj();
	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Resize_Buffer_Reverse(m_fRemainBullet / m_fTotalBullet);
	m_pBufferCom->Render_Buffer();
	End_OrthoProj();
	Render_Font(L"REMAINBULLET", m_strReminaBullet.c_str(), &(_vec2(760.f, 560.f)), D3DXCOLOR(0.5f, 0.5f, 0.3f, 1.f));
	Render_Font(L"TOTALBULLET", m_strTotalBullet.c_str(), &(_vec2(757.5f, 580.f)), D3DXCOLOR(0.5f, 0.5f, 0.3f, 1.f));
}

void CBulletUI::Begin_OrthoProj()
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

	matView.m[0][0] = 160.f; // 이미지 가로
	matView.m[1][1] = 20.f;   // 이미지 세로
	matView.m[2][2] = 1.f;
	matView.m[3][0] = m_pTransCom->m_vInfo[INFO_POS].x + 520.f;
	matView.m[3][1] = m_pTransCom->m_vInfo[INFO_POS].y - 415.f;

	D3DXMatrixOrthoLH(&matOrtho, WINCX, WINCY, 0.f, 1.f);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matOrtho);
}

void CBulletUI::End_OrthoProj()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

HRESULT CBulletUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"RcTex_Bullet"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"RcTex_Bullet", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"BULLET_Gage"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"BULLET_Gage", pComponent });

	return S_OK;
}

CBulletUI * CBulletUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBulletUI*	pInstance = new CBulletUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CBulletUI::Free(void)
{
	CGameObject::Free();
}
