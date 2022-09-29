#include "stdafx.h"
#include "..\Header\Stage.h"

#include "Export_Function.h"

#include "Wall.h"

#include "CubePlayer.h"
#include "CubeHead.h"
#include "CubeBody.h"
#include "CubeArm.h"
#include "CubeLeg.h"
#include "CubeFoot.h"
#include "CubeHand.h"



#include "CubeMonster.h"
#include "CubeMonsterArm.h"
#include "CubeMonsterBody.h"
#include "CubeMonsterHead.h"

#include "Uzi.h"
#include "Shotgun.h"
#include "Sniper.h"


<<<<<<< Updated upstream
//#include "ImguiMgr.h"
=======
#include "BaseMapping.h"
>>>>>>> Stashed changes

CStage::CStage(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev)
{
}


CStage::~CStage()
{
}

HRESULT CStage::Ready_Scene(void)
{
	if (FAILED(Engine::CScene::Ready_Scene()))
		return E_FAIL;

	CGameObject*		pGameObject = nullptr;

	FAILED_CHECK_RETURN(Ready_Proto(), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Light(), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Layer_Environment(L"Layer_Environment"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_GameLogic(L"Layer_GameLogic"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(L"Layer_UI"), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Layer_Wall(L"Layer_Wall"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Character(L"Layer_Character"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Monster(L"Layer_Monster"), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Bullet(L"Layer_Bullet"), E_FAIL);

	// 툴을 위한 레이어 생성
	//FAILED_CHECK_RETURN(Ready_Layer_Tool(L"Layer_Tool"), E_FAIL);

	return S_OK;
}

_int CStage::Update_Scene(const _float & fTimeDelta)
{
	// 스테이지에서 이렇게 업데이트 해주고있음.
	/*CImGuiMgr::GetInstance()->WindowLayOut();
	CImGuiMgr::GetInstance()->TerrainTool(m_pGraphicDev, this);
	CImGuiMgr::GetInstance()->CreateObject(m_pGraphicDev, this, m_pCam);*/

	return Engine::CScene::Update_Scene(fTimeDelta);
}

void CStage::LateUpdate_Scene(void)
{
	Engine::CScene::LateUpdate_Scene();
}

void CStage::Render_Scene(void)
{

}

HRESULT CStage::Ready_Layer_Environment(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	#pragma region 스테이즈 1 코드
// DynamicCamera
	/*pGameObject = CDynamicCamera::Create(m_pGraphicDev, &_vec3(0.f, 10.f, -10.f), &_vec3(0.f, 0.f, 0.f), &_vec3(0.f, 1.f, 0.f));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"DynamicCamera", pGameObject), E_FAIL);
	m_pCam = dynamic_cast<CDynamicCamera*>(pGameObject);*/
	
	// StaticCamera
	pGameObject = CDynamicCamera::Create(m_pGraphicDev, &_vec3(0.f, 20.f, -10.f), &_vec3(0.f, 0.f, 0.f), &_vec3(0.f, 1.f, 0.f));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"StaticCamera", pGameObject), E_FAIL);
	
	//Terrain
	pGameObject = CTerrain::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Terrain", pGameObject), E_FAIL);

#pragma endregion 스테이즈 1 코드

	// sky box
	pGameObject = CSkyBox::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"SkyBox", pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_GameLogic(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	pGameObject = CUzi::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TestPlayer", pGameObject), E_FAIL);

	pGameObject = CShotgun::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TestPlayer2", pGameObject), E_FAIL);

	pGameObject = CSniper::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TestPlayer3", pGameObject), E_FAIL);
	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_UI(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_Wall(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_Character(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	#pragma region 큐브 플레이어 잠가 놓았음 툴때문에 
	//	머리
	pGameObject = CCubeHead::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"HEAD", pGameObject), E_FAIL);
	//	몸통
	pGameObject = CCubeBody::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"BODY", pGameObject), E_FAIL);
	//	왼팔
	pGameObject = CCubeArm::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"L_ARM", pGameObject), E_FAIL);
	//	오른팔
	pGameObject = CCubeArm::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"R_ARM", pGameObject), E_FAIL);
	//	왼다리
	pGameObject = CCubeLeg::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"L_LEG", pGameObject), E_FAIL);
	//	오른다리
	pGameObject = CCubeLeg::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"R_LEG", pGameObject), E_FAIL);
	//	왼손
	pGameObject = CCubeHand::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"L_HAND", pGameObject), E_FAIL);
	//	오른손
	pGameObject = CCubeHand::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"R_HAND", pGameObject), E_FAIL);
	//	왼발
	pGameObject = CCubeFoot::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"L_FOOT", pGameObject), E_FAIL);
	//	오른발
	pGameObject = CCubeFoot::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"R_FOOT", pGameObject), E_FAIL);
	//	조립과 히트박스
	pGameObject = CCubePlayer::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"PLAYER", pGameObject), E_FAIL);

