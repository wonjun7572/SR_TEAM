#include "stdafx.h"
#include "..\Header\CubePlayer.h"

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

	return S_OK;
}

_int CCubePlayer::Update_Object(const _float & fTimeDelta)
{
	Key_Input(fTimeDelta);

	CGameObject::Update_Object(fTimeDelta);

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
	//m_pLeftShoulderWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Ready_Layer_Environment", L"L_SHOULDER", L"Proto_TransformCom", ID_DYNAMIC));
	//NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);
	//m_pRightShoulderWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Ready_Layer_Environment", L"R_SHOULDER", L"Proto_TransformCom", ID_DYNAMIC));
	//NULL_CHECK_RETURN(m_pBodyWorld, E_FAIL);

	//	¸öÃ¼ Á¶¸³, ¹Ùµð ±âÁØ ÁÂÇ¥
	_vec3 vBodyPos;
	m_pBodyWorld->Get_Info(INFO_POS, &vBodyPos);
	m_pHeadWorld->Set_Pos(vBodyPos.x, vBodyPos.y + 3.f, vBodyPos.z);
	m_pLeftArmWorld->Set_Pos(vBodyPos.x - 1.5f, vBodyPos.y, vBodyPos.z);
	m_pRightArmWorld->Set_Pos(vBodyPos.x + 1.5f, vBodyPos.y, vBodyPos.z);
	m_pLeftLegWorld->Set_Pos(vBodyPos.x - 0.5f, vBodyPos.y - 4.f, vBodyPos.z);
	m_pRightLegWorld->Set_Pos(vBodyPos.x + 0.5f, vBodyPos.y - 4.f, vBodyPos.z);

	//m_pLeftArmWorld->Rotation_Axis_X(2.f, D3DXToRadian(0.f));
	//m_pRightArmWorld->Rotation_Axis_X(2.f, D3DXToRadian(0.f));

	return 0;
}

void CCubePlayer::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();

	Set_OnTerrain();
}

void CCubePlayer::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
}

void CCubePlayer::Set_OnTerrain(void)
{
	_vec3		vPos;
	m_pTransform->Get_Info(INFO_POS, &vPos);

	Engine::CTerrainTex*	pTerrainTexCom = dynamic_cast<Engine::CTerrainTex*>(Engine::Get_Component(L"Layer_Environment", L"Terrain", L"Proto_TerrainTexCom", ID_STATIC));
	NULL_CHECK(pTerrainTexCom);

	_float fHeight = m_pCalculatorCom->HeightOnTerrain(&vPos, pTerrainTexCom->Get_VtxPos(), VTXCNTX, VTXCNTZ);

	m_pTransform->Set_Pos(vPos.x, fHeight, vPos.z);
}

