#include "stdafx.h"
#include "..\Header\ToolScene.h"

#include "Export_Function.h"

#include "Wall.h"

#include "ImguiMgr.h"

CToolScene::CToolScene(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev)
{
}


CToolScene::~CToolScene()
{
}

HRESULT CToolScene::Ready_Scene(void)
{
	if (FAILED(Engine::CScene::Ready_Scene()))
		return E_FAIL;

	CGameObject*		pGameObject = nullptr;

	FAILED_CHECK_RETURN(Ready_Proto(), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Light(), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Layer_Environment(L"Layer_Environment"), E_FAIL);
	//FAILED_CHECK_RETURN(Ready_Layer_GameLogic(L"Layer_GameLogic"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(L"Layer_UI"), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Layer_Wall(L"Layer_Wall"), E_FAIL);
	//FAILED_CHECK_RETURN(Ready_Layer_Character(L"Layer_Character"), E_FAIL);
	//FAILED_CHECK_RETURN(Ready_Layer_Bullet(L"Layer_Bullet"), E_FAIL);

	// ���� ���� ���̾� ����
	FAILED_CHECK_RETURN(Ready_Layer_Tool(L"Layer_Tool"), E_FAIL);

	return S_OK;
}

_int CToolScene::Update_Scene(const _float & fTimeDelta)
{
	// ������������ �̷��� ������Ʈ ���ְ�����.
	CImGuiMgr::GetInstance()->WindowLayOut();
	CImGuiMgr::GetInstance()->TerrainTool(m_pGraphicDev, this);
	CImGuiMgr::GetInstance()->CreateObject(m_pGraphicDev, this, m_pCam);

	return Engine::CScene::Update_Scene(fTimeDelta);
}

void CToolScene::LateUpdate_Scene(void)
{
	Engine::CScene::LateUpdate_Scene();
}

void CToolScene::Render_Scene(void)
{

}

