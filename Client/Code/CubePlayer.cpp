#include "stdafx.h"
#include "..\Header\CubePlayer.h"
#include "PoolMgr.h"
#include "Bullet.h"
#include "Uzi.h"
#include "Shotgun.h"
#include "Sniper.h"
#include "ShotParticle.h"
#include "BulletParticle.h"

CCubePlayer::CCubePlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CCubePlayer::~CCubePlayer()
{
}

HRESULT CCubePlayer::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_tAbility = new ABILITY;
	m_tAbility->iHp = 100;
	m_tAbility->iMaxHp = 100;
	m_tAbility->iDefence = 100;
	m_tAbility->iGunTexture = 5;

	m_pTransform->Set_Scale(0.4f, 1.f, 0.4f);
	m_pTransform->Set_Pos(10.f, 10.f, 10.f);
	m_pTransform->Static_Update();

	m_fSpeed = 10.f;

	m_bUzi = false;
	m_bShotgun = false;
	m_bSniper = false;

	//ShowCursor(false);

	return S_OK;
}

_int CCubePlayer::Update_Object(const _float & fTimeDelta)
{
	m_fTimeDelta = fTimeDelta;
	m_fBulletTime += fTimeDelta;

	FAILED_CHECK_RETURN(Get_BodyTransform(), -1);

	// 이동, 애니메이션 관련
	Move();

	Look_Direction();

	Animation();

	Assemble();

	Player_Mapping();

	//FAILED_CHECK_RETURN(CPoolMgr::GetInstance()->Reuse_Obj(m_pGraphicDev, &vPos, &m_vDirection), -1);

	CGameObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CCubePlayer::LateUpdate_Object(void)
{
	if (!m_bJump)
		Set_OnTerrain();

	TransAxis();	//	월드함수 갈아엎으려면 Update 이후에 작업해줘야함

	if (m_Weapon)
	{
		if (m_Weapon->Get_Ability()->fBulletRate - m_fBulletTime <= 0.f)
		{
			Fire_Bullet();
		}
	}
	
	m_pCollision->Get_Item();

	Gun_Check();

	CGameObject::LateUpdate_Object();
}

void CCubePlayer::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//m_pHitBox->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void CCubePlayer::Set_OnTerrain(void)
{
	m_pBodyWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"BODY", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pBodyWorld, );

	_vec3		vPos;
	m_pBodyWorld->Get_BeforeInfo(INFO_POS, &vPos);

	Engine::CTerrainTex*	pTerrainTexCom = dynamic_cast<Engine::CTerrainTex*>(Engine::Get_Component(L"Layer_Environment", L"Terrain", L"Proto_TerrainTexCom", ID_STATIC));
	NULL_CHECK(pTerrainTexCom);

	_float fHeight = m_pCalculatorCom->HeightOnTerrain(&vPos, pTerrainTexCom->Get_VtxPos(), VTXCNTX, VTXCNTZ) + 0.6f;

	m_pBodyWorld->Set_Pos(vPos.x, fHeight, vPos.z);
}

void CCubePlayer::Assemble(void)
{
	FAILED_CHECK_RETURN(Get_BodyTransform(), );

	_vec3 vBodyPos, vBodyAfterPos;
	m_pBodyWorld->Get_BeforeInfo(INFO_POS, &vBodyPos);
	m_pBodyWorld->Get_Info(INFO_POS, &vBodyAfterPos);

	m_pTransform->Set_Pos(vBodyPos.x, vBodyPos.y, vBodyPos.z);
	m_pHeadWorld->Set_Pos(vBodyPos.x, vBodyPos.y + 0.3f, vBodyPos.z);
	m_pLeftArmWorld->Set_Pos(vBodyPos.x - 0.15f, vBodyPos.y + 0.1f, vBodyPos.z);
	m_pRightArmWorld->Set_Pos(vBodyPos.x + 0.15f, vBodyPos.y + 0.1f, vBodyPos.z);
	m_pLeftLegWorld->Set_Pos(vBodyPos.x - 0.05f, vBodyPos.y - 0.3f, vBodyPos.z);
	m_pRightLegWorld->Set_Pos(vBodyPos.x + 0.05f, vBodyPos.y - 0.3f, vBodyPos.z);

	m_pLeftHandWorld->Set_Pos(vBodyPos.x - 0.15f, vBodyPos.y - 0.1f, vBodyPos.z);
	m_pRightHandWorld->Set_Pos(vBodyPos.x + 0.15f, vBodyPos.y - 0.1f, vBodyPos.z);
	m_pLeftFootWorld->Set_Pos(vBodyPos.x - 0.05f, vBodyPos.y - 0.5f, vBodyPos.z);
	m_pRightFootWorld->Set_Pos(vBodyPos.x + 0.05f, vBodyPos.y - 0.5f, vBodyPos.z);

	if (m_bFirst)
	{
		m_bFirst = false;

		m_pLeftArmWorld->Static_Update();
		m_pRightArmWorld->Static_Update();
		m_pLeftLegWorld->Static_Update();
		m_pRightLegWorld->Static_Update();
		m_pLeftHandWorld->Static_Update();
		m_pRightHandWorld->Static_Update();
		m_pLeftFootWorld->Static_Update();
		m_pRightHandWorld->Static_Update();
	}
}