#pragma endregion 큐브 플레이어 잠가 놓았음 툴때문에 
	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_Monster(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	pGameObject = CCubeMonsterArm::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"M_LeftArm", pGameObject), E_FAIL);

	pGameObject = CCubeMonsterArm::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"M_RighrArm", pGameObject), E_FAIL);

	pGameObject = CCubeMonsterBody::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"M_Body", pGameObject), E_FAIL);

	pGameObject = CCubeMonsterHead::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"M_Head", pGameObject), E_FAIL);



	pGameObject = CCubeMonster::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CubeMonster", pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT	CStage::Ready_Layer_Bullet(const _tchar* pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

<<<<<<< Updated upstream
//HRESULT CStage::Ready_Layer_Tool(const _tchar * pLayerTag)
//{
//	// 맵툴을 활용할 것이다.
//	CImGuiMgr::GetInstance()->Ready_MapTool(m_pGraphicDev, this);
//
//	Engine::CLayer*		pLayer = Engine::CLayer::Create();
//	NULL_CHECK_RETURN(pLayer, E_FAIL);
//
//	CGameObject*		pGameObject = nullptr;
//
//	// m_pCam 이 중요함
//	pGameObject = m_pCam = CDynamicCamera::Create(m_pGraphicDev, &_vec3(0.f, 10.f, -10.f), &_vec3(0.f, 0.f, 0.f), &_vec3(0.f, 1.f, 0.f));
//	NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"DynamicCamera", pGameObject), E_FAIL);
//
//	pGameObject = CTerrain::Create(m_pGraphicDev);
//	NULL_CHECK_RETURN(pGameObject, E_FAIL);
//	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TerrainByTool", pGameObject), E_FAIL);
//
//	m_mapLayer.insert({ pLayerTag, pLayer });
//
//	return S_OK;
//}
=======
HRESULT CStage::Ready_Layer_Gun(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	pGameObject = CBaseMapping::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UZI1", pGameObject), E_FAIL);

	pGameObject = CUzi::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UZI2", pGameObject), E_FAIL);

	pGameObject = CUziPart1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Uzi_Part_1_1", pGameObject), E_FAIL);

	pGameObject = CUziPart2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Uzi_Part_1_2", pGameObject), E_FAIL);

	pGameObject = CUziPart3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Uzi_Part_1_3", pGameObject), E_FAIL);

	pGameObject = CUziPart4::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Uzi_Part_1_4", pGameObject), E_FAIL);

	pGameObject = CUziPart5::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Uzi_Part_1_5", pGameObject), E_FAIL);

	pGameObject = CUziPart1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Uzi_Part_2_1", pGameObject), E_FAIL);

	pGameObject = CUziPart2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Uzi_Part_2_2", pGameObject), E_FAIL);

	pGameObject = CUziPart3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Uzi_Part_2_3", pGameObject), E_FAIL);

	pGameObject = CUziPart4::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Uzi_Part_2_4", pGameObject), E_FAIL);

	pGameObject = CUziPart5::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Uzi_Part_2_5", pGameObject), E_FAIL);

	pGameObject = CShotgun::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"SHOTGUN", pGameObject), E_FAIL);

	pGameObject = CShotgunPart1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Shotgun_Part_1", pGameObject), E_FAIL);

	pGameObject = CShotgunPart2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Shotgun_Part_2", pGameObject), E_FAIL);

	pGameObject = CShotgunPart3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Shotgun_Part_3", pGameObject), E_FAIL);

	pGameObject = CShotgunPart4::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Shotgun_Part_4", pGameObject), E_FAIL);

	//pGameObject = CSniper::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"SNIPER", pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}
>>>>>>> Stashed changes

HRESULT CStage::Ready_Proto(void)
{
	return S_OK;
}

HRESULT CStage::Ready_Light(void)
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

CStage * CStage::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CStage *	pInstance = new CStage(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CStage::Free(void)
{
	CScene::Free();
}