HRESULT CToolScene::Ready_Layer_Environment(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

#pragma region �������� 1 �ڵ�
	// DynamicCamera
	/*pGameObject = CDynamicCamera::Create(m_pGraphicDev, &_vec3(0.f, 10.f, -10.f), &_vec3(0.f, 0.f, 0.f), &_vec3(0.f, 1.f, 0.f));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"DynamicCamera", pGameObject), E_FAIL);
	m_pCam = dynamic_cast<CDynamicCamera*>(pGameObject);*/

	// StaticCamera
	/*pGameObject = CStaticCamera::Create(m_pGraphicDev, &_vec3(0.f, 20.f, -10.f), &_vec3(0.f, 0.f, 0.f), &_vec3(0.f, 1.f, 0.f));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"StaticCamera", pGameObject), E_FAIL);*/

	//Terrain
	/*pGameObject = CTerrain::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Terrain", pGameObject), E_FAIL);*/

#pragma endregion �������� 1 �ڵ�

	// sky box
	pGameObject = CSkyBox::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"SkyBox", pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

//HRESULT CToolScene::Ready_Layer_GameLogic(const _tchar * pLayerTag)
//{
//	Engine::CLayer*		pLayer = Engine::CLayer::Create();
//	NULL_CHECK_RETURN(pLayer, E_FAIL);
//
//	CGameObject*		pGameObject = nullptr;
//
//	// �׽�Ʈ �÷��̾�� �׽�Ʈ��
//	pGameObject = CTestPlayer::Create(m_pGraphicDev);
//	NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TestPlayer", pGameObject), E_FAIL);
//
//	m_mapLayer.insert({ pLayerTag, pLayer });
//
//	return S_OK;
//}

HRESULT CToolScene::Ready_Layer_UI(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CToolScene::Ready_Layer_Wall(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

//HRESULT CToolScene::Ready_Layer_Character(const _tchar * pLayerTag)
//{
//	Engine::CLayer*		pLayer = Engine::CLayer::Create();
//	NULL_CHECK_RETURN(pLayer, E_FAIL);
//
//	CGameObject*		pGameObject = nullptr;
//
//#pragma region ť�� �÷��̾� �ᰡ ������ �������� 
//	//	�Ӹ�
//	pGameObject = CCubeHead::Create(m_pGraphicDev);
//	NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"HEAD", pGameObject), E_FAIL);
//	//	����
//	pGameObject = CCubeBody::Create(m_pGraphicDev);
//	NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"BODY", pGameObject), E_FAIL);
//	//	����
//	pGameObject = CCubeArm::Create(m_pGraphicDev);
//	NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"L_ARM", pGameObject), E_FAIL);
//	//	������
//	pGameObject = CCubeArm::Create(m_pGraphicDev);
//	NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"R_ARM", pGameObject), E_FAIL);
//	//	�޴ٸ�
//	pGameObject = CCubeLeg::Create(m_pGraphicDev);
//	NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"L_LEG", pGameObject), E_FAIL);
//	//	�����ٸ�
//	pGameObject = CCubeLeg::Create(m_pGraphicDev);
//	NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"R_LEG", pGameObject), E_FAIL);
//	//	�޼�
//	pGameObject = CCubeHand::Create(m_pGraphicDev);
//	NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"L_HAND", pGameObject), E_FAIL);
//	//	������
//	pGameObject = CCubeHand::Create(m_pGraphicDev);
//	NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"R_HAND", pGameObject), E_FAIL);
//	//	�޹�
//	pGameObject = CCubeFoot::Create(m_pGraphicDev);
//	NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"L_FOOT", pGameObject), E_FAIL);
//	//	������
//	pGameObject = CCubeFoot::Create(m_pGraphicDev);
//	NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"R_FOOT", pGameObject), E_FAIL);
//	//	������ ��Ʈ�ڽ�
//	pGameObject = CCubePlayer::Create(m_pGraphicDev);
//	NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"PLAYER", pGameObject), E_FAIL);
//
//#pragma endregion ť�� �÷��̾� �ᰡ ������ �������� 
//	m_mapLayer.insert({ pLayerTag, pLayer });
//
//	return S_OK;
//}
//
//HRESULT	CToolScene::Ready_Layer_Bullet(const _tchar* pLayerTag)
//{
//	Engine::CLayer*		pLayer = Engine::CLayer::Create();
//	NULL_CHECK_RETURN(pLayer, E_FAIL);
//
//	CGameObject*		pGameObject = nullptr;
//
//	m_mapLayer.insert({ pLayerTag, pLayer });
//
//	return S_OK;
//}

HRESULT CToolScene::Ready_Layer_Tool(const _tchar * pLayerTag)
{
	// ������ Ȱ���� ���̴�.
	CImGuiMgr::GetInstance()->Ready_MapTool(m_pGraphicDev, this);

	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	// m_pCam �� �߿���
	pGameObject = m_pCam = CDynamicCamera::Create(m_pGraphicDev, &_vec3(0.f, 10.f, -10.f), &_vec3(0.f, 0.f, 0.f), &_vec3(0.f, 1.f, 0.f));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"DynamicCamera", pGameObject), E_FAIL);

	pGameObject = CTerrain::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TerrainByTool", pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CToolScene::Ready_Proto(void)
{
	return S_OK;
}

HRESULT CToolScene::Ready_Light(void)
{
	D3DLIGHT9	Light;
	ZeroMemory(&Light, sizeof(D3DLIGHT9));

	Light.Type = D3DLIGHT_DIRECTIONAL;
	Light.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	Light.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	Light.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	Light.Direction = _vec3(0.f, -1.f, 0.f);

	/*	Light.Position =
	Light.Range =
	Light.Falloff =
	Light.Attenuation0 =
	Light.Attenuation1 =
	Light.Attenuation2 =
	Light.Theta
	Light.Phi =
	*/
	FAILED_CHECK_RETURN(Engine::Ready_Light(m_pGraphicDev, &Light, 0), E_FAIL);

	return S_OK;
}

CToolScene * CToolScene::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CToolScene *	pInstance = new CToolScene(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CToolScene::Free(void)
{
	CScene::Free();
}