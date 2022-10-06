#include "stdafx.h"
#include "..\Header\CubeShop.h"
#include "LetterBox.h"
#include "Shop.h"

static _int m_iDialogCnt = 0;

CCubeShop::CCubeShop(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}


CCubeShop::~CCubeShop()
{
}

HRESULT CCubeShop::Ready_Object(const _vec3& vPos)
{
	FAILED_CHECK_RETURN(Add_component(), E_FAIL);

	m_pTransform->Set_Scale(0.5f, 0.5f, 0.5f);
	m_pTransform->Set_Pos(vPos.x, vPos.y, vPos.z);
	return S_OK;
}

_int CCubeShop::Update_Object(const _float & fTimeDelta)
{
	Interact();
	Add_RenderGroup(RENDER_NONALPHA, this);
	CGameObject::Update_Object(fTimeDelta);

	return 0;
}

void CCubeShop::LateUpdate_Object(void)
{

}

void CCubeShop::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	m_pTexture->Set_Texture(0);
	m_pCubeTexture->Render_Buffer();
}

HRESULT CCubeShop::Add_component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTexture = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_InteractShop"));
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_InteractShop", pComponent });

	pComponent = m_pCubeTexture = dynamic_cast<CCubeTex*>(Clone_Proto(CUBETEX_COMP));
	NULL_CHECK_RETURN(m_pCubeTexture, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ CUBETEX_COMP, pComponent });

	pComponent = m_pTransform = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransform, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });
	
	return S_OK;
}

HRESULT CCubeShop::Interact()
{
	CGameObject*		pGameObject = nullptr;

	CTransform*		pPlayerTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_CHARACTER, L"BODY", TRANSFORM_COMP, ID_DYNAMIC));
	NULL_CHECK_RETURN(pPlayerTransformCom, E_FAIL);
	_vec3		vPlayerPos;
	_vec3		vPos;
	_vec3		vDir;
	_float		fDistance;
	m_pTransform->Get_Info(INFO_POS, &vPos);
	pPlayerTransformCom->Get_Info(Engine::INFO_POS, &vPlayerPos);
	vDir = vPos - vPlayerPos;
	fDistance = D3DXVec3Length(&vDir);

	if (fDistance <= 15.f)
	{
		m_bSwitch = true;
		m_bApproaching = true;
	}
	if (fDistance >= 15.f)
	{
		m_bApproaching = false;
	}

	if (!m_bDialogInit && m_iTexIndex == 0 && m_bApproaching)
	{
		m_bDialogInit = true;
	}

	if (m_bSwitch && Get_DIKeyState(DIK_E))
	{
		CTransform* m_pShop = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_UI, L"Shop", TRANSFORM_COMP, ID_DYNAMIC));
		NULL_CHECK_RETURN(m_pShop, E_FAIL);
	}

	if (m_bSwitch && m_pDialogBox != nullptr)
	{
		dynamic_cast<CLetterBox*>(m_pDialogBox)->On_Switch();
	}
	if (!m_bSwitch && m_pDialogBox != nullptr)
	{
		dynamic_cast<CLetterBox*>(m_pDialogBox)->Off_Switch();
	}

	return S_OK;
}

CCubeShop * CCubeShop::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos)
{
	CCubeShop* pInstance = new CCubeShop(pGraphicDev);

	if(FAILED(pInstance->Ready_Object(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CCubeShop::Free(void)
{
	for (auto& iter : m_listDialogCnt)
	{
		if (iter != nullptr)
			delete iter;
	}

	m_listDialogCnt.clear();
	CGameObject::Free();
}
