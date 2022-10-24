#include "stdafx.h"
#include "FinalStage.h"

#include "Export_Function.h"

#include "Wall.h"
#include "TestCube.h"

#include "AnimationPlayer.h"
#include "FlightCamera.h"

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
#include "Warning_AnnihilateUI.h"
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

#include "MonsterParticle.h"
#include "ProjectileParticle.h"
#include "FlameEffect.h"
#include "IceEffect.h"
#include "BubbleEffect.h"
#include "SparkEffect.h"
#include "SoundWave.h"
#include "CloudEffect.h"
#include "BrownCloudEffect.h"
#include "Illusioner.h"
#include "EveryParticle.h"

#include "Thorn.h"
#include "Magma.h"
#include "ItemBox.h"
#include "Terret.h"

#include "Supporter_Uzi.h"
#include "Supporter_Shotgun.h"
#include "Supporter_Sniper.h"

#include "MiddleBoss.h"
#include "KrakenBoss.h"
#include "BattleCursier.h"
#include "FlightBulletParticle.h"
#include "Flight.h"
#include "Key.h"
#include "FlightSpot.h"
#include "Mob.h"

#include "KrakenLeg.h"
#include "Npc.h"
#include "DeadParticle.h"
CFinalStage::CFinalStage(LPDIRECT3DDEVICE9 pGraphicDev)
	:CScene(pGraphicDev)
{
}

CFinalStage::~CFinalStage()
{
}

HRESULT CFinalStage::Ready_Scene(void)
{
	if (FAILED(Engine::CScene::Ready_Scene()))
		return E_FAIL;

	CGameObject*		pGameObject = nullptr;

	//_float fBGMSound = 1.f;
	//PlayBGM(L"Track_01.mp3", fBGMSound);

	Set_SceneId(FINAL_SCENE);

	FAILED_CHECK_RETURN(Ready_Light(), E_FAIL);

	Load_Position(GUN, L"../../Data/GunPos.dat");
	Load_Position(SHOP, L"../../Data/ShopPos.dat");
	Load_Position(LAVA, L"../../Data/LavaPos.dat");
	Load_Position(ITEMBOX, L"../../Data/ItemPos.dat");
	Load_Position(THRONE, L"../../Data/ThronePos.dat");
	Load_Position(SLIME, L"../../Data/SlimePos.dat");
	Load_Position(FIREMAN, L"../../Data/FireManPos.dat");
	Load_Position(ZOMBIE, L"../../Data/ZombiePos.dat");
	Load_Position(ILLUSIONER, L"../../Data/IllusionerPos.dat");

	FAILED_CHECK_RETURN(Ready_Layer_Environment(STAGE_ENVIRONMENT), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_GameLogic(STAGE_GAMELOGIC), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(STAGE_UI), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Character(STAGE_CHARACTER), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Monster(STAGE_MONSTER), E_FAIL);		//	���� ��ü ���� ���̾�
	FAILED_CHECK_RETURN(Ready_Layer_Mapping(STAGE_MAPPING), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Bullet(STAGE_BULLET), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Wall(STAGE_WALL), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Item(STAGE_ITEM), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Gun(STAGE_GUN), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_GunItem(STAGE_GUNITEM), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Player(STAGE_PLAYER), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_DestroyWall(STAGE_DESTORYWALL), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Skill(STAGE_SKILL), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_SkillCruiser(STAGE_SKILLCRUISER), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Layer_Trap(STAGE_TRAP), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Supporter(STAGE_SUPPORTER), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_PlayerBullet(STAGE_BULLETPLAYER), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_ExBullet(STAGE_EXBULLET), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Creature(STAGE_CREATURE), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_PlayerFlight(STAGE_FLIGHTPLAYER), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_KraKenBullet(STAGE_KRAKENBULLET), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Tentacle(STAGE_TENTACLE), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Laser(STAGE_LASER), E_FAIL);

	dynamic_cast<CInventory*>(Engine::Get_GameObject(STAGE_UI, L"InventoryUI"))->WeaponCreate(2);
	dynamic_cast<CInventory*>(Engine::Get_GameObject(STAGE_UI, L"InventoryUI"))->WeaponCreate(3);
	dynamic_cast<CInventory*>(Engine::Get_GameObject(STAGE_UI, L"InventoryUI"))->WeaponCreate(4);

	CGameObject* pShuttle = nullptr;
	pShuttle = Engine::Get_GameObject(STAGE_FLIGHTPLAYER, L"FLIGHTSHUTTLE");

	return S_OK;
}

