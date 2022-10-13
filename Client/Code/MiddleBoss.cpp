#include "stdafx.h"
#include "..\Header\MiddleBoss.h"
#include "PoolMgr.h"
#include "ObtainBullet.h"
#include "ObtainDefense.h"
#include "HealthPotion.h"
#include "MonsterUI.h"
#include "CubePlayer.h"
#include "Weapon.h"
#include "ComboUI.h"
#include "MonsterMapping.h"
#include "TransAxisBox.h"
static _int m_iCnt = 0;

CMiddleBoss::CMiddleBoss(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}


CMiddleBoss::~CMiddleBoss()
{
}

HRESULT CMiddleBoss::Ready_Object(const _vec3 & vPos, _tchar * Name)
{
	m_tAbility = new MIDDLEBOSSABILITY;
	m_tAbility->fMaxHp = 200.f;
	m_tAbility->fCurrentHp = m_tAbility->fMaxHp;
	m_tAbility->fDamage = 5.f;
	m_tAbility->strObjTag = L"MiddleBoss";
	m_fDetectRange = 30.f;

	m_MonsterName = Name;


	m_STATE = MIDDLEBOSS_IDLE;
	m_BeforeState = MIDDLEBOSS_IDLE;
	m_WALK = MIDDLEBOSSWALK_START;
	m_IDLE = MIDDLEBOSSIDLE_1;
	m_ATTACK = MIDDLEBOSSATTACK_START;
	m_SHOT = MIDDLEBOSSSHOT_START;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	//크기 설정 및 위치설정.
	m_pTransCom->Set_Scale(&_vec3(1.f, 1.f, 1.f));
	m_pTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pTransCom->Static_Update();


	//UI가져와야하고 
	m_pTransUICom->Set_Scale(3.f, 1.f, 1.5f);
	

	_vec3 vAnimationPos;
	m_pTransCom->Get_Info(INFO_POS, &vAnimationPos);


	//애니메이션 넣으려면 나중에 이쪽에 넣어주어야한다. 
	m_pHitBoxTransCom->Set_Scale(&_vec3(1.f, 1.f, 1.f));
	m_pHitBoxTransCom->Set_Pos(vAnimationPos.x, vAnimationPos.y, vAnimationPos.z);
	m_pHitBoxTransCom->Static_Update();

	m_pSphereTransCom->Set_Scale(&_vec3(30.f, 30.f, 30.f));
	m_pSphereTransCom->Set_Pos(vAnimationPos.x, vAnimationPos.y, vAnimationPos.z);
	m_pSphereTransCom->Static_Update();


	m_pSearchRange_TransCom->Set_Scale(&_vec3(20.f, 20.f, 20.f));
	m_pSearchRange_TransCom->Set_Pos(vAnimationPos.x, vAnimationPos.y, vAnimationPos.z);
	m_pSearchRange_TransCom->Static_Update();

	m_pAttackRange_TransCom->Set_Scale(&_vec3(15.f, 15.f, 15.f));
	m_pAttackRange_TransCom->Set_Pos(vAnimationPos.x, vAnimationPos.y, vAnimationPos.z);
	m_pAttackRange_TransCom->Static_Update();





	return S_OK;
}

_int CMiddleBoss::Update_Object(const _float & fTimeDelta)
{

	if (m_bDead)
	{
		Create_Item();
		m_pComboUI->KillCntPlus();
		Monster_DeleteMapping();
		_float fMiddle_death = 1.5f;
		PlaySoundGun(L"Middle_Death.wav", SOUND_EFFECT, fMiddle_death);

		return -1;
	}

	m_fTimeDelta = fTimeDelta;

	if (m_bFirst)
	{
		m_bFirst = false;
		Engine::Get_Scene()->New_Layer(m_MonsterName);
		pMyLayer = Engine::Get_Layer(m_MonsterName);
		FAILED_CHECK_RETURN(Build(), -1);

		Load_Animation(L"../../Data/MiddleMonster/MIDDLE_IDLE2.dat", 0);
		Load_Animation(L"../../Data/MiddleMonster/MIDDLE_IDLE3.dat", 1);

		Load_Animation(L"../../Data/MiddleMonster/MIDDLE_STARTING.dat", 2);
		Load_Animation(L"../../Data/MiddleMonster/MIDDLE_WALKING11.dat", 3);
		Load_Animation(L"../../Data/MiddleMonster/MIDDLE_WALKING12.dat", 4);

		Load_Animation(L"../../Data/MiddleMonster/FINAL_FOOTSTEP1.dat", 5);
		Load_Animation(L"../../Data/MiddleMonster/FINAL_FOOTSTEP2.dat", 6);
	
		
		Load_Animation(L"../../Data/MiddleMonster/FINAL_SHOOTING.dat", 7);
		Load_Animation(L"../../Data/MiddleMonster/FINAL_SHOOTING1.dat", 8);
	}





	Update_Pattern(fTimeDelta);
	
	Look_Direction();

	CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_NONALPHA, this);
	m_pTransUICom->Billboard_Transform(fTimeDelta);
	Hit_Check(fTimeDelta);

	_vec3 vMonsterPos;
	m_pTransCom->Get_Info(INFO_POS, &vMonsterPos);
	m_pHitBoxTransCom->Set_Pos(vMonsterPos.x, vMonsterPos.y, vMonsterPos.z);
	m_pSphereTransCom->Set_Pos(vMonsterPos.x, vMonsterPos.y, vMonsterPos.z);
	m_pTransCom->Get_Info(INFO_POS, &vUIPos);
	m_pTransUICom->Set_Pos(vUIPos.x, vUIPos.y + 8.f, vUIPos.z);
	return 0;
}

