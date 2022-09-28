#include "stdafx.h"
#include "..\Header\Uzi.h"
#include "CubePlayer.h"

CUzi::CUzi(LPDIRECT3DDEVICE9 pGraphicDev)
	:CWeapon(pGraphicDev)
{
}


CUzi::~CUzi()
{
}

HRESULT CUzi::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

_int CUzi::Update_Object(const _float & fTimeDelta)
{
	m_fTimeDelta = fTimeDelta;

	//Assemble();

	if (Get_DIKeyState(DIK_8))
	{
		Test1 += 0.1f;
	}
	if (Get_DIKeyState(DIK_9))
	{
		Test2 += 0.1f;
	}
	if (Get_DIKeyState(DIK_0))
	{
		Test3 += 0.1f;
	}
	if (Get_DIKeyState(DIK_I))
	{
		Test1 -= 0.1f;
	}
	if (Get_DIKeyState(DIK_O))
	{
		Test2 -= 0.1f;
	}
	if (Get_DIKeyState(DIK_P))
	{
		Test3 -= 0.1f;
	}

	//TransAxis();

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);
	CGameObject::Update_Object(fTimeDelta);

	return 0;	
}

void CUzi::LateUpdate_Object(void)
{	
	//FAILED_CHECK_RETURN(Add_Parts(), );
	FAILED_CHECK_RETURN(Get_Parts(), );
	CGameObject::LateUpdate_Object();

	if (Engine::Get_GameObject(L"Layer_Gun", L"UZI1") == this)
		TransAxisUzi1();
	else if (Engine::Get_GameObject(L"Layer_Gun", L"UZI2") == this)
		TransAxisUzi2();

	//Assemble();

	//Animation_Fire();
}

void CUzi::Render_Object(void)
{	
}

