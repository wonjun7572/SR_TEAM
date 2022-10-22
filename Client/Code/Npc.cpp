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
		if (m_fFrame <= 1.f)
			m_fFrame += fTimeDelta * 0.05f;

		if (m_fFrame > 0.9f && m_fTexFrame < 52.5f)
			m_fTexFrame += fTimeDelta * 3.f;
		
		_vec3 vScaleLerp;
		D3DXVec3Lerp(&vScaleLerp, &_vec3(0.f, 0.f, 0.f), &m_vScale, m_fFrame);
		m_pTransCom->Set_Scale(&vScaleLerp);
		
		_vec3 vTransLerp;
		D3DXVec3Lerp(&vTransLerp, &vPlayerPos, &m_vPlayerPos, m_fFrame);
		m_pTransCom->Set_Pos(vTransLerp.x, vTransLerp.y, vTransLerp.z);

		CGameObject::Update_Object(fTimeDelta);
		m_pTransCom->Billboard_Transform(fTimeDelta);
		Add_RenderGroup(RENDER_UI, this);
	}
	return 0;
}

void CNpc::Render_Object(void)
{
	_matrix      matWorld, matView, matProj;

	matWorld = *m_pTransCom->Get_WorldMatrixPointer();
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	D3DXMatrixTranspose(&matWorld, &matWorld);
	D3DXMatrixTranspose(&matView, &matView);
	D3DXMatrixTranspose(&matProj, &matProj);

	if (FAILED(m_pShaderCom->Set_RawValue("g_WorldMatrix", &matWorld, sizeof(_matrix))))
		return;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &matView, sizeof(_matrix))))
		return;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &matProj, sizeof(_matrix))))
		return;

	_uint iTexindex = _uint(m_fTexFrame);
	m_pQuest1TexCom->Set_Texture(m_pShaderCom, "g_DefaultTexture", iTexindex);


	m_pShaderCom->Begin_Shader(1);
	m_pBufferCom->Render_Buffer();
	m_pShaderCom->End_Shader();
}

HRESULT CNpc::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(RCTEX_COMP));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ RCTEX_COMP, pComponent });

	// Quest1 모음집
	pComponent = m_pQuest1TexCom = dynamic_cast<CTexture*>(Clone_Proto(L"LetterBox_Tex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"LetterBox_Tex", pComponent });

	// Quest2 모음집
	pComponent = m_pQuest2TexCom = dynamic_cast<CTexture*>(Clone_Proto(L"LetterBox_Tex_2"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"LetterBox_Tex_2", pComponent });

	// Quest3 모음집
	pComponent = m_pQuest3TexCom = dynamic_cast<CTexture*>(Clone_Proto(L"LetterBox_Tex_3"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"LetterBox_Tex_3", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pShaderCom = dynamic_cast<CShader*>(Clone_Proto(RCTEX_SHADER));
	NULL_CHECK_RETURN(m_pShaderCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ RCTEX_SHADER, pComponent });

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