void CMiddleBoss::LateUpdate_Object(void)
{
	Monster_Mapping();
	Set_OnTerrain();
	if (m_tAbility->fCurrentHp <= 0.f)
	{
		m_pMonsterUI->Off_Switch();
		this->Kill_Obj();
	}

	if (!m_bFirst)
	{

		if (m_STATE == MIDDLEBOSS_WALK)
		{
			Walk_Animation_Run();
			Run_Animation(15.f);
		}
		else if (m_STATE == MIDDLEBOSS_IDLE)
		{
			Idle_Animation_Run();
			Run_Animation(15.f);
		}
		else if (m_STATE == MIDDLEBOSS_ATTACK)
		{
			Attack_Animation_Run();
			Run_Animation(15.f);
		}
		else if (m_STATE == MIDDLEBOSS_SHOT)
		{
			Shot_Animation_Run();
			Run_Animation(15.f);
		}
	}




	CGameObject::LateUpdate_Object();
}


void CMiddleBoss::Render_Object(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pHitBoxTransCom->Get_WorldMatrixPointer());
	m_pHitBox->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pAnimationBox->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pSphereTransCom->Get_WorldMatrixPointer());
	m_pSphereBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransUICom->Get_WorldMatrixPointer());

	m_pTextureUICom->Set_Texture(0);
	m_pBufferUICom->Resize_Buffer(m_tAbility->fCurrentHp / m_tAbility->fMaxHp);
	m_pBufferUICom->Render_Buffer();
}



