#include "stdafx.h"
#include "..\Header\KrakenBullet.h"


CKrakenBullet::CKrakenBullet(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}


CKrakenBullet::~CKrakenBullet()
{
}

HRESULT CKrakenBullet::Ready_Object(const _vec3 & vPos, _tchar * Name)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_KrakenInk = Name;

	m_pKrakenBullet->Set_Pos(vPos.x, vPos.y,vPos.z);
	m_pKrakenBullet->Set_Scale(5.f, 5.f, 5.f);
	m_pKrakenBullet->Static_Update();

	m_fSpeed = 10.f;

	m_vDir = { 1.f, 1.f, 1.f };

	return S_OK;
}

_int CKrakenBullet::Update_Object(const _float & fTimeDelta)
{

	CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_NONALPHA, this);
	m_pKrakenBullet->Move_Pos(&(m_vDir * m_fSpeed * fTimeDelta));

	return 0;
}

void CKrakenBullet::LateUpdate_Object(void)
{
	m_pKrakenBullet->Get_Info(INFO_POS, &m_vPos);
	if (m_vPos.y = 0)
	{
		this->Kill_Obj();
	}


	CGameObject::LateUpdate_Object();
}

void CKrakenBullet::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pKrakenBullet->Get_WorldMatrixPointer());
	m_pTexture->Set_Texture(1);
	m_pSphereTex->Render_Buffer();
}

HRESULT CKrakenBullet::Add_Component(void)
{
	
		CComponent* pComponent = nullptr;

		pComponent = m_pKrakenBullet = dynamic_cast<CTransform*>(Engine::Clone_Proto(TRANSFORM_COMP));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });
		
		
		pComponent = m_pSphereTex = dynamic_cast<CSphereTex*>(Engine::Clone_Proto(SPHERETEX_COMP));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].insert({ SPHERETEX_COMP, pComponent });

		pComponent = m_pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_CubePlayerTexture"));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].insert({ L"Proto_CubePlayerTexture", pComponent });


	return S_OK;
}


HRESULT CKrakenBullet::Build(void)
{
	return S_OK;
}

CKrakenBullet * CKrakenBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos, _tchar * Name)
{
	CKrakenBullet* pInstance = new CKrakenBullet(pGraphicDev);

		if(FAILED(pInstance->Ready_Object(vPos, Name)))
		{
			Safe_Release(pInstance);
			return nullptr;

		}
	return pInstance;
}

void CKrakenBullet::Free(void)
{
	CGameObject::Free();

}