void CUzi::TransAxisUzi1(void)
{

#pragma region 아까운거...

	//	역행렬

	//FAILED_CHECK_RETURN(Get_Parts(), );

	//_vec3 vScale5;
	//_matrix matScale5;
	//m_pPart5->Get_Scale(&vScale5);
	//D3DXMatrixScaling(&matScale5, vScale5.x, vScale5.y, vScale5.z);

	//CCubePlayer* pPlayer = dynamic_cast<CCubePlayer*>(Engine::Get_GameObject(L"Layer_Character", L"PLAYER"));
	//_float fAngle, fLookAngle, fArmAngle;
	//pPlayer->Get_Angle(fLookAngle, fAngle, fArmAngle);

	//CTransform*		m_pRightHandWorld = nullptr;
	//m_pRightHandWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"R_HAND", L"Proto_TransformCom", ID_STATIC));
	//NULL_CHECK_RETURN(m_pRightHandWorld, );

	//_vec3	vHandScale, vHandRotX, vHandRotY, vHAndRotExtra, vHandPos;
	//_matrix matHandScale, matHandRotX, matHandRotY, matHandRotExtra, matHandTrans;
	//_matrix matSyncX, matReplaceX, matSyncY, matReplaceY, matSyncExtra, matReplaceExtra;
	//_float	fMoveX = -3.f, fMoveY = 1.5f, fMoveExtra = -1.f;

	////////////	Trans
	//m_pRightHandWorld->Get_Info(INFO_POS, &vHandPos);
	//D3DXMatrixTranslation(&matHandTrans, vHandPos.x, vHandPos.y, vHandPos.z);
	//_matrix matHandTrans_Inverse;
	//D3DXMatrixInverse(&matHandTrans_Inverse, nullptr, &matHandTrans);

	////////////	Y
	//D3DXMatrixTranslation(&matSyncY, fMoveY, 0.f, 0.f);
	//D3DXMatrixTranslation(&matReplaceY, -fMoveY, 0.f, 0.f);
	//D3DXMatrixRotationY(&matHandRotY, -fLookAngle);

	//_matrix matSyncY_Inverse, matReplaceY_Inverse, matHandRotY_Inverse;
	//D3DXMatrixInverse(&matSyncY_Inverse, nullptr, &matSyncY);
	//D3DXMatrixInverse(&matReplaceY_Inverse, nullptr, &matReplaceY);
	//D3DXMatrixInverse(&matHandRotY_Inverse, nullptr, &matHandRotY);

	////////////	X
	//D3DXMatrixTranslation(&matSyncX, 0.f, fMoveX, 0.f);
	//D3DXMatrixTranslation(&matReplaceX, 0.f, -fMoveX, 0.f);
	//D3DXMatrixRotationX(&matHandRotX, -fAngle);

	//_matrix matSyncX_Inverse, matReplaceX_Inverse, matHandRotX_Inverse;
	//D3DXMatrixInverse(&matSyncX_Inverse, nullptr, &matSyncX);
	//D3DXMatrixInverse(&matReplaceX_Inverse, nullptr, &matReplaceX);
	//D3DXMatrixInverse(&matHandRotX_Inverse, nullptr, &matHandRotX);

	////////////	Extra
	//_matrix matSyncExtra_Inverse, matReplaceExtra_Inverse, matHandRotExtra_Inverse;
	//D3DXMatrixTranslation(&matSyncExtra, 0.f, fMoveExtra, 0.f);
	//D3DXMatrixTranslation(&matReplaceExtra, 0.f, -fMoveExtra, 0.f);
	//D3DXMatrixRotationX(&matHandRotExtra, fArmAngle);

	//D3DXMatrixInverse(&matSyncExtra_Inverse, nullptr, &matSyncExtra);
	//D3DXMatrixInverse(&matReplaceExtra_Inverse, nullptr, &matReplaceExtra);
	//D3DXMatrixInverse(&matHandRotExtra_Inverse, nullptr, &matHandRotExtra);

	////////////	Scale
	//m_pRightHandWorld->Get_Scale(&vHandScale);
	//D3DXMatrixScaling(&matHandScale, vHandScale.x, vHandScale.y, vHandScale.z);
	//_matrix matHandScale_Inverse;
	//D3DXMatrixInverse(&matHandScale_Inverse, nullptr, &matHandScale);

	//_matrix matHandWorld;
	//m_pRightHandWorld->Get_WorldMatrix(&matHandWorld);

	//_matrix matInverseWorld;
	//matInverseWorld = matHandWorld * matHandTrans_Inverse
	//	* matReplaceY_Inverse * matHandRotY_Inverse * matSyncY_Inverse
	//	* matReplaceX_Inverse * matHandRotX_Inverse * matSyncX_Inverse
	//	* matReplaceExtra_Inverse * matHandRotExtra_Inverse * matSyncExtra_Inverse
	//	* matHandScale_Inverse
	//	* matScale5
	//	* matSyncExtra * matHandRotExtra * matReplaceExtra
	//	* matSyncX * matHandRotX * matReplaceX
	//	* matSyncY * matHandRotY * matReplaceY
	//	* matHandTrans;

	//m_pPart5->Set_WorldMatrix(&matInverseWorld);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*_matrix	matHandWorld, matBodyWorld;
	m_pRightHandWorld->Get_WorldMatrix(&matHandWorld);
	m_pBodyWorld->Get_WorldMatrix(&matBodyWorld);

	m_pPart4->Set_Pos(vWeaponPos.x, vWeaponPos.y, vWeaponPos.z + 0.9);
	m_pPart4->Rotation_Axis_Gun(0.9f, D3DXToRadian(90.f) - fAngle,
	0.f, -fLookAngle,
	0.f, fArmAngle);
	cout << Test1 << " " << Test2 << " " << Test3 << endl;*/

	//m_pPart1->Set_Pos(vWeaponPos.x - 0.f, vWeaponPos.y + 0.f, vWeaponPos.z);
	//m_pPart1->Rotation_Axis_Gun(0.f, fArmAngle + D3DXToRadian(90.f) - fAngle,
	//							0.f, -fLookAngle,
	//							0.f, 0.f);

	/*m_pPart2->Set_Pos(vWeaponPos.x, vWeaponPos.y - 0.6, vWeaponPos.z + 0.9f);
	m_pPart2->Rotation_Axis_Gun(Test1, fArmAngle + D3DXToRadian(90.f) - fAngle,
	Test2, -fLookAngle,
	Test3, 0.f);
	cout << Test1 << " " << Test2 << " " << Test3 << endl;*/

	/*m_pPart3->Set_Pos(vWeaponPos.x, vWeaponPos.y, vWeaponPos.z + 1.f);
	m_pPart3->Set_Rotation(ROT_X, fArmAngle + D3DXToRadian(90.f) - fAngle);
	m_pPart3->Set_Rotation(ROT_Y, -fLookAngle);
	m_pPart3->Static_Update();
	cout << Test1 << " " << Test2 << " " << Test3 << endl;*/

	/*_vec3	vBodyPos(0, 0, 0);
	m_pBodyWorld->Get_Info(INFO_POS, &vBodyPos);

	m_pPart5->Set_Pos(vBodyPos.x + 2.f, vBodyPos.y, vBodyPos.z);
	m_pPart5->Set_Rotation(ROT_X, -(D3DXToRadian(90.f)));

	m_pPart5->Rotation_Axis_Gun(-2.f, 2.f, -fAngle, -fLookAngle, 3.f, D3DXToRadian(90.f));

	cout << Test1 << " " << Test2 << " " << Test3 << endl;*/

#pragma endregion

	CCubePlayer* pPlayer = dynamic_cast<CCubePlayer*>(Engine::Get_GameObject(L"Layer_Character", L"PLAYER"));
	_float fLookAngle, fLeftArmAngle, fRightArmAngle, fHandAngle;
	pPlayer->Get_Angle(fLookAngle, fLeftArmAngle, fRightArmAngle, fHandAngle);

	FAILED_CHECK_RETURN(Get_Parts(), );

	CTransform*		m_pRightHandWorld = nullptr;
	m_pRightHandWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"R_HAND", L"Proto_TransformCom", ID_STATIC));
	NULL_CHECK_RETURN(m_pRightHandWorld, );

	_vec3 vWeaponPos, vPos, vRight, vUp, vLook, vAngle, vScale;
	m_pRightHandWorld->Get_Info(INFO_RIGHT, &vRight);
	m_pRightHandWorld->Get_Info(INFO_UP, &vUp);
	m_pRightHandWorld->Get_Info(INFO_LOOK, &vLook);
	m_pRightHandWorld->Get_Info(INFO_POS, &vPos);
	m_pRightHandWorld->Get_Scale(&vScale);

	vWeaponPos = vUp * -1.f;
	vWeaponPos += vPos;

	m_pPart5->Set_Pos(vWeaponPos.x, vWeaponPos.y, vWeaponPos.z);
	m_pPart5->Set_Rotation(ROT_X, fRightArmAngle + D3DXToRadian(90.f) - fHandAngle);
	m_pPart5->Set_Rotation(ROT_Y, -fLookAngle);
	m_pPart5->Static_Update();

	vWeaponPos = (vUp * -1.5f) + (vLook);
	vWeaponPos += vPos;

	m_pPart4->Set_Pos(vWeaponPos.x, vWeaponPos.y, vWeaponPos.z);
	m_pPart4->Set_Rotation(ROT_X, fRightArmAngle + D3DXToRadian(90.f) - fHandAngle);
	m_pPart4->Set_Rotation(ROT_Y, -fLookAngle);
	m_pPart4->Static_Update();

	vWeaponPos = (vUp * -2.f) + (vLook * 0.4f);
	vWeaponPos += vPos;

	m_pPart3->Set_Pos(vWeaponPos.x, vWeaponPos.y, vWeaponPos.z);
	m_pPart3->Set_Rotation(ROT_X, fRightArmAngle + D3DXToRadian(90.f) - fHandAngle);
	m_pPart3->Set_Rotation(ROT_Y, -fLookAngle);
	m_pPart3->Static_Update();

	vWeaponPos = (vUp * -1.8f) + (vLook * 1.8f);
	vWeaponPos += vPos;

	m_pPart2->Set_Pos(vWeaponPos.x, vWeaponPos.y, vWeaponPos.z);
	m_pPart2->Set_Rotation(ROT_X, fRightArmAngle + D3DXToRadian(90.f) - fHandAngle);
	m_pPart2->Set_Rotation(ROT_Y, -fLookAngle);
	m_pPart2->Static_Update();

	vWeaponPos = (vUp * -3.f) + (vLook * 1.8f);
	vWeaponPos += vPos;

	m_pPart1->Set_Pos(vWeaponPos.x, vWeaponPos.y, vWeaponPos.z);
	m_pPart1->Set_Rotation(ROT_X, fRightArmAngle + D3DXToRadian(90.f) - fHandAngle);
	m_pPart1->Set_Rotation(ROT_Y, -fLookAngle);
	m_pPart1->Static_Update();
}

