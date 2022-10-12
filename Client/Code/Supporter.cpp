#include "stdafx.h"
#include "..\Header\Supporter.h"
#include "ShotParticle.h"
#include "BulletParticle.h"

CSupporter::CSupporter(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CSupporter::~CSupporter()
{
}

HRESULT CSupporter::Ready_Object(const _vec3 & vPos, wstring _strObjTag)
{
	return S_OK;
}

_int CSupporter::Update_Object(const _float & fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CSupporter::LateUpdate_Object(void)
{
}

void CSupporter::Render_Object(void)
{
}

void CSupporter::Free(void)
{
	CGameObject::Free();
}