void CCubePlayer::Animation(void)
{
	if (Get_DIKeyState(DIK_W) || Get_DIKeyState(DIK_A) || Get_DIKeyState(DIK_S) || Get_DIKeyState(DIK_D) || Get_DIKeyState(DIK_SPACE) || Get_DIKeyState(DIK_LSHIFT))
	{
		if (m_fLeftArmAngle > 0.6f)
			m_bWalkAngle = false;
		if (m_fLeftArmAngle < -0.6f)
			m_bWalkAngle = true;

		if (m_bWalkAngle == true)
			m_fLeftArmAngle += m_fTimeDelta * 4.f;
		else if (m_bWalkAngle == false)
			m_fLeftArmAngle -= m_fTimeDelta * 4.f;

		m_fRightArmAngle = -m_fLeftArmAngle;

		if (m_fLeftLegAngle > 0.6f)
			m_bWalkAngle_Leg = false;
		if (m_fLeftLegAngle < -0.6f)
			m_bWalkAngle_Leg = true;

		if (m_bWalkAngle_Leg == true)
			m_fLeftLegAngle += m_fTimeDelta * 4.f;
		else if (m_bWalkAngle_Leg == false)
			m_fLeftLegAngle -= m_fTimeDelta * 4.f;

		m_fRightLegAngle = -m_fLeftLegAngle;

		if (m_fHandAngle > -D3DX_PI / 2.f)
			m_fHandAngle -= m_fTimeDelta * 4;
	}
	if (	Get_DIMouseState(DIM_RB) || 
			(m_Weapon == Engine::Get_GameObject(L"Layer_Gun", L"SHOTGUN")) ||
			(m_Weapon == Engine::Get_GameObject(L"Layer_Gun", L"SNIPER"))	)
	{
		// 우지 견착
		if ((m_Weapon == Engine::Get_GameObject(L"Layer_Gun", L"UZI1")))
		{
			m_fLeftArmAngle = D3DXToRadian(-90.f) + m_fDownAngle;
			m_fRightArmAngle = D3DXToRadian(-90.f) + m_fDownAngle;
			m_fHandAngle = 0.f;
		
		}
		// 샷건 / 스나 견착
		if ((m_Weapon == Engine::Get_GameObject(L"Layer_Gun", L"SHOTGUN")) ||
			(m_Weapon == Engine::Get_GameObject(L"Layer_Gun", L"SNIPER")))
		{
			m_fLeftArmAngle = D3DXToRadian(-75.f) + m_fDownAngle;
			m_fRightArmAngle = m_fDownAngle;
			m_fHandAngle = D3DXToRadian(-90.f);
		}
	}

	if (m_Weapon == Engine::Get_GameObject(L"Layer_Gun", L"SNIPER"))
	{
		if (Get_DIMouseState(DIM_RB))
			m_bSinperZoom = true;
		else
			m_bSinperZoom = false;
	}

	if (!(Get_DIKeyState(DIK_W) ||
		Get_DIKeyState(DIK_A) ||
		Get_DIKeyState(DIK_S) ||
		Get_DIKeyState(DIK_D) ||
		Get_DIKeyState(DIK_SPACE) ||
		Get_DIKeyState(DIK_LSHIFT) ||
		Get_DIMouseState(DIM_RB)))
	{

		if (!(m_Weapon == Engine::Get_GameObject(L"Layer_Gun", L"SHOTGUN")) &&
			!(m_Weapon == Engine::Get_GameObject(L"Layer_Gun", L"SNIPER")))
		{
			if (m_fLeftArmAngle != 0.f)
			{
				if (m_fLeftArmAngle > 0.f)
				{
					m_fLeftArmAngle -= D3DXToRadian(10.f);
					if (m_fLeftArmAngle < 0.f)
						m_fLeftArmAngle = 0.f;
				}
				else if (m_fLeftArmAngle < 0.f)
				{
					m_fLeftArmAngle += D3DXToRadian(10.f);
					if (m_fLeftArmAngle > 0.f)
						m_fLeftArmAngle = 0.f;
				}
			}

			if (m_fRightArmAngle != 0.f)
			{
				if (m_fRightArmAngle > 0.f)
				{
					m_fRightArmAngle -= D3DXToRadian(10.f);
					if (m_fRightArmAngle < 0.f)
						m_fRightArmAngle = 0.f;
				}
				else if (m_fRightArmAngle < 0.f)
				{
					m_fRightArmAngle += D3DXToRadian(10.f);
					if (m_fRightArmAngle > 0.f)
						m_fRightArmAngle = 0.f;
				}
			}

			if (m_fHandAngle != 0.f)
			{
				if (m_fHandAngle > 0.f)
				{
					m_fHandAngle -= D3DXToRadian(10.f);
					if (m_fHandAngle < 0.f)
						m_fHandAngle = 0.f;
				}
				else if (m_fHandAngle < 0.f)
				{
					m_fHandAngle += D3DXToRadian(10.f);
					if (m_fHandAngle > 0.f)
						m_fHandAngle = 0.f;
				}
			}
		}

		if (m_fLeftLegAngle != 0.f)
		{
			if (m_fLeftLegAngle > 0.f)
			{
				m_fLeftLegAngle -= D3DXToRadian(10.f);
				if (m_fLeftLegAngle < 0.f)
					m_fLeftLegAngle = 0.f;
			}
			else if (m_fLeftLegAngle < 0.f)
			{
				m_fLeftLegAngle += D3DXToRadian(10.f);
				if (m_fLeftLegAngle > 0.f)
					m_fLeftLegAngle = 0.f;
			}
		}

		if (m_fRightLegAngle != 0.f)
		{
			if (m_fRightLegAngle > 0.f)
			{
				m_fRightLegAngle -= D3DXToRadian(10.f);
				if (m_fRightLegAngle < 0.f)
					m_fRightLegAngle = 0.f;
			}
			else if (m_fRightLegAngle < 0.f)
			{
				m_fRightLegAngle += D3DXToRadian(10.f);
				if (m_fRightLegAngle > 0.f)
					m_fRightLegAngle = 0.f;
			}
		}
	}
}

