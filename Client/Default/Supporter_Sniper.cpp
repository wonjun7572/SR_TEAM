#include "stdafx.h"
#include "Supporter_Sniper.h"
#include "TransAxisBox.h"
#include "PoolMgr.h"
#include "VerticalLine.h"

CSupporter_Sniper::CSupporter_Sniper(LPDIRECT3DDEVICE9 pGraphicDev)
	:CSupporter(pGraphicDev)
{
}

CSupporter_Sniper::~CSupporter_Sniper()
{
}

HRESULT CSupporter_Sniper::Ready_Object(const _vec3 & vPos, _tchar * Name)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_SupporterName = Name;

	m_STATE = SNIPERSUPPORT_IDLE;
	m_IDLE = SNIPERSUPPORT_IDLE_1;
	m_WALK = SNIPERSUPPORT_WALK_1;
	m_ATTACK = SNIPERSUPPORT_ATTACK_1;
	m_DROP = SPDROP_1;

	m_pTransform->Set_Scale(0.3f, 0.3f, 0.3f);
	m_pTransform->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pTransform->Static_Update();

	_vec3 vAnimationPos;
	m_pTransform->Get_Info(INFO_POS, &vAnimationPos);

	m_pHitBoxTransform->Set_Scale(&_vec3(0.3f, 0.3f, 0.3f));
	m_pHitBoxTransform->Set_Pos(vAnimationPos.x, vAnimationPos.y, vAnimationPos.z);
	m_pHitBoxTransform->Static_Update();

	m_pSphereTransCom->Set_Scale(&_vec3(10.f, 10.f, 10.f));
	m_pSphereTransCom->Set_Pos(vAnimationPos.x, vAnimationPos.y, vAnimationPos.z);
	m_pSphereTransCom->Static_Update();

	return S_OK;
}

_int CSupporter_Sniper::Update_Object(const _float & fTimeDelta)
{
	m_fTimeDelta = fTimeDelta;

	if (m_pPlayerTransCom == nullptr)
		m_pPlayerTransCom = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_CHARACTER, L"PLAYER", TRANSFORM_COMP, ID_DYNAMIC));

	if (m_bFirst)
	{
		m_bFirst = false;
		Engine::Get_Scene()->New_Layer(m_SupporterName);
		pMyLayer = Engine::Get_Layer(m_SupporterName);

		FAILED_CHECK_RETURN(Build(), -1);

		Load_Animation(L"../../Data/Supporter_Sniper/SNIPER_IDLE_1.dat", 0);
		Load_Animation(L"../../Data/Supporter_Sniper/SNIPER_IDLE_2.dat", 1);

		Load_Animation(L"../../Data/Supporter_Sniper/SNIPER_WALK_1.dat", 2);
		Load_Animation(L"../../Data/Supporter_Sniper/SNIPER_WALK_2.dat", 3);

		Load_Animation(L"../../Data/Supporter_Sniper/SNIPER_ATTACK_1.dat", 4);
		Load_Animation(L"../../Data/Supporter_Sniper/SNIPER_ATTACK_2.dat", 5);

		Load_Animation(L"../../Data/Supporter_Sniper/SNIPER_DROP.dat", 6);
		Load_Animation(L"../../Data/Supporter_Sniper/SNIPER_DROP_COMPLETE.dat", 7);
	}

	_vec3 vPlayerScale;
	m_pPlayerTransCom->Get_Scale(&vPlayerScale);
	_vec3 vScale;
	m_pSphereTransCom->Get_Scale(&vScale);
	_vec3 vPlayerPos;
	m_pPlayerTransCom->Get_Info(INFO_POS, &vPlayerPos);

	_vec3 vPosition;
	m_pTransform->Get_Info(INFO_POS, &vPosition);

	if (vPosition.y >= 0.6f)
	{
		m_pTransform->Move_Pos(&(_vec3(0.f, -1.f, 0.f) * 10.f * fTimeDelta));

		CVerticalLine* pVerticalLine = nullptr;
		_vec3 vPos;
		_vec3 vDir;
		m_pTransform->Get_Info(INFO_POS, &vPos);
		if (!pVerticalLine)
			pVerticalLine = dynamic_cast<CVerticalLine*>(Engine::Get_GameObject(STAGE_ENVIRONMENT, L"VerticalLine"));
		pVerticalLine->Set_PcleDir(vDir);
		pVerticalLine->Set_PclePos(vPos);
		for (_int i = 0; i < 250; ++i)
		{
			pVerticalLine->addParticle();
		}
	}
	else if (vPosition.y <= 0.7f)
	{
		m_bSetCam = false;
	}

	if (vPosition.y > 0.6f)
	{
		m_STATE = SNIPERSUPPORT_DROP;
	}
	else if (m_bGetOrder)
	{
		if (!m_bOrdering)
		{
			CTerrainTex*	pTerrainBufferCom = dynamic_cast<CTerrainTex*>(Engine::Get_Component(STAGE_ENVIRONMENT, L"Terrain", L"Proto_TerrainTexCom", ID_STATIC));
			NULL_CHECK_RETURN(pTerrainBufferCom, 0);

			CTransform*		pTerrainTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(STAGE_ENVIRONMENT, L"Terrain", TRANSFORM_COMP, ID_DYNAMIC));
			NULL_CHECK_RETURN(pTerrainTransformCom, 0);

			_vec3 vPos;
			vPos = m_pCalculatorCom->Peek_Target_Vector(g_hWnd, &_vec3(0.f, 0.f, 0.f), pTerrainBufferCom, pTerrainTransformCom);
			_vec3 vSetPos = _vec3(vPos.x, vPos.y + 0.5f, vPos.z);

			m_vOrderPos = vSetPos;
			m_bGetOrder = true;
			m_bOrdering = true;
		}

		m_pTransform->Chase_Target(&m_vOrderPos, 5.f, fTimeDelta);

		_vec3 vPosition;
		m_pTransform->Get_Info(INFO_POS, &vPosition);

		if (fabs(m_vOrderPos.x - vPosition.x) < 1.f &&
			fabs(m_vOrderPos.y - vPosition.y) < 1.f &&
			fabs(m_vOrderPos.z - vPosition.z) < 1.f)
		{
			m_bGetOrder = false;
			m_bOrdering = false;
		}
		m_STATE = SNIPERSUPPORT_WALK;
	}
	else if (!m_pCollision->Sphere_Collision(this->m_pSphereTransCom, m_pPlayerTransCom, vPlayerScale.x, vScale.x) && (m_STATE != SNIPERSUPPORT_ATTACK))
	{
		m_pTransform->Chase_Target(&vPlayerPos, 5.f, fTimeDelta);
		m_STATE = SNIPERSUPPORT_WALK;
	}
	else // �ƹ� ���µ� �ƴϸ� �������ֱ�
	{
		m_pTransform->Chase_Target(&vPlayerPos, 0.f, fTimeDelta);
		m_STATE = SNIPERSUPPORT_IDLE;
	}
	// ���⼭ good

	if (vPosition.y <= 0.6f)
	{
		Find_Target();	//	�� �Ʒ��� �� ��, �ֺ� �� Ž���Ͽ� �����ϴ� �����
						//	Look_Direction ���� yaw�� �����Ų ����

		Look_Direction();
	}

	CSupporter::Update_Object(fTimeDelta);

	_vec3 vPos;
	m_pTransform->Get_Info(INFO_POS, &vPos);
	m_pHitBoxTransform->Set_Pos(vPos.x, vPos.y, vPos.z);
	m_pSphereTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);

	return 0;
}