_int CMiddleBoss::Update_Pattern(_float fTimeDelta)
{
	if (m_pPlayerTransCom == nullptr)
	{
		m_pPlayerTransCom = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_CHARACTER, L"PLAYER", TRANSFORM_COMP, ID_DYNAMIC));
	}
	if (m_pMonsterUI == nullptr)
		m_pMonsterUI = dynamic_cast<CMonsterUI*>(Engine::Get_GameObject(STAGE_UI, L"MonsterUI"));
	if (m_pComboUI == nullptr)
		m_pComboUI = dynamic_cast<CComboUI*>(Engine::Get_GameObject(STAGE_UI, L"ComboUI"));

	_vec3 vPlayerPos;
	m_pPlayerTransCom->Get_Info(INFO_POS, &vPlayerPos);
	_vec3 vPlayerScale;
	m_pPlayerTransCom->Get_Scale(&vPlayerScale);
	_vec3 vScale;
	m_pSphereTransCom->Get_Scale(&vScale);
	_vec3 vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);
	_vec3 m_vDir;
	m_vDir = vPlayerPos - vPos;
	_vec3 vAnimationPos;

	
	_float m_fPlayerCurrent = D3DXVec3Length(&m_vDir);
	_vec3 vSearchScale, vAttackScale;
	
	m_pSearchRange_TransCom->Get_Scale(&vSearchScale);
	m_pAttackRange_TransCom->Get_Scale(&vAttackScale);
	_float HP = m_tAbility->fCurrentHp / m_tAbility->fMaxHp;
	if (m_fDetectRange >= m_fTargetLength)
	{
		if (HP >= 0.9f)
		{

			if (m_pCollision->Sphere_Collision(this->m_pSphereTransCom, m_pPlayerTransCom, vPlayerScale.x, vScale.x) && m_fFrame < 2.f)
			{//패턴1
				m_pTransCom->Chase_Target(&vPlayerPos, 10.f, fTimeDelta);
				m_STATE = MIDDLEBOSS_WALK;
			}
		}
		else if (HP >= 0.6f)
		{


			_vec3 vDir{ 1.f, 0.f, 0.f };
			if (m_pCollision->Sphere_Collision(this->m_pSphereTransCom, m_pPlayerTransCom, vPlayerScale.x, vScale.x) && m_fFrame < 2.f)
			{//패턴2


				m_STATE = MIDDLEBOSS_SHOT;
				m_pTransCom->Chase_Target(&vPlayerPos, 3.f, fTimeDelta);
				//m_fTimeDelta = fTimeDelta;
				CPoolMgr::GetInstance()->Reuse_Obj(m_pGraphicDev, &vPos, &m_vDir, m_tAbility->fDamage);

			}
		}
		else if (HP >= 0.01f)
		{
			//패턴3

			D3DXVECTOR3		vDir{ 1.f, 0.f, 0.f };
			if (m_pCollision->Sphere_Collision(this->m_pSphereTransCom, m_pPlayerTransCom, vPlayerScale.x, vScale.x))
			{
				m_STATE = MIDDLEBOSS_ATTACK;
				m_pTransCom->Chase_Target(&vPlayerPos, 3.f, fTimeDelta);
				m_fFrame += fTimeDelta;
				_matrix matRotY, matTrans, matWorld;

				if (m_fFrame >= 1.f)
				{
					for (m_fFireAngle = 0.f; m_fFireAngle < 360.f; m_fFireAngle += 2)
					{
						D3DXMatrixRotationY(&matRotY, D3DXToRadian(-m_fFireAngle));
						D3DXMatrixTranslation(&matTrans, vPos.x, 0.f, vPos.y);

						m_pTransCom->Get_WorldMatrix(&matWorld);
						matWorld = matRotY * matTrans;

						D3DXVec3TransformNormal(&vDir, &vDir, &matWorld);

						CPoolMgr::GetInstance()->Reuse_Obj(m_pGraphicDev, &vPos, &vDir, m_tAbility->fDamage);
					}
					m_fFrame = 0.f;
				}
			}


		}

	}
	return 0;
}

void CMiddleBoss::Hit_Check(_float _deltaTime)
{
	m_pTransCom->Static_Update();

	CCubePlayer* pPlayer = dynamic_cast<CCubePlayer*>(Engine::Get_GameObject(STAGE_CHARACTER, L"PLAYER"));
	CWeapon* pWeapon = pPlayer->Get_Weapon();
	if (pWeapon)
	{
		_vec3 vSrcPos;
		pWeapon->Get_Transform()->Get_Info(INFO_POS, &vSrcPos);

		_vec3 vDir;
		if (m_pCollision->HitScan(g_hWnd, &vSrcPos, this->m_pBufferCom, this->m_pTransCom, &vDir))
		{
			m_pMonsterUI->Set_Name(m_tAbility->strObjTag);
			m_pMonsterUI->Set_Hp(m_tAbility->fCurrentHp);
			m_pMonsterUI->Set_MaxHp(m_tAbility->fMaxHp);
			m_pMonsterUI->On_Switch();
			if (pWeapon->Get_Shoot() == true)
			{
				m_tAbility->fCurrentHp -= pWeapon->Get_Ability()->fBulletAttack;
				m_pComboUI->On_Switch();
				m_pComboUI->ComboCntPlus();
	
				pWeapon->Set_Shoot(false);
			}

			if (m_tAbility->fCurrentHp <= 0.f)
			{
				m_tAbility->fCurrentHp = 0.f;
			}
		}
		else
		{
			m_fUISwitchTime += _deltaTime;
			if (m_fUISwitchTime >= 5.f)
			{
				m_pMonsterUI->Off_Switch();
				m_fUISwitchTime = 0.f;
			}
		}
	}
}

