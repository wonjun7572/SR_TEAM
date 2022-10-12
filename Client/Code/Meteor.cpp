#include "stdafx.h"
#include "..\Header\Meteor.h"

CMeteor::CMeteor(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CMeteor::~CMeteor()
{
}

HRESULT CMeteor::Ready_Object(const _vec3& Position)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_vTarget = Position;

	m_pTransCom->Set_Pos(Position.x + 10.f, Position.y + 10.f,Position.z);

	m_pTransCom->Set_Scale(&_vec3(1.f,1.f,1.f));

	return S_OK;
}

_int CMeteor::Update_Object(const _float & fTimeDelta)
{
	_uint iResult = CGameObject::Update_Object(fTimeDelta);

	m_pTransCom->Chase_Target(&m_vTarget, 3.f, fTimeDelta);

	_vec3	vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);
	// 범위안에 여러개
	Add_RenderGroup(RENDER_NONALPHA,this);

	if (vPos.y <= 1.f)
	{
		return -1;
	}

	return iResult;
}

void CMeteor::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CMeteor::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTexture->Set_Texture();
	m_pSphereTex->Render_Buffer();
}

HRESULT CMeteor::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pSphereTex = dynamic_cast<CSphereTex*>(Engine::Clone_Proto(SPHERETEX_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ SPHERETEX_COMP, pComponent });

	pComponent = m_pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Lava_Tex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Lava_Tex", pComponent });

	return S_OK;
}

CMeteor * CMeteor::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& Position)
{
	CMeteor* pInstance = new CMeteor(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(Position)))
	{
		MSG_BOX("CMeteor Object Create Fail");
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMeteor::Free(void)
{
	CGameObject::Free();
}
