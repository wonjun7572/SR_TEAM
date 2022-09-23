#include "stdafx.h"
#include "..\Header\Bullet.h"

#include "Export_Function.h"
#include "PoolMgr.h"

CBullet::CBullet(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CBullet::~CBullet()
{
}

HRESULT CBullet::Ready_Object(const _vec3* pPos, const _vec3* pDir)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_pTransCom->Set_Scale(0.2f, 0.2f, 0.2f);
	m_pTransCom->m_vInfo[INFO_POS] = *pPos;
	m_vDirection = *pDir;
	return S_OK;
}

_int CBullet::Update_Object(const _float & fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	_vec3 vPos;

	m_pTransCom->Get_Info(INFO_POS, &vPos);

	//if (vPos.x >= 50.f || vPos.y >= 50.f || vPos.z >= 50.f
	//	|| vPos.x <= -50.f || vPos.y <= -50.f || vPos.z <= -50.f)
	//{
	//	m_pTransCom->Set_Pos(0.f, 0.f, 0.f);
	//	CPoolMgr::GetInstance()->Collect_Obj(this);
	//}

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);
	m_pTransCom->Move_Pos(&(m_vDirection * fTimeDelta * 5.f));

	return 0;
}

void CBullet::LateUpdate_Object(void)
{
	Engine::CGameObject::LateUpdate_Object();
}

void CBullet::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	m_pTextureCom->Set_Texture(3);

	m_pCubetexCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

HRESULT CBullet::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_CubePlayerTexture"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubePlayerTexture", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	pComponent = m_pCubetexCom = dynamic_cast<CCubeTex*>(Clone_Proto(L"Proto_CubeTexCom"));
	NULL_CHECK_RETURN(m_pCubetexCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_CubeTexCom", pComponent });
	return S_OK;
}

CBullet * CBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3* pPos, const _vec3* pDir)
{
	CBullet *	pInstance = new CBullet(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(pPos, pDir)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CBullet::Free(void)
{
	CGameObject::Free();
}