HRESULT CMiddleBoss::Build(void)
{
	HANDLE      hFile = CreateFile(L"../../Data/MiddleMonster/MIDDLE_FINAL.dat",      // 파일의 경로와 이름	
		GENERIC_READ,         // 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
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
	_int	iDrawNum = 0;
	_float	fAxisX = 0.f, fAxisY = 0.f, fAxisZ = 0.f;
	_int	iChildCnt = 0;
	_int	iParentCnt = 0;

	int iSize = 0;
	ReadFile(hFile, &iSize, sizeof(int), &dwByte, nullptr);

	list<const _tchar*>	LoadOrder;
	for (int i = 0; i < iSize; ++i)
	{
		_tchar* szName = new _tchar[256]{};
		ReadFile(hFile, szName, sizeof(_tchar[256]), &dwByte, nullptr);
		LoadOrder.push_back(szName);
		m_TcharList.push_back(szName);
	}

	while (true)
	{
		ReadFile(hFile, &vRight, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vUp, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vLook, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vPos, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vScale, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &vAngle, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &iDrawNum, sizeof(_int), &dwByte, nullptr);
		ReadFile(hFile, &fAxisX, sizeof(_float), &dwByte, nullptr);
		ReadFile(hFile, &fAxisY, sizeof(_float), &dwByte, nullptr);
		ReadFile(hFile, &fAxisZ, sizeof(_float), &dwByte, nullptr);
		ReadFile(hFile, &iChildCnt, sizeof(_int), &dwByte, nullptr);
		ReadFile(hFile, &iParentCnt, sizeof(_int), &dwByte, nullptr);

		CGameObject *pGameObject = nullptr;

		pGameObject = CTransAxisBox::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pMyLayer, E_FAIL);

		FAILED_CHECK_RETURN(pMyLayer->Add_GamePair(LoadOrder.front(), pGameObject), E_FAIL);	//	Map을 쓰지 않는다!!!!! Layer/노트 참고

		pGameObject->Set_DrawTexIndex(iDrawNum);

		dynamic_cast<CTransAxisBox*>(pGameObject)->Set_Axis(fAxisX, fAxisY, fAxisZ);

		CTransform* Transcom = dynamic_cast<CTransform*>(pGameObject->Get_Component(L"Proto_TransformCom", ID_STATIC));

		Transcom->Set_Info(INFO_RIGHT, &vRight);
		Transcom->Set_Info(INFO_UP, &vUp);
		Transcom->Set_Info(INFO_LOOK, &vLook);
		Transcom->Set_Info(INFO_POS, &vPos);
		Transcom->Set_Angle(&vAngle);
		Transcom->Set_Scale(&vScale);

		Transcom->Worldspace_By_Quarternion();

		_vec3	vPos;
		Transcom->Get_Info(INFO_POS, &vPos);

		_vec3	vPlayerPos;
		m_pTransCom->Get_Info(INFO_POS, &vPlayerPos);

		if (0 == _tcscmp(LoadOrder.front(), L"A_ROOT"))	//	루트 이름은 항상 고정이므로 이렇게 지정해둠, 루트를 몸통으로 사용해도 좋고 아주 작게 만들어서 바닥으로 해도 좋고? 근데 거기까진 안해봤습니다ㅎ
			Transcom->Set_Pos(vPos.x + vPlayerPos.x, vPos.y + vPlayerPos.y, vPos.z + vPlayerPos.z);
		else
			Transcom->Set_Pos(vPos.x, vPos.y, vPos.z);

		Transcom->Worldspace_By_Quarternion();

		LoadOrder.pop_front();

		if (iChildCnt)
		{
			for (int i = 0; i < iChildCnt; ++i)
			{
				_tchar* szName = new _tchar[256]{};
				ReadFile(hFile, szName, sizeof(_tchar[256]), &dwByte, nullptr);
				dynamic_cast<CTransAxisBox*>(pGameObject)->m_ChildKey.push_back(szName);
				m_TcharList.push_back(szName);
			}
		}

		if (iParentCnt)
		{
			for (int i = 0; i < iParentCnt; ++i)
			{
				_tchar* szName = new _tchar[256]{};
				ReadFile(hFile, szName, sizeof(_tchar[256]), &dwByte, nullptr);
				dynamic_cast<CTransAxisBox*>(pGameObject)->m_ParentKey.push_back(szName);
				m_TcharList.push_back(szName);
			}
		}

		iSize--;

		if (0 == dwByte)
			break;

		if (0 == iSize)
			break;
	}

	for (auto& iter : *(pMyLayer->Get_GamePairPtr()))		//	List 개꿀
	{
		for (auto& List : dynamic_cast<CTransAxisBox*>(iter.second)->m_ParentKey)
		{
			auto	MapFindIter = find_if(pMyLayer->Get_GamePairPtr()->begin(), pMyLayer->Get_GamePairPtr()->end(), CTag_Finder(List));

			dynamic_cast<CTransAxisBox*>(iter.second)->m_ParentList.push_back(dynamic_cast<CTransAxisBox*>(MapFindIter->second));
		}
	}

	CloseHandle(hFile);
	return S_OK;
}

