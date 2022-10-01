#include "stdafx.h"
#include "..\Header\MonsterUI.h"
#include "CubeMonster.h"

CMonsterUI::CMonsterUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}


CMonsterUI::~CMonsterUI()
{
}

HRESULT CMonsterUI::Ready_Object(void)
{
	return S_OK;
}

_int CMonsterUI::Update_Object(const _float & fTimeDelta)
{
	_int iResult = CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);
	if (m_pMonster == nullptr)
		m_pMonster = Engine::Get_GameObject(L"Layer_Monster", L"CubeMonster");

	if (m_pMonster != nullptr)
	{/*
		m_iHp = dynamic_cast<CCubeMonster*>(m_pMonster)->Get_CurrentHP()->fCurrentHp*/;
		m_strHp = to_wstring(m_iHp);
	}

	
	return _int();
}

void CMonsterUI::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CMonsterUI::Render_Object(void)
{
	Begin_OrthoProj();
	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Resize_Buffer(m_iHp * 0.01f);
	m_pBufferCom->Render_Buffer();
	End_OrthoProj();
}

CMonsterUI * CMonsterUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return nullptr;
}

void CMonsterUI::Free(void)
{
	CGameObject::Free();
}

void CMonsterUI::Begin_OrthoProj()
{
}

void CMonsterUI::End_OrthoProj()
{
}

HRESULT CMonsterUI::Add_Component()
{
	return S_OK;
}
