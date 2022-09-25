#include "stdafx.h"
#include "..\Header\Item.h"

#include "Export_Function.h"

CItem::CItem(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CItem::CItem(const CGameObject & rhs)
	:CGameObject(rhs)
{
}

CItem::~CItem()
{
}

HRESULT CItem::Ready_Object(const _vec3& vPos)
{
	return S_OK;
}

_int CItem::Update_Object(const _float & fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_PRIORITY, this);
	return 0;
}

void CItem::LateUpdate_Object()
{
	CGameObject::LateUpdate_Object();
}

void CItem::Render_Object()
{
}

void CItem::Free()
{
	CGameObject::Free();
}