void CUzi::TransAxisUzi2(void)
{
	CCubePlayer* pPlayer = dynamic_cast<CCubePlayer*>(Engine::Get_GameObject(L"Layer_Character", L"PLAYER"));
	_float fLookAngle, fLeftArmAngle, fRightArmAngle, fHandAngle;
	pPlayer->Get_Angle(fLookAngle, fLeftArmAngle, fRightArmAngle, fHandAngle);

	FAILED_CHECK_RETURN(Get_Parts(), );

	CTransform*		m_pLeftHandWorld = nullptr;
	m_pLeftHandWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"L_HAND", L"Proto_TransformCom", ID_STATIC));
	NULL_CHECK_RETURN(m_pLeftHandWorld, );

	_vec3 vWeaponPos, vPos, vRight, vUp, vLook, vAngle, vScale;
	m_pLeftHandWorld->Get_Info(INFO_RIGHT, &vRight);
	m_pLeftHandWorld->Get_Info(INFO_UP, &vUp);
	m_pLeftHandWorld->Get_Info(INFO_LOOK, &vLook);
	m_pLeftHandWorld->Get_Info(INFO_POS, &vPos);
	m_pLeftHandWorld->Get_Scale(&vScale);

	vWeaponPos = vUp * -1.f;
	vWeaponPos += vPos;

	m_pPart5->Set_Pos(vWeaponPos.x, vWeaponPos.y, vWeaponPos.z);
	m_pPart5->Set_Rotation(ROT_X, fLeftArmAngle + D3DXToRadian(90.f) + fHandAngle);
	m_pPart5->Set_Rotation(ROT_Y, -fLookAngle);
	m_pPart5->Static_Update();

	vWeaponPos = (vUp * -1.5f) + (vLook);
	vWeaponPos += vPos;

	m_pPart4->Set_Pos(vWeaponPos.x, vWeaponPos.y, vWeaponPos.z);
	m_pPart4->Set_Rotation(ROT_X, fLeftArmAngle + D3DXToRadian(90.f) + fHandAngle);
	m_pPart4->Set_Rotation(ROT_Y, -fLookAngle);
	m_pPart4->Static_Update();

	vWeaponPos = (vUp * -2.f) + (vLook * 0.4f);
	vWeaponPos += vPos;

	m_pPart3->Set_Pos(vWeaponPos.x, vWeaponPos.y, vWeaponPos.z);
	m_pPart3->Set_Rotation(ROT_X, fLeftArmAngle + D3DXToRadian(90.f) + fHandAngle);
	m_pPart3->Set_Rotation(ROT_Y, -fLookAngle);
	m_pPart3->Static_Update();

	vWeaponPos = (vUp * -1.8f) + (vLook * 1.8f);
	vWeaponPos += vPos;

	m_pPart2->Set_Pos(vWeaponPos.x, vWeaponPos.y, vWeaponPos.z);
	m_pPart2->Set_Rotation(ROT_X, fLeftArmAngle + D3DXToRadian(90.f) + fHandAngle);
	m_pPart2->Set_Rotation(ROT_Y, -fLookAngle);
	m_pPart2->Static_Update();

	vWeaponPos = (vUp * -3.f) + (vLook * 1.8f);
	vWeaponPos += vPos;

	m_pPart1->Set_Pos(vWeaponPos.x, vWeaponPos.y, vWeaponPos.z);
	m_pPart1->Set_Rotation(ROT_X, fLeftArmAngle + D3DXToRadian(90.f) + fHandAngle);
	m_pPart1->Set_Rotation(ROT_Y, -fLookAngle);
	m_pPart1->Static_Update();
}

