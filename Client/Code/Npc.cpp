#include "stdafx.h"
#include "..\Header\Npc.h"
#include "StaticCamera.h"

CNpc::CNpc(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CNpc::~CNpc()
{
}

HRESULT CNpc::Ready_Object(const _vec3& vPos)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	_vec3 vScale = { 0.f, 0.f, 0.f };
	m_pTransCom->Set_Scale(&vScale);
	m_pTransCom->Set_Pos(vPos.x,vPos.y,vPos.z);

	return S_OK;
}

_int CNpc::Update_Object(const _float & fTimeDelta)
{
	CStaticCamera* pCam = dynamic_cast<CStaticCamera*>(Get_GameObject(STAGE_ENVIRONMENT, L"StaticCamera"));
	CTransform* pPlayer = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_CHARACTER, L"BODY", TRANSFORM_COMP, ID_DYNAMIC));
	_vec3 vPlayerLook;
	pPlayer->Get_Info(INFO_LOOK, &vPlayerLook);
	_vec3 vPlayerPos;
	pPlayer->Get_Info(INFO_POS, &vPlayerPos);

	if (!m_bInit)
	{
		m_vPlayerPos = vPlayerPos;
		D3DXVec3Normalize(&vPlayerLook, &vPlayerLook);
		m_vPlayerPos.x += vPlayerLook.x * 10.f;
		m_vPlayerPos.y += vPlayerLook.y * 10.f + 2.f;
		m_vPlayerPos.z += vPlayerLook.z * 10.f;

		m_bInit = true;
	}

	if (pCam != nullptr && pCam->Get_bNpc() == true)
	{
		if (m_fFrame < 1.f)
			m_fFrame += fTimeDelta * 0.01f;

		_vec3 vScaleLerp;
		D3DXVec3Lerp(&vScaleLerp, &_vec3(0.f, 0.f, 0.f), &m_vScale, m_fFrame);
		m_pTransCom->Set_Scale(&vScaleLerp);
		
		_vec3 vTransLerp;
		D3DXVec3Lerp(&vTransLerp, &vPlayerPos, &m_vPlayerPos, m_fFrame);
		m_pTransCom->Set_Pos(vTransLerp.x, vTransLerp.y, vTransLerp.z);

		CGameObject::Update_Object(fTimeDelta);
		m_pTransCom->Billboard_Transform(fTimeDelta);
		Add_RenderGroup(RENDER_UI, this);
		return 0;
	}
	return 0;
}

void CNpc::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTextureCom->Set_Texture();
	m_pBufferCom->Render_Buffer();
}

HRESULT CNpc::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(RCTEX_COMP));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ RCTEX_COMP, pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"LetterBox_Tex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"LetterBox_Tex", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	return S_OK;
}

CNpc * CNpc::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos)
{
	CNpc*	pInstance = new CNpc(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CNpc::Free()
{
	CGameObject::Free();
}