void CMiddleBoss::Load_Animation(wstring FileName, _uint AnimationID)
{
	HANDLE      hFile = CreateFile(FileName.c_str(),      // 파일의 경로와 이름
		GENERIC_READ,         // 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
		NULL,               // 공유 방식(파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가)    
		NULL,               // 보안 속성(NULL을 지정하면 기본값 상태)
		OPEN_EXISTING,         // CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING  : 파일이 있을 경우에만 열기
		FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등) : FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일
		NULL);               // 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니깐 NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}

	DWORD   dwByte = 0;

	int iSize = 0;
	ReadFile(hFile, &iSize, sizeof(_int), &dwByte, nullptr);

	list<const _tchar*>	LoadOrder;
	for (int i = 0; i < iSize; ++i)
	{
		_tchar* szName = new _tchar[256]{};
		ReadFile(hFile, szName, sizeof(_tchar[256]), &dwByte, nullptr);
		LoadOrder.push_back(szName);
		m_TcharList.push_back(szName);
	}

	for (auto& iter : LoadOrder)
	{
		auto	MapFindIter = find_if(pMyLayer->Get_GamePairPtr()->begin(), pMyLayer->Get_GamePairPtr()->end(), CTag_Finder(iter));

		CQuarternion* Quaternion = dynamic_cast<CQuarternion*>(MapFindIter->second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));

		if (Quaternion->Get_WorldVector()->size() >= 2)
		{
			CloseHandle(hFile);
			return;
		}

		_int iAnimationSize = 0;
		ReadFile(hFile, &iAnimationSize, sizeof(_int), &dwByte, nullptr);
		for (int i = 0; i < iAnimationSize; ++i)
		{
			_matrix matAnimation;
			ReadFile(hFile, &matAnimation, sizeof(D3DXMATRIX), &dwByte, nullptr);
			Quaternion->Fill_Animation(&matAnimation, AnimationID);
		}

		iSize--;

		if (0 == dwByte)
			break;

		if (0 == iSize)
			break;
	}

	CloseHandle(hFile);
}

void CMiddleBoss::Run_Animation(const _float & AnimationSpeed)
{
	list<pair<const _tchar*, CGameObject*>> ListBox = *(pMyLayer->Get_GamePairPtr());

	for (auto& iter : ListBox)
	{
		CQuarternion* Qtan = dynamic_cast<CQuarternion*>(iter.second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));
		if (Qtan->Get_WorldVector()->size() < 2)
			return;

		_matrix matFront = (Qtan->Get_WorldVector())->front();
		_matrix matLast = (Qtan->Get_WorldVector())->back();

		D3DXQUATERNION q1, q2, qSLerp;
		_vec3 vScale1, vTrans1, vScale2, vTrans2, vScaleLerp, vTransLerp;

		D3DXMatrixDecompose(&vScale1, &q1, &vTrans1, &matFront);
		D3DXMatrixDecompose(&vScale2, &q2, &vTrans2, &matLast);

		D3DXVec3Lerp(&vScaleLerp, &vScale1, &vScale2, m_AnimationTime);
		D3DXQuaternionSlerp(&qSLerp, &q1, &q2, m_AnimationTime);
		D3DXVec3Lerp(&vTransLerp, &vTrans1, &vTrans2, m_AnimationTime);

		m_AnimationTime += (m_fTimeDelta / AnimationSpeed);

		_float pitch, yaw, roll;

		FLOAT sqw = qSLerp.w * qSLerp.w;
		FLOAT sqx = qSLerp.x * qSLerp.x;
		FLOAT sqy = qSLerp.y * qSLerp.y;
		FLOAT sqz = qSLerp.z * qSLerp.z;

		pitch = asinf(2.f * (qSLerp.w * qSLerp.x - qSLerp.y * qSLerp.z));
		yaw = atan2f(2.0f * (qSLerp.x * qSLerp.z + qSLerp.w * qSLerp.y), (-sqx - sqy + sqz + sqw));
		roll = atan2f(2.0f * (qSLerp.x * qSLerp.y + qSLerp.w * qSLerp.z), (-sqx + sqy - sqz + sqw));

		_matrix matNewWorld, matNewScale, matNewRot, matNewTrans;
		D3DXMatrixScaling(&matNewScale, vScaleLerp.x, vScaleLerp.y, vScaleLerp.z);
		D3DXMatrixRotationQuaternion(&matNewRot, &qSLerp);
		D3DXMatrixTranslation(&matNewTrans, vTransLerp.x, vTransLerp.y, vTransLerp.z);
		matNewWorld = matNewScale * matNewRot * matNewTrans;

		CTransform*	BoxTransform = dynamic_cast<CTransform*>(iter.second->Get_Component(L"Proto_TransformCom", ID_STATIC));
		_matrix matWorld;
		BoxTransform->Set_WorldMatrix(&matNewWorld);
		BoxTransform->Set_Scale(&vScaleLerp);
		BoxTransform->Set_Angle(&_vec3(yaw, pitch, roll));

		_vec3		vPlayerPos;
		m_pTransCom->Get_Info(INFO_POS, &vPlayerPos);

		if (0 == _tcscmp(iter.first, L"A_ROOT"))
			BoxTransform->Set_Pos(vTransLerp.x + vPlayerPos.x, vTransLerp.y + vPlayerPos.y, vTransLerp.z + vPlayerPos.z);
		else
			BoxTransform->Set_Pos(vTransLerp.x, vTransLerp.y, vTransLerp.z);
	}
}