void CSupporter_Sniper::LateUpdate_Object(void)
{
	if (!m_bFirst)
	{
		if (m_STATE == UZISUPPORTER_DROP)
		{
			DROP_Animation_Run();
			Run_Animation(10.f);
		}
		else if (m_STATE == SNIPERSUPPORT_IDLE)
		{
			IDLE_Animation_Run();
			Run_Animation(10.f);
		}
		else if (m_STATE == SNIPERSUPPORT_WALK)
		{
			WALK_Animation_Run();
			Run_Animation(5.f);
		}
		else if (m_STATE == SNIPERSUPPORT_ATTACK)
		{
			ATTACK_Animation_Run();
			if (m_ATTACK == SNIPERSUPPORT_ATTACK_1)
				Run_Animation(0.5f);
			else
				Run_Animation(20.f);
		}
	}

	CSupporter::LateUpdate_Object();
}

void CSupporter_Sniper::Render_Object(void)
{
	/*m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pHitBoxTransform->Get_WorldMatrixPointer());
	m_pHitBox->Render_Buffer();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pSphereTransCom->Get_WorldMatrixPointer());
	m_pSphereBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);*/
}

HRESULT CSupporter_Sniper::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTransform = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pHitBox = dynamic_cast<CHitBox*>(Clone_Proto(HITBOX_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ HITBOX_COMP, pComponent });

	pComponent = m_pHitBoxTransform = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"m_pHitBoxTransform", pComponent });

	pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Clone_Proto(CALCULATOR_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ CALCULATOR_COMP, pComponent });

	pComponent = m_pCollision = dynamic_cast<CCollision*>(Clone_Proto(COLLISION_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ COLLISION_COMP, pComponent });

	pComponent = m_pSphereBufferCom = dynamic_cast<CSphereTex*>(Clone_Proto(SPHERETEX_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ SPHERETEX_COMP, pComponent });

	pComponent = m_pSphereTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"m_pSphereTransCom", pComponent });

	return S_OK;
}

