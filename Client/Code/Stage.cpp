#include "stdafx.h"
#include "..\Header\Stage.h"

#include "Export_Function.h"

#include "Wall.h"
#include "TestCube.h"

#include "AnimationPlayer.h"

#include "CubePlayer.h"
#include "CubeHead.h"
#include "CubeBody.h"
#include "CubeArm.h"
#include "CubeLeg.h"
#include "CubeFoot.h"
#include "CubeHand.h"

#include "Uzi.h"
#include "Shotgun.h"
#include "Sniper.h"

#include "PlayerUI.h"
#include "PlayerFaceUI.h"
#include "PlayerHpUI.h"
#include "PlayerDefenseUI.h"
#include "WeaponUI.h"
#include "BulletUI.h"
#include "GunUI.h"
#include "BaseMapping.h"

#include "GetUzi.h"
#include "GetShotgun.h"
#include "GetSniper.h"

//Item
#include "HealthPotion.h"
#include "ObtainBullet.h"
#include "ObtainDefense.h"
#include "MaxPlusHp.h"


#include "LetterBox.h"
#include "ShotParticle.h"
#include "ItemParticle.h"

#include "CrossHeader.h"
#include "TargetCube.h"
#include "BulletParticle.h"
#include "Shop.h"
#include "CubeShop.h"
#include "Inventory.h"

#include "FireMan.h"
#include "Slime.h"
#include "Zombie.h"
#include "Skeleton.h"
#include "MonsterUI.h"
#include "HitBarUI.h"
#include "ComboUI.h"

#include "Illusioner.h"

#include "EveryParticle.h"

#include "Thorn.h"
#include "Magma.h"
#include "ItemBox.h"

#include "Supporter_Uzi.h"
#include "MiddleBoss.h"

#include "BattleCursier.h"
#include "Flight.h"

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

	//_float fBGMSound = 1.f;
	//PlayBGM(L"Track_01.mp3", fBGMSound);

	FAILED_CHECK_RETURN(Ready_Proto(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Light(), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Layer_Environment(STAGE_ENVIRONMENT), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_GameLogic(STAGE_GAMELOGIC), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(STAGE_UI), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Character(STAGE_CHARACTER), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Monster(STAGE_MONSTER), E_FAIL);		//	몬스터 본체 관리 레이어
	FAILED_CHECK_RETURN(Ready_Layer_Mapping(STAGE_MAPPING), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Bullet(STAGE_BULLET), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Wall(STAGE_WALL), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Item(STAGE_ITEM), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Gun(STAGE_GUN), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_GunItem(STAGE_GUNITEM), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Player(STAGE_PLAYER), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_DestroyWall(STAGE_DESTORYWALL), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Skill(STAGE_SKILL), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Trap(STAGE_TRAP), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Supporter(STAGE_SUPPORTER), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_PlayerBullet(STAGE_BULLETPLAYER), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Creature(STAGE_CREATURE), E_FAIL);

	return S_OK;
}