void CMiddleBoss::Look_Direction(void)
{
	_matrix matWorld;
	m_pTransCom->Get_WorldMatrix(&matWorld);

	D3DXQUATERNION qRot;
	D3DXMatrixDecompose(&_vec3(), &qRot, &_vec3(), &matWorld);

	_float pitch, yaw, roll;

	FLOAT sqw = qRot.w * qRot.w;
	FLOAT sqx = qRot.x * qRot.x;
	FLOAT sqy = qRot.y * qRot.y;
	FLOAT sqz = qRot.z * qRot.z;

	pitch = asinf(2.f * (qRot.w * qRot.x - qRot.y * qRot.z));
	yaw = atan2f(2.0f * (qRot.x * qRot.z + qRot.w * qRot.y), (-sqx - sqy + sqz + sqw));
	roll = atan2f(2.0f * (qRot.x * qRot.y + qRot.w * qRot.z), (-sqx + sqy - sqz + sqw));


	list<pair<const _tchar*, CGameObject*>> ListBox = *(pMyLayer->Get_GamePairPtr());

	for (auto& iter : ListBox)
	{
		if (0 == _tcscmp(iter.first, L"A_ROOT"))
		{
			_vec3 vAngle;
			CTransform* Transform = dynamic_cast<CTransform*>(iter.second->Get_Component(L"Proto_TransformCom", ID_STATIC));
			Transform->Get_Angle(&vAngle);
			Transform->Set_Angle(&_vec3(yaw, vAngle.y, vAngle.z));
		}
	}
}

void CMiddleBoss::Walk_Animation_Run(void)
{
	list<pair<const _tchar*, CGameObject*>> ListBox = *(pMyLayer->Get_GamePairPtr());

	if (m_AnimationTime >= 1.f)
	{
		for (auto& iter : ListBox)
		{
			CQuarternion* Qtan = dynamic_cast<CQuarternion*>(iter.second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));
			Qtan->Delete_WorldVector();
		}
		if (m_WALK == MIDDLEBOSSWALK_START)
			m_WALK = MIDDLEBOSSWALK_1;
		else if (m_WALK == MIDDLEBOSSWALK_1)
			m_WALK = MIDDLEBOSSWALK_2;
		else if (m_WALK == MIDDLEBOSSWALK_2)
			m_WALK = MIDDLEBOSSWALK_1;

		m_AnimationTime = 0.f;
	}
	for (auto& iter : ListBox)	// 애니메이션 변경
	{
		CQuarternion* Qtan = dynamic_cast<CQuarternion*>(iter.second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));
		Qtan->Change_Animation(2 + m_WALK);
	}

	
}

void CMiddleBoss::Attack_Animation_Run(void)
{
	list<pair<const _tchar*, CGameObject*>> ListBox = *(pMyLayer->Get_GamePairPtr());

	if (m_AnimationTime >= 1.f)
	{
		for (auto& iter : ListBox)
		{
			CQuarternion* Qtan = dynamic_cast<CQuarternion*>(iter.second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));
			Qtan->Delete_WorldVector();
		}
		m_AnimationTime = 0.f;
		if (m_ATTACK == MIDDLEBOSSATTACK_START)
			m_ATTACK = MIDDLEBOSSATTACK_1;


	}

	for (auto& iter : ListBox)	// 애니메이션 변경
	{
		CQuarternion* Qtan = dynamic_cast<CQuarternion*>(iter.second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));
		Qtan->Change_Animation(5 + m_ATTACK);
	}
}