void CSupporter_Sniper::Look_Direction(void)
{
	_matrix matWorld;
	m_pTransform->Get_WorldMatrix(&matWorld);

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
			Transform->Set_Angle(&_vec3(yaw, 0.f, 0.f));
		}
	}
}

void CSupporter_Sniper::Find_Target(void)
{
	CLayer*	pMonsterLayer = Engine::Get_Layer(STAGE_MONSTER);

	_vec3 vGunPos_Left, vGunPos_Right;
	for (auto& iter : pMyLayer->Get_GamePair())
	{
		if (0 == _tcscmp(iter.first, L"SNIPER_3"))
		{
			_matrix matFinal;
			dynamic_cast<CTransAxisBox*>(iter.second)->Get_Final(&matFinal);
			vGunPos_Left = { matFinal.m[3][0], matFinal.m[3][1], matFinal.m[3][2] };
		}
	}

	_vec3 vScale;
	m_pSphereTransCom->Get_Scale(&vScale);

	for (auto& iter : pMonsterLayer->Get_GameList())
	{
		CTransform* pTransform = dynamic_cast<CTransform*>(iter->Get_Component(TRANSFORM_COMP, ID_DYNAMIC));

		_vec3 vMonsterScale;
		pTransform->Get_Scale(&vMonsterScale);
		_vec3 vMonsterPos;
		pTransform->Get_Info(INFO_POS, &vMonsterPos);

		if (m_pCollision->Sphere_Collision(this->m_pSphereTransCom, pTransform, vMonsterScale.x, vScale.x))
		{
			_vec3 vDir_Left = vMonsterPos - vGunPos_Left;
			D3DXVec3Normalize(&vDir_Left, &vDir_Left);

			m_pTransform->Chase_Target(&vMonsterPos, 0.f, m_fTimeDelta);
			m_STATE = SNIPERSUPPORT_ATTACK;

			if (m_AnimationTime >= 1.f)
			{
				CPoolMgr::GetInstance()->Reuse_PlayerBullet(m_pGraphicDev, &vGunPos_Left, &vDir_Left, 20.f, 20.f);
			}
		}
	}
}

HRESULT CSupporter_Sniper::Build(void)
{
	HANDLE      hFile = CreateFile(L"../../Data/Supporter_Sniper/PLAYER_SNIPER.dat",      // ������ ��ο� �̸�	
		GENERIC_READ,         // ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
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

		FAILED_CHECK_RETURN(pMyLayer->Add_GamePair(LoadOrder.front(), pGameObject), E_FAIL);	//	Map�� ���� �ʴ´�!!!!! Layer/��Ʈ ����

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
		m_pTransform->Get_Info(INFO_POS, &vPlayerPos);

		if (0 == _tcscmp(LoadOrder.front(), L"A_ROOT"))	//	��Ʈ �̸��� �׻� �����̹Ƿ� �̷��� �����ص�, ��Ʈ�� �������� ����ص� ���� ���� �۰� ���� �ٴ����� �ص� ����? �ٵ� �ű���� ���غý��ϴ٤�
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

	for (auto& iter : *(pMyLayer->Get_GamePairPtr()))		//	List ����
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

void CSupporter_Sniper::Load_Animation(wstring FileName, _uint AnimationID)
{
	HANDLE      hFile = CreateFile(FileName.c_str(),      // ������ ��ο� �̸�
		GENERIC_READ,         // ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
		NULL,               // ���� ���(������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�)    
		NULL,               // ���� �Ӽ�(NULL�� �����ϸ� �⺻�� ����)
		OPEN_EXISTING,         // CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING  : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��) : FILE_ATTRIBUTE_NORMAL : �ƹ��� �Ӽ��� ���� ����
		NULL);               // ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��ϱ� NULL)

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

void CSupporter_Sniper::Run_Animation(const _float & AnimationSpeed)
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
		m_pTransform->Get_Info(INFO_POS, &vPlayerPos);

		if (0 == _tcscmp(iter.first, L"A_ROOT"))
			BoxTransform->Set_Pos(vTransLerp.x + vPlayerPos.x, vTransLerp.y + vPlayerPos.y, vTransLerp.z + vPlayerPos.z);
		else
			BoxTransform->Set_Pos(vTransLerp.x, vTransLerp.y, vTransLerp.z);
	}
}

void CSupporter_Sniper::IDLE_Animation_Run(void)
{
	list<pair<const _tchar*, CGameObject*>> ListBox = *(pMyLayer->Get_GamePairPtr());

	if (m_AnimationTime >= 1.f)
	{
		for (auto& iter : ListBox)
		{
			CQuarternion* Qtan = dynamic_cast<CQuarternion*>(iter.second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));
			Qtan->Delete_WorldVector();
		}

		if (m_IDLE == SNIPERSUPPORT_IDLE_1)
			m_IDLE = SNIPERSUPPORT_IDLE_2;
		else if (m_IDLE == SNIPERSUPPORT_IDLE_2)
			m_IDLE = SNIPERSUPPORT_IDLE_1;

		m_AnimationTime = 0.f;
	}

	for (auto& iter : ListBox)	// �ִϸ��̼� ����
	{
		CQuarternion* Qtan = dynamic_cast<CQuarternion*>(iter.second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));
		if (m_IDLE == SNIPERSUPPORT_IDLE_1)
			Qtan->Change_Animation(0);
		else if (m_IDLE == SNIPERSUPPORT_IDLE_2)
			Qtan->Change_Animation(1);
	}
}

