#include "stdafx.h"
#include "..\Header\PlayButton.h"


#include "Export_Function.h"
#include "Stage.h"
CPlayButton::CPlayButton(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}


CPlayButton::~CPlayButton()
{
}



HRESULT CPlayButton::Ready_Object()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);



	m_TranformCom->Set_Scale(0.1f, 0.1f, 0.f);
	m_TranformCom->Set_Pos(0.65f, 0.75f, 0.f);

	return S_OK;
}

_int CPlayButton::Update_Object(const _float & fTimeDelta)
{
	/*_int iResult = CScene::Update_Scene(fTimeDelta);

	if (m_pLoading->Get_Finish())
	{
	if (Get_DIKeyState(DIK_RETURN) & 0x8000)
	{
	CScene*		pScene = CStage::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pScene, E_FAIL);

	FAILED_CHECK_RETURN(Engine::Set_Scene(pScene), E_FAIL);

	return 0;
	}


	}

	return iResult;*/
	if (PointMouse())
	{
		if (Get_DIMouseState(DIM_LB) & 0x80)
		{
			Mouse_check = true;
		}
	}


	Engine::CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_UI, this);
	return 0;
}

void CPlayButton::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
	//_int iResult = CScene::Update_Scene();


}

void CPlayButton::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_TranformCom->Get_WorldMatrixPointer());
	m_TextureCom->Set_Texture(0);
	m_RcTexCom->Render_Buffer();

}

//void CPlayButton::MoveButton(void)
//{
//	_vec3	ButtonPos;
//	m_PlayButton->Get_Info(INFO_POS, &ButtonPos);
//	m_TranformCom->Set_Pos(0.1f, 0.1f, 0.f);
//	m_TranformCom->Set_Scale( 0.75,  0.75, 0.f);
//}

HRESULT CPlayButton::Add_Component(void)
{
	CComponent* pComponent = nullptr;
	pComponent = m_RcTexCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_RcTexCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pComponent });

	pComponent = m_TextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_ButtonPlayTexture"));
	NULL_CHECK_RETURN(m_TextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_ButtonPlayTexture", pComponent });

	pComponent = m_TranformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_TranformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });



	return S_OK;
}

//CPlayButton * CPlayButton::Create(LPDIRECT3DDEVICE9 pGraphicDev, fX, fY)
//{
//	CPlayButton* pInsatnce = new CPlayButton(pGraphicDev);
//
//	if (FAILED(pInsatnce->Ready_Object()))
//	{
//		Safe_Release(pInsatnce);
//		return nullptr;
//	}
//
//	pInsatnce->m_TranformCom->Set_Pos()
//
//	return pInsatnce;
//}


CPlayButton * CPlayButton::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{

	CPlayButton* pInsatnce = new CPlayButton(pGraphicDev);

	if (FAILED(pInsatnce->Ready_Object()))
	{
		Safe_Release(pInsatnce);
		return nullptr;
	}

	//pInsatnce->m_TranformCom->Set_Scale(0.75f, 0.75f, 0.f);

	return pInsatnce;

}

_bool CPlayButton::PointMouse(void)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	_long lLeft, lRight, lUp, lDown;


	//������ ��ǥ��ü���� ������ ������  �����ϰ��� ������ŭ ���ְ�  ������ ������ �ǰ� 
	lLeft = _long((0.5 * WINCX) * (1 + m_TranformCom->m_vInfo[INFO_POS].x) - (m_TranformCom->m_vScale.x) * (0.5 * WINCX));
	//�����ϸ�ŭ �����ְ�
	lRight = _long((0.5 * WINCX) * (1 + m_TranformCom->m_vInfo[INFO_POS].x) + (m_TranformCom->m_vScale.x * (0.5f * WINCX)));



	//y����ŭ  Up
	lUp = _long((0.5 * WINCY) * (1 - m_TranformCom->m_vInfo[INFO_POS].y) - (m_TranformCom->m_vScale.y * (WINCY * 0.5f)));
	lDown = _long((0.5 * WINCY) * (1 - m_TranformCom->m_vInfo[INFO_POS].y) + (m_TranformCom->m_vScale.y * (WINCY * 0.5f)));


	RECT rc = { lLeft, lUp, lRight, lDown };

	if (PtInRect(&rc, pt))
	{
		return true;
	}

	return false;
}

void CPlayButton::Free(void)
{
	CGameObject::Free();
}