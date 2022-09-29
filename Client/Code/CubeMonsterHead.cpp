#include "stdafx.h"
#include "..\Header\CubeMonsterHead.h"




CCubeMonsterHead::CCubeMonsterHead(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
	fTimeDelta = 1.f;
}

CCubeMonsterHead::~CCubeMonsterHead()
{
}

HRESULT CCubeMonsterHead::Ready_Object(void)
{

	FAILED_CHECK_RETURN(Add_component(), E_FAIL);


	m_pTransform->Set_Scale(1.f, 1.f, 1.f);

	return S_OK;
}

_int CCubeMonsterHead::Update_Object(const _float & fTimeDelta)
{

	Add_RenderGroup(RENDER_ALPHA, this);
	CGameObject::Update_Object(fTimeDelta);

	
	return 0;
}

void CCubeMonsterHead::LateUpdate_Object(void)
{
	m_pTexture->Set_Texture(104);


}

void CCubeMonsterHead::Render_Object(void)
{

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	m_pTexture->Set_Texture(104);
	m_pCubeTexture->Render_Buffer();

}




HRESULT CCubeMonsterHead::Add_component(void)
{



	CComponent* pComponent = nullptr;


	pComponent = m_pTexture = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_CubeMonsterTexture"));
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubeMonsterTexture", pComponent });

	pComponent = m_pCubeTexture = dynamic_cast<CCubeTex*>(Clone_Proto(L"Proto_CubeTexCom"));
	NULL_CHECK_RETURN(m_pCubeTexture, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_CubeTexCom", pComponent });

	pComponent = m_pTransform = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransform, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });


	return S_OK;
}

CCubeMonsterHead * CCubeMonsterHead::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{

	CCubeMonsterHead* pInstance = new CCubeMonsterHead(pGraphicDev);
	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCubeMonsterHead::Free(void)
{
	CGameObject::Free();
}
