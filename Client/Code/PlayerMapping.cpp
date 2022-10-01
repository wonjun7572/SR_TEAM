#include "stdafx.h"
#include "..\Header\PlayerMapping.h"


CPlayerMapping::CPlayerMapping(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CPlayerMapping::~CPlayerMapping()
{
}

HRESULT CPlayerMapping::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_pTransform->Set_Scale(0.5f, 0.5f, 0.5f);
	return S_OK;
}

_int CPlayerMapping::Update_Object(const _float & fTimeDelta)
{
	if (!m_bWorldMap)
	{
		Add_RenderGroup(RENDER_MINIMAP, this);
	}
	if (m_bWorldMap)
	{
		Add_RenderGroup(RENDER_MAPVIEW, this);
	}

	Key_Input();
	CGameObject::Update_Object(fTimeDelta);

	return 0;
}

void CPlayerMapping::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
	if (nullptr == m_pTransformPlayer)
	{
		m_pTransformPlayer = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"BODY", L"Proto_TransformCom", ID_DYNAMIC));
		NULL_CHECK(m_pTransformPlayer);
	}
	
	_vec3 vPos;
	m_pTransformPlayer->Get_Info(INFO_POS, &vPos);
	m_pTransform->Set_Pos(vPos.x, vPos.y, vPos.z);

}

void CPlayerMapping::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	Begin_OrthoProj();
	m_pTexture->Set_Texture(60);
	if(!m_bWorldMap)
		m_pBufferCom->Render_Buffer();
	End_OrthoProj();
	
	if(m_bWorldMap)
		m_pCube->Render_Buffer();
}

void CPlayerMapping::Begin_OrthoProj()
{
	_vec3 vPos;
	m_pTransformPlayer->Get_Info(INFO_POS, &vPos);
	m_pTransform->Set_Pos(vPos.x, vPos.y, vPos.z);

	_matrix matWorld, matView, matProj, matOrtho;
	m_pGraphicDev->GetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	memcpy(&m_matWorld, &matWorld, sizeof(_matrix));
	memcpy(&m_matView, &matView, sizeof(_matrix));
	memcpy(&m_matProj, &matProj, sizeof(_matrix));

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	matView.m[0][0] = PINGSIZE*WINCX / WINCY * MAPCX/MAPCY; // �̹��� ����
	matView.m[1][1] = PINGSIZE*WINCX / WINCY* MAPCX / MAPCY; // �̹��� ����
	matView.m[2][2] = 1.f;
	matView.m[3][0] = MAPPOSX - (MAPCX)+vPos.x * (((float)MAPCX * 2) / (float)VTXCNTX); //- PINGSIZE /2;
	matView.m[3][1] = MAPPOSY - (MAPCY)+vPos.z * (((float)MAPCY * 2) / (float)VTXCNTZ); //- PINGSIZE /2;
	matView.m[3][2] = 0.001f;


	D3DXMatrixOrthoLH(&matOrtho, WINCX, WINCY, 0.f, 1.f);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matOrtho);
}

void CPlayerMapping::End_OrthoProj()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void CPlayerMapping::Key_Input(void)
{
	if (Get_DIKeyState(DIK_Y))
	{
		CRenderer::GetInstance()->On_Minimap();
		m_bWorldMap = false;
	}
	if (Get_DIKeyState(DIK_U))
	{
		CRenderer::GetInstance()->Off_Minimap();
		m_bWorldMap = true;
	}
}

HRESULT CPlayerMapping::Add_Component(void)
{
	CComponent* pInstance = nullptr;

	pInstance = m_pCube = dynamic_cast<CCubeTex*>(Engine::Clone_Proto(L"Proto_CubeTexCom"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubeTexCom", pInstance });

	pInstance = m_pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_CubePlayerTexture"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubePlayerTexture", pInstance });

	pInstance = m_pTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pInstance });
	
	pInstance = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pInstance });


	return S_OK;
}

CPlayerMapping * CPlayerMapping::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayerMapping* pInstance = new CPlayerMapping(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Safe_Release(pInstance);


	return pInstance;
}

void CPlayerMapping::Free(void)
{
	CGameObject::Free();
}