void CCubePlayer::Move()
{
	////////////방향체크용////////////////
	_vec3 vPos;
	m_pBodyWorld->Get_Info(INFO_POS, &vPos);
	////////////방향체크용////////////////

	_vec3	vDir(0, 0, 0);
	_vec3	vNormal(0, 0, 0);

	if (Get_DIKeyState(DIK_W) && Get_DIKeyState(DIK_A))
	{
		_vec3 vLook, vRight;
		m_pBodyWorld->Get_Info(INFO_LOOK, &vLook);
		m_pBodyWorld->Get_Info(INFO_RIGHT, &vRight);
		vRight *= -1.f;

		vDir = vLook + vRight;

		D3DXVec3Normalize(&vDir, &vDir);
	}
	else if (Get_DIKeyState(DIK_W) && Get_DIKeyState(DIK_D))
	{
		_vec3 vLook, vRight;
		m_pBodyWorld->Get_Info(INFO_LOOK, &vLook);
		m_pBodyWorld->Get_Info(INFO_RIGHT, &vRight);

		vDir = vLook + vRight;

		D3DXVec3Normalize(&vDir, &vDir);
	}
	else if (Get_DIKeyState(DIK_S) && Get_DIKeyState(DIK_D))
	{
		_vec3 vLook, vRight;
		m_pBodyWorld->Get_Info(INFO_LOOK, &vLook);
		m_pBodyWorld->Get_Info(INFO_RIGHT, &vRight);
		vLook *= -1.f;

		vDir = vLook + vRight;

		D3DXVec3Normalize(&vDir, &vDir);
	}
	else if (Get_DIKeyState(DIK_S) && Get_DIKeyState(DIK_A))
	{
		_vec3 vLook, vRight;
		m_pBodyWorld->Get_Info(INFO_LOOK, &vLook);
		m_pBodyWorld->Get_Info(INFO_RIGHT, &vRight);
		vLook *= -1.f;
		vRight *= -1.f;

		vDir = vLook + vRight;

		D3DXVec3Normalize(&vDir, &vDir);
	}
	else if (Get_DIKeyState(DIK_W))
	{
		m_pBodyWorld->Get_Info(INFO_LOOK, &vDir);
		D3DXVec3Normalize(&vDir, &vDir);
	}
	else if (Get_DIKeyState(DIK_S))
	{
		m_pBodyWorld->Get_Info(INFO_LOOK, &vDir);
		D3DXVec3Normalize(&vDir, &vDir);
		vDir = -vDir;
	}
	else if (Get_DIKeyState(DIK_A))
	{
		m_pBodyWorld->Get_Info(INFO_RIGHT, &vDir);
		D3DXVec3Normalize(&vDir, &vDir);
		vDir = -vDir;
	}
	else if (Get_DIKeyState(DIK_D))
	{
		m_pBodyWorld->Get_Info(INFO_RIGHT, &vDir);
		D3DXVec3Normalize(&vDir, &vDir);
	}

	if (Get_DIKeyState(DIK_SPACE))
	{
		m_bJump = true;
	}

	if (Get_DIKeyState(DIK_LSHIFT))
	{
		m_bJump = false;
	}

	_int iCollision = m_pCollision->Wall_Collision(&vNormal);

	if (-1 != iCollision)
	{
		float fDot = D3DXVec3Dot(&vNormal, &vDir);
		float fDiagonal = acosf(fDot);

		if (iCollision == WALL_RIGHT || iCollision == WALL_LEFT || iCollision == WALL_BACK)
		{
			if (D3DXToDegree(fDiagonal) > 90.f)
			{
				_vec3 vSliding = vDir;
				m_pCollision->Wall_Collision_By_DotSliding(&vSliding);

				m_pBodyWorld->Move_Pos(&(vSliding * m_fSpeed * m_fTimeDelta));
				//FAILED_CHECK_RETURN(CPoolMgr::GetInstance()->Reuse_Obj(m_pGraphicDev, &vPos, &vSliding), );
			}
			else
			{
				m_pBodyWorld->Move_Pos(&(vDir * m_fSpeed * m_fTimeDelta));
				//FAILED_CHECK_RETURN(CPoolMgr::GetInstance()->Reuse_Obj(m_pGraphicDev, &vPos, &vDir), );
			}
		}
		if (iCollision == WALL_FRONT)
		{
			if (D3DXToDegree(fDiagonal) < 90.f)
			{
				_vec3 vSliding = vDir;
				m_pCollision->Wall_Collision_By_DotSliding(&vSliding);

				m_pBodyWorld->Move_Pos(&(vSliding * m_fSpeed * m_fTimeDelta));
				//FAILED_CHECK_RETURN(CPoolMgr::GetInstance()->Reuse_Obj(m_pGraphicDev, &vPos, &vSliding), );
			}
			else
			{
				m_pBodyWorld->Move_Pos(&(vDir * m_fSpeed * m_fTimeDelta));
				//FAILED_CHECK_RETURN(CPoolMgr::GetInstance()->Reuse_Obj(m_pGraphicDev, &vPos, &vDir), );
			}
		}
	}
	else	//	충돌하지 않았으며 충돌한 방향과 반대 방향으로 진행하는 이동 처리
	{
		m_pBodyWorld->Move_Pos(&(vDir * m_fSpeed * m_fTimeDelta));
		//FAILED_CHECK_RETURN(CPoolMgr::GetInstance()->Reuse_Obj(m_pGraphicDev, &vPos, &vDir), );
	}
}