_int CStage::Update_Scene(const _float & fTimeDelta)
{
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

	pGameObject = CStaticCamera::Create(m_pGraphicDev, &_vec3(0.f, 20.f, -10.f), &_vec3(0.f, 0.f, 0.f), &_vec3(0.f, 1.f, 0.f));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"StaticCamera", pGameObject), E_FAIL);

	pGameObject = CTerrain::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Terrain", pGameObject), E_FAIL);

	pGameObject = CSkyBox::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"SkyBox", pGameObject), E_FAIL);

	pGameObject = CShotParticle::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"ShotParticle", pGameObject), E_FAIL);

	pGameObject = CBulletParticle::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"BulletParticle", pGameObject), E_FAIL);

	pGameObject = CItemParticle::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"ItemParticle", pGameObject), E_FAIL);

	pGameObject = CFlameEffect::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"FlameEffect", pGameObject), E_FAIL);

	pGameObject = CIceEffect::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"IceEffect", pGameObject), E_FAIL);

	pGameObject = CSparkEffect::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"SparkEffect", pGameObject), E_FAIL);

	pGameObject = CSoundWave::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"SoundWave", pGameObject), E_FAIL);

	pGameObject = CCloudEffect::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CloudEffect", pGameObject), E_FAIL);

	pGameObject = CBrownCloudEffect::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"BrownCloudEffect", pGameObject), E_FAIL);

	pGameObject = CRainbowCloudEffect::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"RainbowCloudEffect", pGameObject), E_FAIL);

	pGameObject = CBubbleEffect::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"BubbleEffect", pGameObject), E_FAIL);

	pGameObject = CMonsterParticle::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MonsterParticle", pGameObject), E_FAIL);

	pGameObject = CProjectileParticle::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"ProjectileParticle", pGameObject), E_FAIL);

	// KEY 추가해야함
	// X: 8 Z : 65

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_GameLogic(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_UI(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	pGameObject = CPlayerUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"PlayerUI", pGameObject), E_FAIL);

	pGameObject = CPlayerFaceUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"PlayerFaceUI", pGameObject), E_FAIL);

	pGameObject = CPlayerHpUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"PlayerHpUI", pGameObject), E_FAIL);

	pGameObject = CPlayerDefenseUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"PlayerDefenseUI", pGameObject), E_FAIL);

	pGameObject = CWeaponUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"WeaponUI", pGameObject), E_FAIL);

	pGameObject = CBulletUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"BulletUI", pGameObject), E_FAIL);

	pGameObject = CGunUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"GunUI", pGameObject), E_FAIL);

	pGameObject = CMonsterUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MonsterUI", pGameObject), E_FAIL);

	pGameObject = CHitBarUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"HitBarUI", pGameObject), E_FAIL);

	pGameObject = CComboUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"ComboUI", pGameObject), E_FAIL);

	pGameObject = CShop::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Shop", pGameObject), E_FAIL);

	pGameObject = CCrossHeader::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CrossHeader", pGameObject), E_FAIL);

	pGameObject = CInventory::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"InventoryUI", pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_Wall(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	HANDLE      hFile = CreateFile(L"../../Data/Map1.dat",      // 파일의 경로와 이름
		GENERIC_READ,									 // 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
		NULL,               // 공유 방식(파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가)    
		NULL,               // 보안 속성(NULL을 지정하면 기본값 상태)
		OPEN_EXISTING,         // CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING  : 파일이 있을 경우에만 열기
		FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등) : FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
		NULL);               // 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니깐 NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return E_FAIL;
	}

	DWORD   dwByte = 0;

	_vec3   vRight, vUp, vLook, vPos, vScale, vAngle;
	_int	iDrawIndex = 0;
	CLayer* pMyLayer = nullptr;

	while (true)
	{
		ReadFile(hFile, &vRight, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vUp, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vLook, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vPos, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vScale, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vAngle, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &iDrawIndex, sizeof(_int), &dwByte, nullptr);

		_tchar* Load_Name = new _tchar[20];
		wstring t = L"Test%d";
		wsprintfW(Load_Name, t.c_str(), m_iIndex);
		NameList.push_back(Load_Name);

		pGameObject = CTestCube::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameObject(Load_Name, pGameObject), E_FAIL);

		pGameObject->Set_DrawTexIndex(iDrawIndex);
		++m_iIndex;

		CTransform* Transcom = dynamic_cast<CTransform*>(pGameObject->Get_Component(TRANSFORM_COMP, ID_DYNAMIC));

		Transcom->Set_Info(INFO_RIGHT, &vRight);
		Transcom->Set_Info(INFO_UP, &vUp);
		Transcom->Set_Info(INFO_LOOK, &vLook);
		Transcom->Set_Info(INFO_POS, &vPos);
		Transcom->Set_Angle(&vAngle);
		Transcom->Set_Scale(&vScale);

		Transcom->Update_Component(0.01f);

		if (0 == dwByte)
			break;
	}
	CloseHandle(hFile);

	pGameObject = CCubeShop::Create(m_pGraphicDev, _vec3(15.f, 0.f, 10.f));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CubeShop1", pGameObject), E_FAIL);

	pGameObject = CCubeShop::Create(m_pGraphicDev, _vec3(79.f, 0.f, 41.f));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CubeShop2", pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_Character(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

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

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_Monster(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	// 위랑 아래랑 같아야함 문자열, 몬스터 아이템 땜시
	srand((unsigned int)time(NULL));
	// 0  42
	// 18 59
	//{
	//	for (int i = 0; i < 2; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Zombie_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CZombie::Create(m_pGraphicDev, _vec3(_float(rand() % 18) + 2, 0.6f, _float(rand() % 17 + 44)), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 0; i < 1; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Fireman_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CFireMan::Create(m_pGraphicDev, _vec3(_float(rand() % 18) + 2, 0.6f, _float(rand() % 17) + 44), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 0; i < 2; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Slime_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CSlime::Create(m_pGraphicDev, _vec3(_float(rand() % 18) + 2, 0.6f, _float(rand() % 17) + 44), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 0; i < 1; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Illusioner%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);
	//		pGameObject = CIllusioner::Create(m_pGraphicDev, _vec3(_float(rand() % 18) + 2, 0.6f, _float(rand() % 17) + 44), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}
	//}

	//// 15 ~ 64
	//// 1 ~ 88
	//{
	//	for (int i = 2; i < 4; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Zombie_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CZombie::Create(m_pGraphicDev, _vec3(_float(rand() % 14 + 1), 0.6f, _float(rand() % 64) + 24), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 1; i < 3; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Fireman_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CFireMan::Create(m_pGraphicDev, _vec3(_float(rand() % 14 + 1), 0.6f, _float(rand() % 64) + 24), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 2; i < 4; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Slime_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CSlime::Create(m_pGraphicDev, _vec3(_float(rand() % 14) + 1, 0.6f, _float(rand() % 64) + 24), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 1; i < 3; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Illusioner%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);
	//		pGameObject = CIllusioner::Create(m_pGraphicDev, _vec3(_float(rand() % 14 + 1), 0.6f, _float(rand() % 64) + 24), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}
	//}

	//// 1 ~ 101 
	//// 10 ~ 116
	//{
	//	for (int i = 4; i < 5; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Zombie_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CZombie::Create(m_pGraphicDev, _vec3(_float(rand() % 9 + 1), 0.6f, _float(rand() % 15) + 101), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 3; i < 4; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Fireman_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CFireMan::Create(m_pGraphicDev, _vec3(_float(rand() % 9 + 1), 0.6f, _float(rand() % 15) + 101), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 4; i < 5; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Slime_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CSlime::Create(m_pGraphicDev, _vec3(_float(rand() % 9) + 1, 0.6f, _float(rand() % 15) + 101), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 3; i < 4; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Illusioner%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);
	//		pGameObject = CIllusioner::Create(m_pGraphicDev, _vec3(_float(rand() % 9 + 1), 0.6f, _float(rand() % 15) + 101), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}
	//}
	//
	//// 26 ~ 125
	//// 16 ~ 117
	//{
	//	for (int i = 5; i < 6; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Zombie_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CZombie::Create(m_pGraphicDev, _vec3(_float(rand() % 10 + 16), 0.6f, _float(rand() % 8) + 117), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 4; i < 5; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Fireman_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CFireMan::Create(m_pGraphicDev, _vec3(_float(rand() % 10 + 16), 0.6f, _float(rand() % 8) + 117), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 5; i < 6; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Slime_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CSlime::Create(m_pGraphicDev, _vec3(_float(rand() % 10 + 16), 0.6f, _float(rand() % 8) + 117), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 4; i < 5; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Illusioner%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);
	//		pGameObject = CIllusioner::Create(m_pGraphicDev, _vec3(_float(rand() % 10 + 16), 0.6f, _float(rand() % 8) + 117), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}
	//}

	//// 48 ~ 103
	//// 61 ~ 114
	//{
	//	for (int i = 6; i < 7; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Zombie_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CZombie::Create(m_pGraphicDev, _vec3(_float(rand() % 13 + 48), 0.6f, _float(rand() % 11) + 103), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 5; i < 6; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Fireman_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CFireMan::Create(m_pGraphicDev, _vec3(_float(rand() % 13 + 48), 0.6f, _float(rand() % 11) + 103), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 6; i < 7; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Slime_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CSlime::Create(m_pGraphicDev, _vec3(_float(rand() % 13 + 48), 0.6f, _float(rand() % 11) + 103), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 5; i < 6; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Illusioner%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);
	//		pGameObject = CIllusioner::Create(m_pGraphicDev, _vec3(_float(rand() % 13 + 48), 0.6f, _float(rand() % 11) + 103), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}
	//}

	//// 43 - 96
	//// 52 - 79
	//{
	//	for (int i = 7; i < 9; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Zombie_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CZombie::Create(m_pGraphicDev, _vec3(_float(rand() % 9 + 43), 0.6f, _float(rand() % 17) + 76), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 6; i < 8; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Fireman_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CFireMan::Create(m_pGraphicDev, _vec3(_float(rand() % 9 + 43), 0.6f, _float(rand() % 17) + 76), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 7; i < 9; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Slime_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CSlime::Create(m_pGraphicDev, _vec3(_float(rand() % 9 + 43), 0.6f, _float(rand() % 17) + 76), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 6; i < 8; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Illusioner%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);
	//		pGameObject = CIllusioner::Create(m_pGraphicDev, _vec3(_float(rand() % 9 + 43), 0.6f, _float(rand() % 17) + 76), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}
	//}


	//// 43 - 5
	//// 55 - 23
	//{
	//	for (int i = 9; i < 11; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Zombie_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CZombie::Create(m_pGraphicDev, _vec3(_float(rand() % 12 + 43), 0.6f, _float(rand() % 18) + 5), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 8; i < 10; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Fireman_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CFireMan::Create(m_pGraphicDev, _vec3(_float(rand() % 12 + 43), 0.6f, _float(rand() % 18) + 5), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 9; i < 11; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Slime_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);

	//		pGameObject = CSlime::Create(m_pGraphicDev, _vec3(_float(rand() % 12 + 43), 0.6f, _float(rand() % 18) + 5), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}

	//	for (int i = 8; i < 10; i++)
	//	{
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"Illusioner%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);
	//		pGameObject = CIllusioner::Create(m_pGraphicDev, _vec3(_float(rand() % 12 + 43), 0.6f, _float(rand() % 18) + 5), szName);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	//	}
	//}

	pGameObject = CMiddleBoss::Create(m_pGraphicDev, _vec3(109.f, 0.6f, 10.f), L"MiddleBoss");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

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

HRESULT CStage::Ready_Layer_PlayerBullet(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_Mapping(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	pGameObject = CBaseMapping::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"BaseMapping", pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_Gun(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	pGameObject = CUzi::Create(m_pGraphicDev);
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

	pGameObject = CSniper::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"SNIPER", pGameObject), E_FAIL);

	pGameObject = CSniperPart1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Sniper_Part_1", pGameObject), E_FAIL);

	pGameObject = CSniperPart2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Sniper_Part_2", pGameObject), E_FAIL);

	pGameObject = CSniperPart3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Sniper_Part_3", pGameObject), E_FAIL);

	pGameObject = CSniperPart4::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Sniper_Part_4", pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_Item(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_GunItem(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	pGameObject = CGetUzi::Create(m_pGraphicDev, _vec3(10.f, 0.6f, 20.f));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"GetUzi", pGameObject), E_FAIL);

	pGameObject = CGetShotgun::Create(m_pGraphicDev, _vec3(13.87f, 0.8f, 111.3f));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"GetShotgun", pGameObject), E_FAIL);

	pGameObject = CGetSniper::Create(m_pGraphicDev, _vec3(47.f, 0.6f, 104.f));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"GetSniper", pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_DestroyWall(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_Skill(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_Creature(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	pGameObject = CBattleCursier::Create(m_pGraphicDev, _vec3(10, 20, -10), _vec3(0, 0, 1), L"BATTLECRUISER1");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

	pGameObject = CBattleCursier::Create(m_pGraphicDev, _vec3(20, 20, -5), _vec3(0, 0, 1), L"BATTLECRUISER2");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

	pGameObject = CBattleCursier::Create(m_pGraphicDev, _vec3(30, 20, -10), _vec3(0, 0, 1), L"BATTLECRUISER3");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

	pGameObject = CFlight::Create(m_pGraphicDev, _vec3(0, 30, 100), _vec3(0, 0, -2), L"FLIGHT1");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

	pGameObject = CFlight::Create(m_pGraphicDev, _vec3(10, 30, 100), _vec3(0, 0, -2), L"FLIGHT2");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

	pGameObject = CFlight::Create(m_pGraphicDev, _vec3(20, 30, 100), _vec3(0, 0, -2), L"FLIGHT3");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

	pGameObject = CFlight::Create(m_pGraphicDev, _vec3(30, 30, 100), _vec3(0, 0, -2), L"FLIGHT4");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

	pGameObject = CFlight::Create(m_pGraphicDev, _vec3(40, 30, 100), _vec3(0, 0, -2), L"FLIGHT5");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_Player(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_Slime(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_Trap(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	{
		pGameObject = CThorn::Create(m_pGraphicDev, _vec3(33.f, 0.f, 60.f), L"Thorn1");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CThorn::Create(m_pGraphicDev, _vec3(35.f, 0.f, 60.f), L"Thorn2");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CThorn::Create(m_pGraphicDev, _vec3(37.f, 0.f, 60.f), L"Thorn3");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CThorn::Create(m_pGraphicDev, _vec3(38.f, 0.f, 120.5f), L"Thorn4");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CThorn::Create(m_pGraphicDev, _vec3(38.f, 0.f, 122.5f), L"Thorn5");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CThorn::Create(m_pGraphicDev, _vec3(38.f, 0.f, 124.5f), L"Thorn6");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CThorn::Create(m_pGraphicDev, _vec3(38.f, 0.f, 126.5f), L"Thorn7");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CThorn::Create(m_pGraphicDev, _vec3(64.f, 0.f, 40.5f), L"Thorn8");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CThorn::Create(m_pGraphicDev, _vec3(64.f, 0.f, 42.5f), L"Thorn9");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CThorn::Create(m_pGraphicDev, _vec3(64.f, 0.f, 44.5f), L"Thorn10");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CThorn::Create(m_pGraphicDev, _vec3(64.f, 0.f, 46.5f), L"Thor11");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	}

	{
		pGameObject = CMagma::Create(m_pGraphicDev, _vec3(47.f, 0.f, 122.5f), L"MAGMA3");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CMagma::Create(m_pGraphicDev, _vec3(55.f, 0.f, 125.f), L"MAGMA4");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CMagma::Create(m_pGraphicDev, _vec3(62.f, 0.f, 126.f), L"MAGMA6");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CMagma::Create(m_pGraphicDev, _vec3(65.f, 0.f, 122.5f), L"MAGMA7");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CMagma::Create(m_pGraphicDev, _vec3(71.f, 0.f, 125.f), L"MAGMA8");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CMagma::Create(m_pGraphicDev, _vec3(45.f, 0.f, 17.f), L"MAGMA9");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CMagma::Create(m_pGraphicDev, _vec3(47.f, 0.f, 11.f), L"MAGMA10");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CMagma::Create(m_pGraphicDev, _vec3(55.f, 0.f, 20.5f), L"MAGMA11");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	}

	{
		pGameObject = CItemBox::Create(m_pGraphicDev, _vec3(25.f, 0.3f, 65.f), L"ITEMBOX1");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CItemBox::Create(m_pGraphicDev, _vec3(47.f, 0.3f, 109.f), L"ITEMBOX2");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	}

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_Supporter(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	pGameObject = CSupporter_Uzi::Create(m_pGraphicDev, _vec3(20.f, 0.5f, 20.f), L"SUPPORT_UZI");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CStage::Ready_Layer_Zombie(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

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
	for (auto iter : NameList)
	{
		Safe_Delete_Array(iter);
	}
}