void CMiddleBoss::Shot_Animation_Run(void)
{
	list<pair<const _tchar*, CGameObject*>> ListBox = *(pMyLayer->Get_GamePairPtr());

	if (m_AnimationTime >= 1.f)
	{
		for (auto& iter : ListBox)
		{
			CQuarternion* Qtan = dynamic_cast<CQuarternion*>(iter.second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));
			Qtan->Delete_WorldVector();
		}
		m_AnimationTime = 0.f;
		if (m_SHOT == MIDDLEBOSSSHOT_START)
			m_SHOT = MIDDLEBOSSSHOT_1;


	}

	for (auto& iter : ListBox)	// 애니메이션 변경
	{
		CQuarternion* Qtan = dynamic_cast<CQuarternion*>(iter.second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));
		Qtan->Change_Animation(7 + m_SHOT);
	}
}



void CMiddleBoss::Set_OnTerrain(void)
{
	_vec3 vAnimationPos;

	_vec3		vPos;
	m_pTransCom->Get_BeforeInfo(INFO_POS, &vAnimationPos);

	Engine::CTerrainTex*	pTerrainTexCom = dynamic_cast<Engine::CTerrainTex*>(Engine::Get_Component(STAGE_ENVIRONMENT, L"Terrain", TERRAINTEX_COMP, ID_STATIC));
	NULL_CHECK(pTerrainTexCom);

	_float fHeight = m_pCalculatorCom->HeightOnTerrain(&vAnimationPos, pTerrainTexCom->Get_VtxPos(), VTXCNTX, VTXCNTZ) + 0.6f;

	m_pTransCom->Set_Pos(vAnimationPos.x, fHeight + 10.f, vAnimationPos.z);
}

_bool CMiddleBoss::Collision_Wall(const _float & fTimeDelta)
{
	_vec3 vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);

	_vec3	vDir(0, 0, 0);
	_vec3	vNormal(0, 0, 0);

	_int iCollision = m_pCollision->Wall_Collision_For_Monster(&vNormal, this->m_pTransCom, this->m_pHitBox);

	if (-1 != iCollision)
	{
		float fDot = D3DXVec3Dot(&vNormal, &vDir);
		float fDiagonal = acosf(fDot);

		if (iCollision == WALL_RIGHT || iCollision == WALL_LEFT || iCollision == WALL_BACK)
		{
			if (D3DXToDegree(fDiagonal) > 90.f)
			{
				_vec3 vSliding = vDir;
				m_pCollision->Wall_Collision_By_DotSliding_For_Monster(&vSliding, this->m_pTransCom, this->m_pHitBox);

				m_pTransCom->Move_Pos(&(vSliding * m_fSpeed * fTimeDelta));
			}
			else
			{
				vDir = _vec3(1, 0, 0);
				m_pTransCom->Move_Pos(&(vDir * m_fSpeed * fTimeDelta));
			}
			return true;
		}
		if (iCollision == WALL_FRONT)
		{
			if (D3DXToDegree(fDiagonal) < 90.f)
			{
				_vec3 vSliding = vDir;
				m_pCollision->Wall_Collision_By_DotSliding_For_Monster(&vSliding, this->m_pTransCom, this->m_pHitBox);

				m_pTransCom->Move_Pos(&(vSliding * m_fSpeed * fTimeDelta));
			}
			else
			{
				vDir = _vec3(-1, 0, 0);
				m_pTransCom->Move_Pos(&(vDir * m_fSpeed * fTimeDelta));
			}
			return true;
		}
	}
	else
	{
		m_pTransCom->Move_Pos(&(vDir * m_fSpeed * fTimeDelta));
		return false;
	}

	return false;
}

void CMiddleBoss::Idle_Animation_Run(void)
{
	list<pair<const _tchar*, CGameObject*>> ListBox = *(pMyLayer->Get_GamePairPtr());

	if (m_AnimationTime >= 1.f)
	{
		for (auto& iter : ListBox)
		{
			CQuarternion* Qtan = dynamic_cast<CQuarternion*>(iter.second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));
			Qtan->Delete_WorldVector();
		}
		if (m_IDLE == MIDDLEBOSSIDLE_1)
			m_IDLE = MIDDLEBOSSIDLE_2;
		else if (m_IDLE == MIDDLEBOSSIDLE_2)
			m_IDLE = MIDDLEBOSSIDLE_1;

		m_AnimationTime = 0.f;
	}
	for (auto& iter : ListBox)
	{
		CQuarternion* Qtan = dynamic_cast<CQuarternion*>(iter.second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));
		Qtan->Change_Animation(0 + m_IDLE);
	}
	
}