void CCubePlayer::TransAxis(void)
{
	_vec3	vBefore, vAfter;

	FAILED_CHECK_RETURN(Get_BodyTransform(), );

	m_pBodyWorld->Get_Info(INFO_POS, &vBefore);
	m_pBodyWorld->Get_BeforeInfo(INFO_POS, &vAfter);

	m_pLeftArmWorld->Rotation_Axis_Animation(-0.1f, -0.15f, m_fLeftArmAngle, -m_fLookAngle);
	m_pRightArmWorld->Rotation_Axis_Animation(-0.1f, 0.15f, m_fRightArmAngle, -m_fLookAngle);

	if ((nullptr != m_Weapon) && Get_DIMouseState(DIM_RB) || (	(m_Weapon == Engine::Get_GameObject(L"Layer_Gun", L"SHOTGUN")) ||
		(m_Weapon == Engine::Get_GameObject(L"Layer_Gun", L"SNIPER"))	)	)
		m_pLeftHandWorld->Rotation_Axis_Special(-0.3f, -0.15f, m_fLeftArmAngle, -m_fLookAngle, -0.1f, -m_fHandAngle);
	else
		m_pLeftHandWorld->Rotation_Axis_Animation(-0.3f, -0.15f, m_fLeftArmAngle, -m_fLookAngle, -0.1f, m_fHandAngle);

	m_pRightHandWorld->Rotation_Axis_Animation(-0.3f, 0.15f, m_fRightArmAngle, -m_fLookAngle, -0.1f, m_fHandAngle);

	m_pLeftLegWorld->Rotation_Axis_Animation(-0.1f, -0.05f, m_fLeftLegAngle, -m_fLookAngle);
	m_pRightLegWorld->Rotation_Axis_Animation(-0.1f, 0.05f, m_fRightLegAngle, -m_fLookAngle);
	m_pLeftFootWorld->Rotation_Axis_Animation(-0.3f, -0.05f, m_fLeftLegAngle, -m_fLookAngle, -0.1f, fabs(m_fLeftLegAngle));
	m_pRightFootWorld->Rotation_Axis_Animation(-0.3f, 0.05f, m_fRightLegAngle, -m_fLookAngle, -0.1f, fabs(m_fRightLegAngle));
}