HRESULT CUzi::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	return S_OK;
}

HRESULT CUzi::Add_Parts()
{			

#pragma region 수정

	/*if (!m_bPartInit)
	{
	CGameObject*	m_pUziCreate1 = CUziPart1::Create(m_pGraphicDev);
	CGameObject*	m_pUziCreate2 = CUziPart2::Create(m_pGraphicDev);
	CGameObject*	m_pUziCreate3 = CUziPart3::Create(m_pGraphicDev);
	CGameObject*	m_pUziCreate4 = CUziPart4::Create(m_pGraphicDev);
	CGameObject*	m_pUziCreate5 = CUziPart5::Create(m_pGraphicDev);

	if (Engine::Get_GameObject(L"Layer_GameLogic", L"UZI1") == this)
	{
	TCHAR* szFinalName = new TCHAR[64];
	wsprintf(szFinalName, L"UziPart1");
	Engine::Add_GameObject(L"Layer_GameLogic", m_pUziCreate1, szFinalName);
	m_liszFinalName.push_back(szFinalName);

	TCHAR* szFinalName2 = new TCHAR[64];
	wsprintf(szFinalName2, L"UziPart2");
	Engine::Add_GameObject(L"Layer_GameLogic", m_pUziCreate2, szFinalName2);
	m_liszFinalName.push_back(szFinalName2);

	TCHAR* szFinalName3 = new TCHAR[64];
	wsprintf(szFinalName3, L"UziPart3");
	Engine::Add_GameObject(L"Layer_GameLogic", m_pUziCreate3, szFinalName3);
	m_liszFinalName.push_back(szFinalName3);

	TCHAR* szFinalName4 = new TCHAR[64];
	wsprintf(szFinalName4, L"UziPart4");
	Engine::Add_GameObject(L"Layer_GameLogic", m_pUziCreate4, szFinalName4);
	m_liszFinalName.push_back(szFinalName4);

	TCHAR* szFinalName5 = new TCHAR[64];
	wsprintf(szFinalName5, L"UziPart5");
	Engine::Add_GameObject(L"Layer_GameLogic", m_pUziCreate5, szFinalName5);
	m_liszFinalName.push_back(szFinalName5);

	pGameObject = CUzi::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UZI2", pGameObject), E_FAIL);
	}

	m_bPartInit = true;
	}*/

#pragma endregion 수정
	
	if (!m_bPartInit)
	{
		CGameObject*	pGameObject = nullptr;
		
		pGameObject = CUziPart1::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		Engine::Add_GameObject(L"Layer_Gun", pGameObject, L"Uzi_Part_1_1");

		pGameObject = CUziPart2::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		Engine::Add_GameObject(L"Layer_Gun", pGameObject, L"Uzi_Part_1_2");

		pGameObject = CUziPart3::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		Engine::Add_GameObject(L"Layer_Gun", pGameObject, L"Uzi_Part_1_3");

		pGameObject = CUziPart4::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		Engine::Add_GameObject(L"Layer_Gun", pGameObject, L"Uzi_Part_1_4");

		pGameObject = CUziPart5::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		Engine::Add_GameObject(L"Layer_Gun", pGameObject, L"Uzi_Part_1_5");
		
		pGameObject = CUziPart1::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		Engine::Add_GameObject(L"Layer_Gun", pGameObject, L"Uzi_Part_2_1");

		pGameObject = CUziPart2::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		Engine::Add_GameObject(L"Layer_Gun", pGameObject, L"Uzi_Part_2_2");

		pGameObject = CUziPart3::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		Engine::Add_GameObject(L"Layer_Gun", pGameObject, L"Uzi_Part_2_3");

		pGameObject = CUziPart4::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		Engine::Add_GameObject(L"Layer_Gun", pGameObject, L"Uzi_Part_2_4");

		pGameObject = CUziPart5::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		Engine::Add_GameObject(L"Layer_Gun", pGameObject, L"Uzi_Part_2_5");
		
		m_bPartInit = true;
	}

	return S_OK;
}