void CCubePlayer::Key_Input(const _float & fTimeDelta)
{
	_vec3	vDir;

#pragma region ÆÈ´Ù¸®È¸Àü

	if (Get_DIKeyState(DIK_W) || Get_DIKeyState(DIK_A) || Get_DIKeyState(DIK_S) || Get_DIKeyState(DIK_D))
	{
		if (m_fAngle > 0.3f)
			m_bWalkAngle = false;
		if (m_fAngle < -0.3f)
			m_bWalkAngle = true;

		if (m_bWalkAngle == true)
		{
			m_fAngle += fTimeDelta * 4;

			m_pLeftArmWorld->Rotation_Axis_X(2.f, m_fAngle);
			m_pRightArmWorld->Rotation_Axis_X(2.f, -m_fAngle);

			m_pLeftLegWorld->Rotation_Axis_X(2.f, -m_fAngle);
			m_pRightLegWorld->Rotation_Axis_X(2.f, +m_fAngle);
		}
		else if (m_bWalkAngle == false)
		{
			m_fAngle -= fTimeDelta * 4;

			m_pLeftArmWorld->Rotation_Axis_X(2.f, m_fAngle);
			m_pRightArmWorld->Rotation_Axis_X(2.f, -m_fAngle);

			m_pLeftLegWorld->Rotation_Axis_X(2.f, -m_fAngle);
			m_pRightLegWorld->Rotation_Axis_X(2.f, +m_fAngle);
		}
	}
	else if (m_fAngle != 0)
	{
		if (m_fAngle > 0)
		{
			m_fAngle -= fTimeDelta;
			if (m_fAngle < 0)
				m_fAngle = 0;

			m_pLeftArmWorld->Rotation_Axis_X(2.f, m_fAngle);
			m_pRightArmWorld->Rotation_Axis_X(2.f, -m_fAngle);
			m_pLeftLegWorld->Rotation_Axis_X(2.f, -m_fAngle);
			m_pRightLegWorld->Rotation_Axis_X(2.f, m_fAngle);
		}
		else if (m_fAngle < 0)
		{
			m_fAngle += fTimeDelta;
			if (m_fAngle > 0)
				m_fAngle = 0;

			m_pLeftArmWorld->Rotation_Axis_X(2.f, m_fAngle);
			m_pRightArmWorld->Rotation_Axis_X(2.f, -m_fAngle);
			m_pLeftLegWorld->Rotation_Axis_X(2.f, -m_fAngle);
			m_pRightLegWorld->Rotation_Axis_X(2.f, m_fAngle);
		}

	}

#pragma endregion ÆÈ´Ù¸®¿òÁ÷ÀÓ

	if (Get_DIKeyState(DIK_W))
	{
		m_pBodyWorld->Get_Info(INFO_LOOK, &vDir);

		m_pBodyWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
		m_pHeadWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
		m_pLeftArmWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
		m_pRightArmWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
		m_pLeftLegWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
		m_pRightLegWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	}
	if (Get_DIKeyState(DIK_S))
	{
		m_pBodyWorld->Get_Info(INFO_LOOK, &vDir);

		m_pBodyWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
		m_pHeadWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
		m_pLeftArmWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
		m_pRightArmWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
		m_pLeftLegWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
		m_pRightLegWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	}
	if (Get_DIKeyState(DIK_A))
	{
		m_pBodyWorld->Get_Info(INFO_RIGHT, &vDir);

		if (m_fLookAngle > -0.2f)
		{
			m_fLookAngle -= fTimeDelta * 5.f;
			m_pBodyWorld->Rotation(ROT_Y, -(fTimeDelta * 5.f));
		}

		//		m_pBodyWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
		//		m_pHeadWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));

		/*m_pLeftArmWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
		m_pRightArmWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));*/

		m_pLeftArmWorld->Rotation_Axis_Y(-1.5f, m_fLookAngle);
		m_pRightArmWorld->Rotation_Axis_Y(1.5f, m_fLookAngle);

		//		m_pLeftLegWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
		//		m_pRightLegWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	}
	if (Get_DIKeyState(DIK_D))
	{
		m_pBodyWorld->Get_Info(INFO_RIGHT, &vDir);

		if (m_fLookAngle < 0.2f)
		{
			m_fLookAngle += fTimeDelta * 5.f;
			m_pBodyWorld->Rotation(ROT_Y, fTimeDelta * 5.f);
		}

		m_pLeftArmWorld->Rotation_Axis_Y(-1.5f, m_fLookAngle);
		m_pRightArmWorld->Rotation_Axis_Y(1.5f, m_fLookAngle);

		/*m_pBodyWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
		m_pHeadWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
		m_pLeftArmWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
		m_pRightArmWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
		m_pLeftLegWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
		m_pRightLegWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));*/
	}

	if (Get_DIKeyState(DIK_SPACE))
	{
		m_pBodyWorld->Get_Info(INFO_UP, &vDir);

		m_pBodyWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
		m_pHeadWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
		m_pLeftArmWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
		m_pRightArmWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
		m_pLeftLegWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
		m_pRightLegWorld->Move_Pos(&(vDir * 10.f * fTimeDelta));
	}

	if (Get_DIKeyState(DIK_LSHIFT))
	{
		m_pBodyWorld->Get_Info(INFO_UP, &vDir);

		m_pBodyWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
		m_pHeadWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
		m_pLeftArmWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
		m_pRightArmWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
		m_pLeftLegWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
		m_pRightLegWorld->Move_Pos(&(vDir * -10.f * fTimeDelta));
	}
}

HRESULT CCubePlayer::Add_Component(void)
{
	CComponent* pInstance = nullptr;

	pInstance = m_pTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(pInstance, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pInstance });

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
	CGameObject::Free();
}