void CCubePlayer::Look_Direction(void)
{
	FAILED_CHECK_RETURN(Get_BodyTransform(), );

	_vec3	vHead, vBody;
	m_pHeadWorld->Get_BeforeInfo(INFO_LOOK, &vHead);
	m_pBodyWorld->Get_BeforeInfo(INFO_LOOK, &vBody);

	_long MoveX = Get_DIMouseMove(DIMS_X);
	_long MoveY = Get_DIMouseMove(DIMS_Y);
	_long MoveZ = Get_DIMouseMove(DIMS_Z);

	m_pBodyWorld->Rotation(ROT_Y, D3DXToRadian(MoveX / 10.f));
	m_fLookAngle -= D3DXToRadian(MoveX / 10.f);

	m_fDownAngle += D3DXToRadian(MoveY / 10.f);
}

void CCubePlayer::Fire_Bullet(void)
{
	if (Get_DIMouseState(DIM_RB))
	{
		if (Get_DIMouseState(DIM_LB))
		{
			if (m_Weapon->Get_Ability()->fRemainBulletCnt > 0)
			{
				CGameObject* pBullet = Engine::Get_GameObject(L"Layer_Environment", L"BulletParticle");
				dynamic_cast<CBulletParticle*>(pBullet)->addParticle();

				CGameObject* pShot = Engine::Get_GameObject(L"Layer_Environment", L"ShotParticle");
				dynamic_cast<CShotParticle*>(pShot)->addParticle();

				_float fGunSound = 1.f;
				PlaySoundGun(L"RifleShot.mp3", SOUND_EFFECT, fGunSound);
				m_Weapon->Set_MinusBullet();
				m_Weapon->Set_Shoot(true);
				m_fBulletTime = 0.f;
			}
		}
	}
}