HRESULT CUzi::Get_Parts(void)
{
	if (Engine::Get_GameObject(L"Layer_Gun", L"UZI1") == this)
	{
		m_pPart1 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Gun", L"Uzi_Part_1_1", L"Proto_TransformCom", ID_STATIC));
		NULL_CHECK_RETURN(m_pPart1, E_FAIL);
		m_pPart2 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Gun", L"Uzi_Part_1_2", L"Proto_TransformCom", ID_STATIC));
		NULL_CHECK_RETURN(m_pPart2, E_FAIL);
		m_pPart3 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Gun", L"Uzi_Part_1_3", L"Proto_TransformCom", ID_STATIC));
		NULL_CHECK_RETURN(m_pPart3, E_FAIL);
		m_pPart4 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Gun", L"Uzi_Part_1_4", L"Proto_TransformCom", ID_STATIC));
		NULL_CHECK_RETURN(m_pPart4, E_FAIL);
		m_pPart5 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Gun", L"Uzi_Part_1_5", L"Proto_TransformCom", ID_STATIC));
		NULL_CHECK_RETURN(m_pPart5, E_FAIL);
	}
	else if (Engine::Get_GameObject(L"Layer_Gun", L"UZI2") == this)
	{
		m_pPart1 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Gun", L"Uzi_Part_2_1", L"Proto_TransformCom", ID_STATIC));
		NULL_CHECK_RETURN(m_pPart1, E_FAIL);
		m_pPart2 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Gun", L"Uzi_Part_2_2", L"Proto_TransformCom", ID_STATIC));
		NULL_CHECK_RETURN(m_pPart2, E_FAIL);
		m_pPart3 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Gun", L"Uzi_Part_2_3", L"Proto_TransformCom", ID_STATIC));
		NULL_CHECK_RETURN(m_pPart3, E_FAIL);
		m_pPart4 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Gun", L"Uzi_Part_2_4", L"Proto_TransformCom", ID_STATIC));
		NULL_CHECK_RETURN(m_pPart4, E_FAIL);
		m_pPart5 = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Gun", L"Uzi_Part_2_5", L"Proto_TransformCom", ID_STATIC));
		NULL_CHECK_RETURN(m_pPart5, E_FAIL);
	}
	return S_OK;
}