_int CFinalStage::Update_Scene(const _float & fTimeDelta)
{
	return Engine::CScene::Update_Scene(fTimeDelta);
}

void CFinalStage::LateUpdate_Scene(void)
{
	Engine::CScene::LateUpdate_Scene();
}

void CFinalStage::Render_Scene(void)
{
}

HRESULT CFinalStage::Ready_Layer_Environment(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	pGameObject = CFlightSpot::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"FlightSpot", pGameObject), E_FAIL);

	pGameObject = CFlightCamera::Create(m_pGraphicDev, &_vec3(0.f, 0.f, 0.f), &_vec3(1.f, 0.f, 0.f), &_vec3(0.f, 1.f, 0.f));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"FlightCamera", pGameObject), E_FAIL);

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

	pGameObject = CTriggerParticle::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TriggerParticle", pGameObject), E_FAIL);

	pGameObject = CTriggerFront::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TriggerFront", pGameObject), E_FAIL);

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

	pGameObject = CRainbowCloudEffect::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"RainbowCloudEffect", pGameObject), E_FAIL);

	pGameObject = CBrownCloudEffect::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"BrownCloudEffect", pGameObject), E_FAIL);

	pGameObject = CBubbleEffect::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"BubbleEffect", pGameObject), E_FAIL);

	pGameObject = CMonsterParticle::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MonsterParticle", pGameObject), E_FAIL);

	pGameObject = CProjectileParticle::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"ProjectileParticle", pGameObject), E_FAIL);

	pGameObject = CFlightBulletParticle::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"FlightBulletParticle", pGameObject), E_FAIL);

	pGameObject = CCubeParticle::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CubeParticle", pGameObject), E_FAIL);

	pGameObject = CVerticalLine::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"VerticalLine", pGameObject), E_FAIL);

	pGameObject = CTraceEffect::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TraceEffect", pGameObject), E_FAIL);

	pGameObject = CRoundEffect::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"RoundEffect", pGameObject), E_FAIL);

	pGameObject = CLaserEffect::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LaserEffect", pGameObject), E_FAIL);

	pGameObject = CLaserPoint::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"LaserPoint", pGameObject), E_FAIL);

	pGameObject = CDefensiveEffect::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"DefensiveEffect", pGameObject), E_FAIL);

	pGameObject = CDashCube::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"DashCube", pGameObject), E_FAIL);


	pGameObject = CKrakenParticle::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"KrakenParticle", pGameObject), E_FAIL);

	pGameObject = CKrakenEffect::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"KraKenEffect", pGameObject), E_FAIL);


	pGameObject = CKrakenHit::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"KrakenHit", pGameObject), E_FAIL);

	pGameObject = CCartridgeParticle::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CartridgeParticle", pGameObject), E_FAIL);

	/*pGameObject = CNpc::Create(m_pGraphicDev, _vec3(14.f, 0.5f, 10.f));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"NPC", pGameObject), E_FAIL);*/


	pGameObject = CDeadParticle::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"DeadParticle", pGameObject), E_FAIL);
	m_mapLayer.insert({ pLayerTag, pLayer });

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_GameLogic(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });
	pGameObject = CExBulletEffect::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"ExBulletEffect", pGameObject), E_FAIL);

	pGameObject = CMBLaser::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MBLaser", pGameObject), E_FAIL);
	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_UI(const _tchar * pLayerTag)
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

	pGameObject = CWarning_AnnihilateUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(WARNING_TEX, pGameObject), E_FAIL);
	
	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_Wall(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	//HANDLE      hFile = CreateFile(L"../../Data/Map1.dat",      // ������ ��ο� �̸�
	//	GENERIC_READ,									 // ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
	//	NULL,               // ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�)    
	//	NULL,               // ���� �Ӽ�(NULL�� �����ϸ� �⺻�� ����)
	//	OPEN_EXISTING,         // CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING  : ������ ���� ��쿡�� ����
	//	FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��) : FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
	//	NULL);               // ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��ϱ� NULL)

	//if (INVALID_HANDLE_VALUE == hFile)
	//{
	//	return E_FAIL;
	//}

	//DWORD   dwByte = 0;

	//_vec3   vRight, vUp, vLook, vPos, vScale, vAngle;
	//_int	iDrawIndex = 0;
	//CLayer* pMyLayer = nullptr;

	//while (true)
	//{
	//	ReadFile(hFile, &vRight, sizeof(_vec3), &dwByte, nullptr);
	//	ReadFile(hFile, &vUp, sizeof(_vec3), &dwByte, nullptr);
	//	ReadFile(hFile, &vLook, sizeof(_vec3), &dwByte, nullptr);
	//	ReadFile(hFile, &vPos, sizeof(_vec3), &dwByte, nullptr);
	//	ReadFile(hFile, &vScale, sizeof(_vec3), &dwByte, nullptr);
	//	ReadFile(hFile, &vAngle, sizeof(_vec3), &dwByte, nullptr);
	//	ReadFile(hFile, &iDrawIndex, sizeof(_int), &dwByte, nullptr);

	//	_tchar* Load_Name = new _tchar[20];
	//	wstring t = L"Test%d";
	//	wsprintfW(Load_Name, t.c_str(), m_iIndex);
	//	NameList.push_back(Load_Name);

	//	pGameObject = CTestCube::Create(m_pGraphicDev);
	//	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//	FAILED_CHECK_RETURN(pLayer->Add_GameObject(Load_Name, pGameObject), E_FAIL);

	//	pGameObject->Set_DrawTexIndex(iDrawIndex);
	//	++m_iIndex;

	//	CTransform* Transcom = dynamic_cast<CTransform*>(pGameObject->Get_Component(TRANSFORM_COMP, ID_DYNAMIC));

	//	Transcom->Set_Info(INFO_RIGHT, &vRight);
	//	Transcom->Set_Info(INFO_UP, &vUp);
	//	Transcom->Set_Info(INFO_LOOK, &vLook);
	//	Transcom->Set_Info(INFO_POS, &vPos);
	//	Transcom->Set_Angle(&vAngle);
	//	Transcom->Set_Scale(&vScale);

	//	Transcom->Update_Component(0.01f);

	//	if (0 == dwByte)
	//		break;
	//}
	//CloseHandle(hFile);

	//if (!vecShop.empty())
	//{
	//	for (size_t i = 0; i < vecShop.size(); i++)
	//	{
	//		_vec3 vShop = { 0.f,0.5f,0.f };
	//		_tchar* szName = new _tchar[256]{};
	//		wstring wName = L"CubeShop_%d";
	//		wsprintfW(szName, wName.c_str(), i);
	//		NameList.push_back(szName);
	//		pGameObject = CCubeShop::Create(m_pGraphicDev, vecShop[i] + vShop);
	//		NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//		FAILED_CHECK_RETURN(pLayer->Add_GameObject(szName, pGameObject), E_FAIL);
	//	}
	//}

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_Character(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	//	�Ӹ�
	pGameObject = CCubeHead::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"HEAD", pGameObject), E_FAIL);
	//	����
	pGameObject = CCubeBody::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"BODY", pGameObject), E_FAIL);
	//	����
	pGameObject = CCubeArm::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"L_ARM", pGameObject), E_FAIL);
	//	������
	pGameObject = CCubeArm::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"R_ARM", pGameObject), E_FAIL);
	//	�޴ٸ�
	pGameObject = CCubeLeg::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"L_LEG", pGameObject), E_FAIL);
	//	�����ٸ�
	pGameObject = CCubeLeg::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"R_LEG", pGameObject), E_FAIL);
	//	�޼�
	pGameObject = CCubeHand::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"L_HAND", pGameObject), E_FAIL);
	//	������
	pGameObject = CCubeHand::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"R_HAND", pGameObject), E_FAIL);
	//	�޹�
	pGameObject = CCubeFoot::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"L_FOOT", pGameObject), E_FAIL);
	//	������
	pGameObject = CCubeFoot::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"R_FOOT", pGameObject), E_FAIL);
	//	������ ��Ʈ�ڽ�
	pGameObject = CCubePlayer::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CCubePlayer*>(pGameObject)->Capture_Uzi();
	dynamic_cast<CCubePlayer*>(pGameObject)->Capture_Shotgun();
	dynamic_cast<CCubePlayer*>(pGameObject)->Capture_Sniper();
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"PLAYER", pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_Monster(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	/*if (!vecFireMan.empty())
	{
	for (size_t i = 0; i < vecFireMan.size(); i++)
	{
	_tchar* szName = new _tchar[256]{};
	wstring wName = L"Fireman_%d";
	wsprintfW(szName, wName.c_str(), i);
	NameList.push_back(szName);
	pGameObject = CFireMan::Create(m_pGraphicDev, vecFireMan[i], szName);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	}
	}

	if (!vecSlime.empty())
	{
	for (size_t i = 0; i < vecSlime.size(); i++)
	{
	_tchar* szName = new _tchar[256]{};
	wstring wName = L"Slime_%d";
	wsprintfW(szName, wName.c_str(), i);
	NameList.push_back(szName);
	pGameObject = CSlime::Create(m_pGraphicDev, vecSlime[i], szName);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	}
	}

	pGameObject = CMiddleBoss::Create(m_pGraphicDev, _vec3(109.f, 0.6f, 10.f), L"MiddleBoss");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);*/

	pGameObject = CKrakenBoss::Create(m_pGraphicDev, _vec3(65.f, 10.f, 65.f), L"Kraken");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

	//pGameObject = CMob::Create(m_pGraphicDev, _vec3(10.f, 0.6f, 10.f), L"Mob");
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_Bullet(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_PlayerBullet(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_ExBullet(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_Laser(const _tchar * pLayerTag)
{
	Engine::CLayer*      pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*      pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_Tentacle(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	{
		pGameObject = CKrakenLeg::Create(m_pGraphicDev, _vec3(95.f, -50.f, 35.f), L"LEG_1");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CKrakenLeg::Create(m_pGraphicDev, _vec3(95.f, -50.f, 65.f), L"LEG_2");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CKrakenLeg::Create(m_pGraphicDev, _vec3(95.f, -50.f, 95.f), L"LEG_3");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CKrakenLeg::Create(m_pGraphicDev, _vec3(65.f, -50.f, 35.f), L"LEG_4");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CKrakenLeg::Create(m_pGraphicDev, _vec3(65.f, -50.f, 95.f), L"LEG_5");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CKrakenLeg::Create(m_pGraphicDev, _vec3(35.f, -50.f, 35.f), L"LEG_6");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CKrakenLeg::Create(m_pGraphicDev, _vec3(35.f, -50.f, 65.f), L"LEG_7");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

		pGameObject = CKrakenLeg::Create(m_pGraphicDev, _vec3(35.f, -50.f, 95.f), L"LEG_8");
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);
	}

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_Mapping(const _tchar * pLayerTag)
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

HRESULT CFinalStage::Ready_Layer_Gun(const _tchar * pLayerTag)
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

HRESULT CFinalStage::Ready_Layer_Item(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_GunItem(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	/*if (!vecGun.empty())
	{
	_vec3 vTemp = _vec3(1.f, 0.5f, 0.f);

	pGameObject = CGetShotgun::Create(m_pGraphicDev, vecGun[1] + vTemp);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"GetShotgun", pGameObject), E_FAIL);

	pGameObject = CGetUzi::Create(m_pGraphicDev, vecGun[0] + vTemp);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"GetUzi", pGameObject), E_FAIL);

	pGameObject = CGetSniper::Create(m_pGraphicDev, vecGun[2] + vTemp);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"GetSniper", pGameObject), E_FAIL);
	}*/

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_DestroyWall(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_Skill(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;


	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_SkillCruiser(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	pGameObject = CBattleCursier::Create(m_pGraphicDev, _vec3(10, 20, -10), _vec3(0, 0, 1), L"BattleCruiser_Skill");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CBattleCursier*>(pGameObject)->Random();
	FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_Creature(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_Player(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_Slime(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_Trap(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_Supporter(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	pGameObject = CSupporter_Uzi::Create(m_pGraphicDev, _vec3(15.f, 10.f, 15.f), L"SUPPORTER_UZI");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"SUPPORTER_UZI", pGameObject), E_FAIL);

	pGameObject = CSupporter_Shotgun::Create(m_pGraphicDev, _vec3(20.f, 10.f, 15.f), L"SUPPORTER_SHOTGUN");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"SUPPORTER_SHOTGUN", pGameObject), E_FAIL);

	pGameObject = CSupporter_Sniper::Create(m_pGraphicDev, _vec3(25.f, 10.f, 15.f), L"SUPPORTER_SNIPER");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"SUPPORTER_SNIPER", pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_PlayerFlight(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	pGameObject = CFlight::Create(m_pGraphicDev, _vec3(0, 30, 100), _vec3(0, 0, -2), L"FLIGHTPLAYER_ANI");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CFlight*>(pGameObject)->Random();
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"FLIGHTPLAYER", pGameObject), E_FAIL);

	pGameObject = CFlight::Create(m_pGraphicDev, _vec3(0, 30, 100), _vec3(0, 0, -2), L"FLIGHTPLAYER_ANI2");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	dynamic_cast<CFlight*>(pGameObject)->Random();
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"FLIGHTSHUTTLE", pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

HRESULT CFinalStage::Ready_Light(void)
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

HRESULT CFinalStage::Load_Position(OBJECT_ID eID, wstring strDirectory)
{
	HANDLE      hFile = CreateFile(strDirectory.c_str(),      // ������ ��ο� �̸�
		GENERIC_READ,									 // ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
		NULL,               // ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�)    
		NULL,               // ���� �Ӽ�(NULL�� �����ϸ� �⺻�� ����)
		OPEN_EXISTING,         // CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING  : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��) : FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
		NULL);               // ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��ϱ� NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return E_FAIL;
	}

	DWORD   dwByte = 0;

	_vec3   vRight, vUp, vLook, vPos, vScale, vAngle;

	while (true)
	{
		ReadFile(hFile, &vRight, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vUp, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vLook, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vPos, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vScale, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vAngle, sizeof(_vec3), &dwByte, nullptr);

		switch (eID)
		{
		case Engine::GUN:
			vecGun.push_back(vPos);
			break;
		case Engine::SHOP:
			vecShop.push_back(vPos);
			break;
		case Engine::LAVA:
			vecLava.push_back(vPos);
			break;
		case Engine::ITEMBOX:
			vecItem.push_back(vPos);
			break;
		case Engine::THRONE:
			vecThrone.push_back(vPos);
			break;
		case Engine::SLIME:
			vecSlime.push_back(vPos);
			break;
		case Engine::FIREMAN:
			vecFireMan.push_back(vPos);
			break;
		case Engine::ZOMBIE:
			vecZombie.push_back(vPos);
			break;
		case Engine::ILLUSIONER:
			vecIllusioner.push_back(vPos);
			break;
		default:
			break;
		}

		if (0 == dwByte)
			break;
	}
	CloseHandle(hFile);

	return S_OK;
}

HRESULT CFinalStage::Ready_Layer_KraKenBullet(const _tchar * pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CGameObject*		pGameObject = nullptr;

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}

CFinalStage * CFinalStage::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFinalStage *	pInstance = new CFinalStage(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CFinalStage::Free(void)
{
	CScene::Free();
	for (auto iter : NameList)
	{
		Safe_Delete_Array(iter);
	}
}