void CCubePlayer::Gun_Check(void)
{
	// 만약 땅에 떨어진 UZI랑 충돌을 했다면 m_vecWeapon에 pushback으로 우지가 들어간다.
	// ex코드
	if (m_bUzi == true)
	{
		dynamic_cast<CSniper*>(Engine::Get_GameObject(L"Layer_Gun", L"SNIPER"))->Off_Sniper();
		dynamic_cast<CShotgun*>(Engine::Get_GameObject(L"Layer_Gun", L"SHOTGUN"))->Off_ShotGun();
		dynamic_cast<CUzi*>(Engine::Get_GameObject(L"Layer_Gun", L"UZI1"))->Set_Uzi();
		dynamic_cast<CUzi*>(Engine::Get_GameObject(L"Layer_Gun", L"UZI2"))->Set_Uzi();

      //m_vecWeapon.push_back(dynamic_cast<CWeapon*>(Engine::Get_GameObject(L"Layer_Gun", L"UZI1")));
		m_Weapon = dynamic_cast<CWeapon*>(Engine::Get_GameObject(L"Layer_Gun", L"UZI1"));
		m_vecWeapon.push_back(m_Weapon);
		m_tAbility->iGunTexture = 0;

		m_bUzi = false;
	}
	if (m_bShotgun == true)
	{
		dynamic_cast<CSniper*>(Engine::Get_GameObject(L"Layer_Gun", L"SNIPER"))->Off_Sniper();
		dynamic_cast<CUzi*>(Engine::Get_GameObject(L"Layer_Gun", L"UZI1"))->Off_Uzi();
		dynamic_cast<CUzi*>(Engine::Get_GameObject(L"Layer_Gun", L"UZI2"))->Off_Uzi();
		dynamic_cast<CShotgun*>(Engine::Get_GameObject(L"Layer_Gun", L"SHOTGUN"))->Set_ShotGun();

		//m_vecWeapon.push_back(dynamic_cast<CWeapon*>(Engine::Get_GameObject(L"Layer_Gun", L"SHOTGUN")));
		m_Weapon = dynamic_cast<CWeapon*>(Engine::Get_GameObject(L"Layer_Gun", L"SHOTGUN"));
		m_vecWeapon.push_back(m_Weapon);
		m_tAbility->iGunTexture = 2;

		m_bShotgun = false;
	}
	if (m_bSniper == true)
	{
		dynamic_cast<CUzi*>(Engine::Get_GameObject(L"Layer_Gun", L"UZI1"))->Off_Uzi();
		dynamic_cast<CUzi*>(Engine::Get_GameObject(L"Layer_Gun", L"UZI2"))->Off_Uzi();
		dynamic_cast<CShotgun*>(Engine::Get_GameObject(L"Layer_Gun", L"SHOTGUN"))->Off_ShotGun();
		dynamic_cast<CSniper*>(Engine::Get_GameObject(L"Layer_Gun", L"SNIPER"))->Set_Sniper();

		//m_vecWeapon.push_back(dynamic_cast<CWeapon*>(Engine::Get_GameObject(L"Layer_Gun", L"SNIPER")));
		m_Weapon = dynamic_cast<CWeapon*>(Engine::Get_GameObject(L"Layer_Gun", L"SNIPER"));
		m_vecWeapon.push_back(m_Weapon);
		m_tAbility->iGunTexture = 4;

		m_bSniper = false;
	}

	if (Get_DIKeyState(DIK_1) & 0x80)
	{
		if (!m_vecWeapon.empty())
		{
			if (m_vecWeapon[0] != nullptr)
			{
				dynamic_cast<CSniper*>(Engine::Get_GameObject(L"Layer_Gun", L"SNIPER"))->Off_Sniper();
				dynamic_cast<CShotgun*>(Engine::Get_GameObject(L"Layer_Gun", L"SHOTGUN"))->Off_ShotGun();
				dynamic_cast<CUzi*>(Engine::Get_GameObject(L"Layer_Gun", L"UZI1"))->Set_Uzi();
				dynamic_cast<CUzi*>(Engine::Get_GameObject(L"Layer_Gun", L"UZI2"))->Set_Uzi();
				m_Weapon = m_vecWeapon[0];
				m_tAbility->iGunTexture = 0; // 혹여나 총 업그레이드해서 다른 총으로 보이게 된다면 이 숫자와 UI/Gun 에 들어있는 숫자와 비교해서 넣으면됨.
			}
		}
	}
	if (Get_DIKeyState(DIK_2) & 0x80)
	{
		if (m_vecWeapon.size() >= 2)
		{
			if (m_vecWeapon[1] != nullptr)
			{
				dynamic_cast<CSniper*>(Engine::Get_GameObject(L"Layer_Gun", L"SNIPER"))->Off_Sniper();
				dynamic_cast<CUzi*>(Engine::Get_GameObject(L"Layer_Gun", L"UZI1"))->Off_Uzi();
				dynamic_cast<CUzi*>(Engine::Get_GameObject(L"Layer_Gun", L"UZI2"))->Off_Uzi();
				dynamic_cast<CShotgun*>(Engine::Get_GameObject(L"Layer_Gun", L"SHOTGUN"))->Set_ShotGun();
				m_Weapon = m_vecWeapon[1];
				m_tAbility->iGunTexture = 2;
			}
		}
	}
	if (Get_DIKeyState(DIK_3) & 0x80)
	{
		if (m_vecWeapon.size() >= 3)
		{
			if (m_vecWeapon[2] != nullptr)
			{
				dynamic_cast<CUzi*>(Engine::Get_GameObject(L"Layer_Gun", L"UZI1"))->Off_Uzi();
				dynamic_cast<CUzi*>(Engine::Get_GameObject(L"Layer_Gun", L"UZI2"))->Off_Uzi();
				dynamic_cast<CShotgun*>(Engine::Get_GameObject(L"Layer_Gun", L"SHOTGUN"))->Off_ShotGun();
				dynamic_cast<CSniper*>(Engine::Get_GameObject(L"Layer_Gun", L"SNIPER"))->Set_Sniper();
				m_Weapon = m_vecWeapon[2];
				m_tAbility->iGunTexture = 4;
			}
		}
	}
	if (Get_DIKeyState(DIK_4) & 0x80)
	{
		if (m_vecWeapon.size() >= 4)
		{
			if (m_vecWeapon[3] != nullptr)
			{
				m_Weapon = m_vecWeapon[3];
				m_tAbility->iGunTexture = 3;
			}
		}
	}
	if (Get_DIKeyState(DIK_5) & 0x80)
	{
		if (m_vecWeapon.size() >= 5)
		{
			if (m_vecWeapon[4] != nullptr)
			{
				m_Weapon = m_vecWeapon[4];
				m_tAbility->iGunTexture = 4;
			}
		}
	}
}