void CSupporter_Sniper::WALK_Animation_Run(void)
{
	list<pair<const _tchar*, CGameObject*>> ListBox = *(pMyLayer->Get_GamePairPtr());

	if (m_AnimationTime >= 1.f)
	{
		for (auto& iter : ListBox)
		{
			CQuarternion* Qtan = dynamic_cast<CQuarternion*>(iter.second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));
			Qtan->Delete_WorldVector();
		}

		if (m_WALK == SNIPERSUPPORT_WALK_1)
			m_WALK = SNIPERSUPPORT_WALK_2;
		else if (m_WALK == SNIPERSUPPORT_WALK_2)
			m_WALK = SNIPERSUPPORT_WALK_1;

		m_AnimationTime = 0.f;
	}

	for (auto& iter : ListBox)	// �ִϸ��̼� ����
	{
		CQuarternion* Qtan = dynamic_cast<CQuarternion*>(iter.second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));
		if (m_WALK == SNIPERSUPPORT_WALK_1)
			Qtan->Change_Animation(2);
		else if (m_WALK == SNIPERSUPPORT_WALK_2)
			Qtan->Change_Animation(3);
	}
}

void CSupporter_Sniper::ATTACK_Animation_Run(void)
{
	list<pair<const _tchar*, CGameObject*>> ListBox = *(pMyLayer->Get_GamePairPtr());

	if (m_AnimationTime >= 1.f)
	{
		for (auto& iter : ListBox)
		{
			CQuarternion* Qtan = dynamic_cast<CQuarternion*>(iter.second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));
			Qtan->Delete_WorldVector();
		}

		if (m_ATTACK == SNIPERSUPPORT_ATTACK_1)
			m_ATTACK = SNIPERSUPPORT_ATTACK_2;
		else if (m_ATTACK == SNIPERSUPPORT_ATTACK_2)
			m_ATTACK = SNIPERSUPPORT_ATTACK_1;

		m_AnimationTime = 0.f;
	}

	for (auto& iter : ListBox)	// �ִϸ��̼� ����
	{
		CQuarternion* Qtan = dynamic_cast<CQuarternion*>(iter.second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));
		if (m_ATTACK == SNIPERSUPPORT_ATTACK_1)
			Qtan->Change_Animation(4);
		else if (m_ATTACK == SNIPERSUPPORT_ATTACK_2)
			Qtan->Change_Animation(5);
	}
}

void CSupporter_Sniper::DROP_Animation_Run(void)
{
	list<pair<const _tchar*, CGameObject*>> ListBox = *(pMyLayer->Get_GamePairPtr());

	_vec3 vPosition;
	m_pTransform->Get_Info(INFO_POS, &vPosition);

	if (m_AnimationTime >= 1.f)
	{
		for (auto& iter : ListBox)
		{
			CQuarternion* Qtan = dynamic_cast<CQuarternion*>(iter.second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));
			Qtan->Delete_WorldVector();
		}

		if (vPosition.y >= 2.f)
			m_DROP = SPDROP_1;
		else
			m_DROP = SPDROP_2;

		m_AnimationTime = 0.f;
	}

	for (auto& iter : ListBox)	// �ִϸ��̼� ����
	{
		CQuarternion* Qtan = dynamic_cast<CQuarternion*>(iter.second->Get_Component(L"Proto_QuaternionCom", ID_STATIC));
		Qtan->Change_Animation(6 + m_DROP);

	}
}

CSupporter_Sniper * CSupporter_Sniper::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos, _tchar * Name)
{
	CSupporter_Sniper* pInstance = new CSupporter_Sniper(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(vPos, Name)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CSupporter_Sniper::Free(void)
{
	for (auto& iter : *(pMyLayer->Get_GamePairPtr()))
	{
		iter.second->Kill_Obj();
	}

	for (auto iter : m_TcharList)
	{
		Safe_Delete_Array(iter);
	}

	CSupporter::Free();
}