void CUzi::Assemble(void)
{
	FAILED_CHECK_RETURN(Get_Parts(),  );

	CTransform*		m_pRightHandWorld = nullptr;
	m_pRightHandWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"R_HAND", L"Proto_TransformCom", ID_STATIC));
	NULL_CHECK_RETURN(m_pRightHandWorld, );

	_vec3 vHandPos, vHandRight, vHandLook, vHandUp;
	m_pRightHandWorld->Get_BeforeInfo(INFO_RIGHT, &vHandRight);
	m_pRightHandWorld->Get_BeforeInfo(INFO_UP, &vHandUp);
	m_pRightHandWorld->Get_BeforeInfo(INFO_LOOK, &vHandLook);
	m_pRightHandWorld->Get_BeforeInfo(INFO_POS, &vHandPos);

	_vec3 vBodyPos;
	m_pPart5->Set_Pos(vHandPos.x, vHandPos.y, vHandPos.z);

	m_pPart1->Set_Pos(vBodyPos.x -1.6f, vBodyPos.y +.6f, vBodyPos.z);
	m_pPart2->Set_Pos(vBodyPos.x -.2f, vBodyPos.y +.6f, vBodyPos.z);
	m_pPart3->Set_Pos(vBodyPos.x -.6f, vBodyPos.y + .2f, vBodyPos.z);
	m_pPart4->Set_Pos(vBodyPos.x -.1f, vBodyPos.y + .4f, vBodyPos.z);
	
	//cout << vBodyPos.y << endl;
}

void CUzi::Animation_Fire(void)
{
}


void CUzi::Set_OnTerrain(void)
{
	/*m_pUziWorld = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_Character", L"UziPart5", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK_RETURN(m_pUziWorld, );

	_vec3		vPos;
	m_pUziWorld->Get_Info(INFO_POS, &vPos);

	Engine::CTerrainTex*	pTerrainTexCom = dynamic_cast<Engine::CTerrainTex*>(Engine::Get_Component(L"Layer_Environment", L"Terrain", L"Proto_TerrainTexCom", ID_STATIC));
	NULL_CHECK(pTerrainTexCom);

	_float fHeight = m_pCalculatorCom->HeightOnTerrain(&vPos, pTerrainTexCom->Get_VtxPos(), VTXCNTX, VTXCNTZ);

	m_pUziWorld->Set_Pos(vPos.x, fHeight, vPos.z);*/
}


CUzi * CUzi::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CUzi* pInstance = new CUzi(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;	
}

void CUzi::Free(void)
{
	for (auto& iter : m_liszFinalName)
	{
		if (iter != nullptr)
			delete iter;
	}
	m_liszFinalName.clear();
	CWeapon::Free();
}