void CCubePlayer::Jump(void)
{
}

HRESULT CCubePlayer::Get_BodyTransform(void)
{
	m_pHeadWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"HEAD", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pHeadWorld, E_FAIL);
	m_pBodyWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"BODY", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);
	m_pLeftArmWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"L_ARM", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);
	m_pRightArmWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"R_ARM", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);
	m_pLeftLegWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"L_LEG", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);
	m_pRightLegWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"R_LEG", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);

	m_pLeftHandWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"L_HAND", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);
	m_pRightHandWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"R_HAND", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);
	m_pLeftFootWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"L_FOOT", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);
	m_pRightFootWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"R_FOOT", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);

	return S_OK;
}

HRESULT CCubePlayer::Player_Mapping(void)
{
	if (!m_MappingInit)
	{
		CGameObject*	m_pMapMonster = CPlayerMapping::Create(m_pGraphicDev);
		TCHAR* szCntName = new TCHAR[64];
		wsprintf(szCntName, L"Map");
		Engine::Add_GameObject(L"Layer_Mapping", m_pMapMonster, szCntName);
		m_listMonsterCnt.push_back(szCntName);

		m_pBaseMapping = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Mapping", szCntName, L"Proto_TransformCom", ID_DYNAMIC));
		NULL_CHECK_RETURN(m_pBaseMapping, E_FAIL);
		m_MappingInit = true;
	}

	return S_OK;
}

void CCubePlayer::Key_Input(const _float & fTimeDelta)
{
}

HRESULT CCubePlayer::Add_Component(void)
{
	CComponent* pInstance = nullptr;

	pInstance = m_pTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pInstance });

	pInstance = m_pHitBox = dynamic_cast<CHitBox*>(Engine::Clone_Proto(L"Proto_HitboxCom"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_HitboxCom", pInstance });

	pInstance = m_pCollision = dynamic_cast<CCollision*>(Engine::Clone_Proto(L"Proto_CollisionCom"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_CollisionCom", pInstance });

	pInstance = m_pCalculatorCom = dynamic_cast<CCalculator*>(Engine::Clone_Proto(L"Proto_CalculatorCom"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CalculatorCom", pInstance });

	return S_OK;
}

CCubePlayer * CCubePlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCubePlayer* pInstance = new CCubePlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	Safe_Release(pInstance);

	return pInstance;
}
     
void CCubePlayer::Free(void)
{
	for (auto& iter : m_listMonsterCnt)
	{
		if (iter != nullptr)
			delete iter;
	}

	Safe_Delete<ABILITY*>(m_tAbility);

	m_listMonsterCnt.clear();
	CGameObject::Free();
}