HRESULT CMiddleBoss::Create_Item()
{
	CGameObject*		pGameObject = nullptr;
	_vec3 vItemPos;
	m_pTransCom->Get_Info(INFO_POS, &vItemPos);

	srand((unsigned int)time(NULL));
	_int iRand = rand() % 3;

	switch (iRand)
	{
	case 0:
		pGameObject = CHealthPotion::Create(m_pGraphicDev, vItemPos);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		Get_Layer(STAGE_ITEM)->Add_GameList(pGameObject);
		break;

	case 1:
		pGameObject = CObtainBullet::Create(m_pGraphicDev, vItemPos);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		Get_Layer(STAGE_ITEM)->Add_GameList(pGameObject);
		break;

	case 2:
		pGameObject = CObtainDefense::Create(m_pGraphicDev, vItemPos);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		Get_Layer(STAGE_ITEM)->Add_GameList(pGameObject);
		break;
	}

	return S_OK;
}

HRESULT CMiddleBoss::Monster_Mapping(void)
{
	_vec3		vPos;
	m_pHitBoxTransCom->Get_Info(INFO_POS, &vPos);
	if (!m_MappingInit)
	{
		CGameObject*	m_pMapMonster = CMonsterMapping::Create(m_pGraphicDev);
		wsprintf(m_szCntName, L"");
		const _tchar*	szNumbering = L"MapMonster_%d";
		wsprintf(m_szCntName, szNumbering, m_iCnt);
		Engine::Add_GameObject(STAGE_MAPPING, m_pMapMonster, m_szCntName);
		m_listMonsterCnt.push_back(m_szCntName);

		m_pMonsterMapping = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_MAPPING, m_szCntName, TRANSFORM_COMP, ID_DYNAMIC));
		NULL_CHECK_RETURN(m_pMonsterMapping, E_FAIL);
		++m_iCnt;
		m_MappingInit = true;

	}
	m_pMonsterMapping->Set_Pos(vPos.x, vPos.y, vPos.z);
	return S_OK;

}

HRESULT CMiddleBoss::Monster_DeleteMapping(void)
{
	Engine::Delete_GameObject(STAGE_MAPPING, m_szCntName);

	return S_OK;
}


HRESULT CMiddleBoss::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CCubeTex*>(Clone_Proto(L"Proto_CubeTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubeTexCom", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_CubePlayerTexture"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CubePlayerTexture", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });


	pComponent = m_pHitBox = dynamic_cast<CHitBox*>(Engine::Clone_Proto(HITBOX_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ HITBOX_COMP, pComponent });

	pComponent = m_pCollision = dynamic_cast<CCollision*>(Engine::Clone_Proto(COLLISION_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ COLLISION_COMP, pComponent });

	pComponent = m_pHitBoxTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"HitBox_Transform", pComponent });


	pComponent = m_pTransUICom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pTransUICom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformUICom", pComponent });

	pComponent = m_pBufferUICom = dynamic_cast<CRcTex*>(Clone_Proto(RCTEX_MONTER_HP_COMP));
	NULL_CHECK_RETURN(m_pBufferUICom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ RCTEX_MONTER_HP_COMP, pComponent });

	pComponent = m_pTextureUICom = dynamic_cast<CTexture*>(Clone_Proto(L"Monster_General_HP"));
	NULL_CHECK_RETURN(m_pTextureUICom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Monster_General_HP", pComponent });


	pComponent = m_pSphereBufferCom = dynamic_cast<CSphereTex*>(Clone_Proto(SPHERETEX_COMP));
	NULL_CHECK_RETURN(m_pSphereBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ SPHERETEX_COMP, pComponent });

	pComponent = m_pSearchRange_TransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pSphereBufferCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"SearchRange", pComponent });

	pComponent = m_pAttackRange_TransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pSphereBufferCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"AttackRange", pComponent });

	pComponent = m_pSphereTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(m_pSphereBufferCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Sphere_TransCom", pComponent });

	pComponent = m_pAnimationBox = dynamic_cast<CCubeCol*>(Clone_Proto(CUBECOL_COMP));
	NULL_CHECK_RETURN(m_pSphereBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ CUBECOL_COMP, pComponent });

	return S_OK;
}

CMiddleBoss * CMiddleBoss::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos, _tchar * Name)
{
	CMiddleBoss * pInstance = new CMiddleBoss(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(vPos, Name)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMiddleBoss::Free(void)
{
	for (auto& iter : *(pMyLayer->Get_GamePairPtr()))
	{
		iter.second->Kill_Obj();
	}

	for (auto iter : m_TcharList)
	{
		Safe_Delete_Array(iter);
	}

	for (auto iter : m_listMonsterCnt)
	{
		Safe_Delete_Array(iter);
	}
	
	m_listMonsterCnt.clear();	
	CGameObject::Free();
	Safe_Delete<MIDDLEBOSSABILITY*>(m_tAbility);
}
