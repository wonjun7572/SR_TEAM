#include "..\Header\Collision.h"
#include "Export_Function.h"

USING(Engine)

CCollision::CCollision(LPDIRECT3DDEVICE9 pGraphicDev)
	:CComponent(pGraphicDev)
{
}

CCollision::CCollision(const CCollision & rhs)
	: CComponent(rhs)
{
}

CCollision::~CCollision()
{
}

HRESULT CCollision::Ready_Collision(void)
{
	return S_OK;
}

_bool CCollision::Check_Collision(void)
{
	m_pSrc = dynamic_cast<CHitBox*>(Get_Component(L"Layer_Character", L"PLAYER", L"Proto_HitboxCom", ID_STATIC));
	m_pDst = dynamic_cast<CHitBox*>(Get_Component(L"Layer_GameLogic", L"TestPlayer0", L"Proto_HitboxCom", ID_STATIC));

	CTransform*	pSrcTrans = dynamic_cast<CTransform*>(Get_Component(L"Layer_Character", L"PLAYER", L"Proto_TransformCom", ID_DYNAMIC));
	CTransform*	pDstTrans = dynamic_cast<CTransform*>(Get_Component(L"Layer_GameLogic", L"TestPlayer0", L"Proto_TransformCom", ID_DYNAMIC));

	m_pSrc->Get_MinMax(&m_vMin1, &m_vMax1);
	m_pDst->Get_MinMax(&m_vMin2, &m_vMax2);

	D3DXVec3TransformCoord(&m_vMin1, &m_vMin1, pSrcTrans->Get_WorldMatrixPointer());
	D3DXVec3TransformCoord(&m_vMax1, &m_vMax1, pSrcTrans->Get_WorldMatrixPointer());
	D3DXVec3TransformCoord(&m_vMin2, &m_vMin2, pDstTrans->Get_WorldMatrixPointer());
	D3DXVec3TransformCoord(&m_vMax2, &m_vMax2, pDstTrans->Get_WorldMatrixPointer());

	if (m_vMin1.x <= m_vMax2.x && m_vMax1.x >= m_vMin2.x &&
		m_vMin1.y <= m_vMax2.y && m_vMax1.y >= m_vMin2.y &&
		m_vMin1.z <= m_vMax2.z && m_vMax1.z >= m_vMin2.z)
	{
		cout << "AAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
		return true;
	}

	return false;
}

_int CCollision::Wall_Collision(_vec3* vNorm)
{
	CLayer* pLayer = Engine::Get_Layer(L"Layer_Wall");
	map<const _tchar*, CGameObject*> mapWall = pLayer->Get_GameObjectMap();

	CTransform*	pPlayerTransform = dynamic_cast<CTransform*>(Get_Component(L"Layer_Character", L"PLAYER", L"Proto_TransformCom", ID_DYNAMIC));
	CHitBox* pPlayerBox = dynamic_cast<CHitBox*>(Get_Component(L"Layer_Character", L"PLAYER", L"Proto_HitboxCom", ID_STATIC));

	CTransform* pPlayerBodyTransform = dynamic_cast<CTransform*>(Get_Component(L"Layer_Character", L"BODY", L"Proto_TransformCom", ID_DYNAMIC));

	_vec3 vPlayerPos;
	pPlayerTransform->Get_Info(INFO_POS, &vPlayerPos);

	for (auto iter : mapWall)
	{
		CTransform* pWallTransform = dynamic_cast<CTransform*>(iter.second->Get_Component(L"Proto_TransformCom", ID_DYNAMIC));
		NULL_CHECK_RETURN(pWallTransform, false);
		CHitBox* pWallBox = dynamic_cast<CHitBox*>(iter.second->Get_Component(L"Proto_HitboxCom", ID_STATIC));
		NULL_CHECK_RETURN(pWallBox, false);

		m_pSrc->Get_MinMax(&m_vMin1, &m_vMax1);
		m_pDst->Get_MinMax(&m_vMin2, &m_vMax2);

		D3DXVec3TransformCoord(&m_vMin1, &m_vMin1, pPlayerTransform->Get_WorldMatrixPointer());
		D3DXVec3TransformCoord(&m_vMax1, &m_vMax1, pPlayerTransform->Get_WorldMatrixPointer());
		D3DXVec3TransformCoord(&m_vMin2, &m_vMin2, pWallTransform->Get_WorldMatrixPointer());
		D3DXVec3TransformCoord(&m_vMax2, &m_vMax2, pWallTransform->Get_WorldMatrixPointer());

		if (m_vMin1.x <= m_vMax2.x && m_vMax1.x >= m_vMin2.x &&
			m_vMin1.y <= m_vMax2.y && m_vMax1.y >= m_vMin2.y &&
			m_vMin1.z <= m_vMax2.z && m_vMax1.z >= m_vMin2.z)
		{
			_vec3 vWallPos, vWallRight, vWallUp, vWallLook;
			pWallTransform->Get_Info(INFO_POS, &vWallPos);

			const _vec3*	pCubtVtx = pWallBox->Get_VtxPos();
			_vec3	vNormal(0,0,0);
			_ulong	dwVtxIdx[3]{};
			_float	fU, fV, fDist;

			if ((vPlayerPos.x > vWallPos.x) && (m_vMin1.z > m_vMin2.z) && (m_vMax1.z < m_vMax2.z))
			{
				// ���� ������ �浹
				dwVtxIdx[0] = 1;
				dwVtxIdx[1] = 5;
				dwVtxIdx[2] = 6;
				_vec3 vSrc = pCubtVtx[5] - pCubtVtx[6];
				_vec3 vDst = pCubtVtx[5] - pCubtVtx[1];
				D3DXVec3Cross(&vNormal, &vSrc, &vDst);
				D3DXVec3Normalize(&vNormal, &vNormal);

				memcpy(vNorm, vNormal, sizeof(_vec3));

				return WALL_RIGHT;
			}
			if ((vPlayerPos.x < vWallPos.x) && (m_vMin1.z > m_vMin2.z) && (m_vMax1.z < m_vMax2.z))
			{
				// ���� ������ �浹
				dwVtxIdx[0] = 4;
				dwVtxIdx[1] = 0;
				dwVtxIdx[2] = 3;
				_vec3 vSrc = pCubtVtx[3] - pCubtVtx[0];
				_vec3 vDst = pCubtVtx[4] - pCubtVtx[0];
				D3DXVec3Cross(&vNormal, &vSrc, &vDst);
				D3DXVec3Normalize(&vNormal, &vNormal);

				memcpy(vNorm, vNormal, sizeof(_vec3));

				return WALL_LEFT;
			}
			if ((vPlayerPos.z > vWallPos.z) && (m_vMin1.x > m_vMin2.x) && (m_vMax1.x < m_vMax2.x))
			{
				// ���� ������ �浹
				dwVtxIdx[0] = 7;
				dwVtxIdx[1] = 6;
				dwVtxIdx[2] = 5;
				_vec3 vSrc = pCubtVtx[6] - pCubtVtx[7];
				_vec3 vDst = pCubtVtx[6] - pCubtVtx[5];
				D3DXVec3Cross(&vNormal, &vSrc, &vDst);
				D3DXVec3Normalize(&vNormal, &vNormal);

				memcpy(vNorm, vNormal, sizeof(_vec3));

				return WALL_FRONT;
			}
			if ((vPlayerPos.z < vWallPos.z) && (m_vMin1.x > m_vMin2.x) && (m_vMax1.x < m_vMax2.x))
			{
				// ���� ������ �浹
				dwVtxIdx[0] = 0;
				dwVtxIdx[1] = 1;
				dwVtxIdx[2] = 2;
				_vec3 vSrc = pCubtVtx[1] - pCubtVtx[0];
				_vec3 vDst = pCubtVtx[2] - pCubtVtx[1];
				D3DXVec3Cross(&vNormal, &vSrc, &vDst);
				D3DXVec3Normalize(&vNormal, &vNormal);

				memcpy(vNorm, vNormal, sizeof(_vec3));

				return WALL_BACK;
			}
			return -1;
#pragma region

			//_vec3 vRayPos, vRayDir, vNormal;
			//pPlayerTransform->Get_Info(INFO_POS, &vRayPos);
			//vRayDir = *vDir;

			////cout << vRayPos.x << " " << vRayPos.y << " " << vRayPos.z << endl;

			//const _vec3*	pCubtVtx = pWallBox->Get_VtxPos();

			//_ulong	dwVtxIdx[3]{};
			//_float	fU, fV, fDist;
			//// +X

			//dwVtxIdx[0] = 1;
			//dwVtxIdx[1] = 5;
			//dwVtxIdx[2] = 6;
			//if (D3DXIntersectTri(&pCubtVtx[dwVtxIdx[1]],
			//	&pCubtVtx[dwVtxIdx[0]],
			//	&pCubtVtx[dwVtxIdx[2]],
			//	&vRayPos, &vRayDir,
			//	&fU, &fV, &fDist))
			//{
			//	_vec3 vSrc = pCubtVtx[5] - pCubtVtx[6];
			//	_vec3 vDst = pCubtVtx[5] - pCubtVtx[1];
			//	D3DXVec3Cross(&vNormal, &vSrc, &vDst);
			//	cout << "�� " << vNormal.x << " " << vNormal.y << " " << vNormal.z << endl;
			//}
			//dwVtxIdx[0] = 1;
			//dwVtxIdx[1] = 6;
			//dwVtxIdx[2] = 2;
			//if (D3DXIntersectTri(&pCubtVtx[dwVtxIdx[1]],
			//	&pCubtVtx[dwVtxIdx[0]],
			//	&pCubtVtx[dwVtxIdx[2]],
			//	&vRayPos, &vRayDir,
			//	&fU, &fV, &fDist))
			//{
			//	_vec3 vSrc = pCubtVtx[1] - pCubtVtx[2];
			//	_vec3 vDst = pCubtVtx[6] - pCubtVtx[2];
			//	D3DXVec3Cross(&vNormal, &vSrc, &vDst);
			//	cout << "�� " << vNormal.x << " " << vNormal.y << " " << vNormal.z << endl;
			//}
			//// ~+X

			//// -X
			//dwVtxIdx[0] = 4;
			//dwVtxIdx[1] = 0;
			//dwVtxIdx[2] = 3;
			//if (D3DXIntersectTri(&pCubtVtx[dwVtxIdx[1]],
			//	&pCubtVtx[dwVtxIdx[0]],
			//	&pCubtVtx[dwVtxIdx[2]],
			//	&vRayPos, &vRayDir,
			//	&fU, &fV, &fDist))
			//{
			//	_vec3 vSrc = pCubtVtx[3] - pCubtVtx[0];
			//	_vec3 vDst = pCubtVtx[4] - pCubtVtx[0];
			//	D3DXVec3Cross(&vNormal, &vSrc, &vDst);
			//	cout << "�� " << vNormal.x << " " << vNormal.y << " " << vNormal.z << endl;
			//}
			//dwVtxIdx[0] = 4;
			//dwVtxIdx[1] = 3;
			//dwVtxIdx[2] = 7;
			//if (D3DXIntersectTri(&pCubtVtx[dwVtxIdx[1]],
			//	&pCubtVtx[dwVtxIdx[0]],
			//	&pCubtVtx[dwVtxIdx[2]],
			//	&vRayPos, &vRayDir,
			//	&fU, &fV, &fDist))
			//{
			//	_vec3 vSrc = pCubtVtx[7] - pCubtVtx[4];
			//	_vec3 vDst = pCubtVtx[3] - pCubtVtx[7];
			//	D3DXVec3Cross(&vNormal, &vSrc, &vDst);
			//	cout << "�� " << vNormal.x << " " << vNormal.y << " " << vNormal.z << endl;
			//}
			//// ~-X

			//// Y
			//dwVtxIdx[0] = 4;
			//dwVtxIdx[1] = 5;
			//dwVtxIdx[2] = 1;

			//if (D3DXIntersectTri(&pCubtVtx[dwVtxIdx[1]],
			//	&pCubtVtx[dwVtxIdx[0]],
			//	&pCubtVtx[dwVtxIdx[2]],
			//	&vRayPos, &vRayDir,
			//	&fU, &fV, &fDist))
			//{
			//	_vec3 vSrc = pCubtVtx[5] - pCubtVtx[1];
			//	_vec3 vDst = pCubtVtx[5] - pCubtVtx[4];
			//	D3DXVec3Cross(&vNormal, &vSrc, &vDst);
			//	cout << vNormal.x << " " << vNormal.y << " " << vNormal.z << endl;
			//}

			//dwVtxIdx[0] = 4;
			//dwVtxIdx[1] = 1;
			//dwVtxIdx[2] = 0;

			//if (D3DXIntersectTri(&pCubtVtx[dwVtxIdx[1]],
			//	&pCubtVtx[dwVtxIdx[0]],
			//	&pCubtVtx[dwVtxIdx[2]],
			//	&vRayPos, &vRayDir,
			//	&fU, &fV, &fDist))
			//{
			//	_vec3 vSrc = pCubtVtx[4] - pCubtVtx[0];
			//	_vec3 vDst = pCubtVtx[1] - pCubtVtx[0];
			//	D3DXVec3Cross(&vNormal, &vSrc, &vDst);
			//	cout << vNormal.x << " " << vNormal.y << " " << vNormal.z << endl;
			//}
			//// ~ +Y

			//// ~ -Y
			//dwVtxIdx[0] = 3;
			//dwVtxIdx[1] = 2;
			//dwVtxIdx[2] = 6;
			//if (D3DXIntersectTri(&pCubtVtx[dwVtxIdx[1]],
			//	&pCubtVtx[dwVtxIdx[0]],
			//	&pCubtVtx[dwVtxIdx[2]],
			//	&vRayPos, &vRayDir,
			//	&fU, &fV, &fDist))
			//{
			//	_vec3 vSrc = pCubtVtx[6] - pCubtVtx[2];
			//	_vec3 vDst = pCubtVtx[3] - pCubtVtx[2];
			//	D3DXVec3Cross(&vNormal, &vSrc, &vDst);
			//	cout << vNormal.x << " " << vNormal.y << " " << vNormal.z << endl;
			//}

			//dwVtxIdx[0] = 3;
			//dwVtxIdx[1] = 6;
			//dwVtxIdx[2] = 7;
			//if (D3DXIntersectTri(&pCubtVtx[dwVtxIdx[1]],
			//	&pCubtVtx[dwVtxIdx[0]],
			//	&pCubtVtx[dwVtxIdx[2]],
			//	&vRayPos, &vRayDir,
			//	&fU, &fV, &fDist))
			//{
			//	_vec3 vSrc = pCubtVtx[7] - pCubtVtx[3];
			//	_vec3 vDst = pCubtVtx[7] - pCubtVtx[6];
			//	D3DXVec3Cross(&vNormal, &vSrc, &vDst);
			//	cout << vNormal.x << " " << vNormal.y << " " << vNormal.z << endl;
			//}
			//// ~ -Y

			//// Z+
			//dwVtxIdx[0] = 7;
			//dwVtxIdx[1] = 6;
			//dwVtxIdx[2] = 5;
			//if (D3DXIntersectTri(&pCubtVtx[dwVtxIdx[1]],
			//	&pCubtVtx[dwVtxIdx[0]],
			//	&pCubtVtx[dwVtxIdx[2]],
			//	&vRayPos, &vRayDir,
			//	&fU, &fV, &fDist))
			//{
			//	_vec3 vSrc = pCubtVtx[6] - pCubtVtx[7];
			//	_vec3 vDst = pCubtVtx[6] - pCubtVtx[5];
			//	D3DXVec3Cross(&vNormal, &vSrc, &vDst);
			//	cout << "�� " << vNormal.x << " " << vNormal.y << " " << vNormal.z << endl;
			//}

			//dwVtxIdx[0] = 7;
			//dwVtxIdx[1] = 5;
			//dwVtxIdx[2] = 4;
			//if (D3DXIntersectTri(&pCubtVtx[dwVtxIdx[1]],
			//	&pCubtVtx[dwVtxIdx[0]],
			//	&pCubtVtx[dwVtxIdx[2]],
			//	&vRayPos, &vRayDir,
			//	&fU, &fV, &fDist))
			//{
			//	_vec3 vSrc = pCubtVtx[5] - pCubtVtx[4];
			//	_vec3 vDst = pCubtVtx[4] - pCubtVtx[7];
			//	D3DXVec3Cross(&vNormal, &vSrc, &vDst);
			//	cout << "�� " << vNormal.x << " " << vNormal.y << " " << vNormal.z << endl;
			//}

			//// ~Z+

			//// Z-
			//dwVtxIdx[0] = 0;
			//dwVtxIdx[1] = 1;
			//dwVtxIdx[2] = 2;
			//if (D3DXIntersectTri(&pCubtVtx[dwVtxIdx[1]],
			//	&pCubtVtx[dwVtxIdx[0]],
			//	&pCubtVtx[dwVtxIdx[2]],
			//	&vRayPos, &vRayDir,
			//	&fU, &fV, &fDist))
			//{
			//	_vec3 vSrc = pCubtVtx[1] - pCubtVtx[0];
			//	_vec3 vDst = pCubtVtx[2] - pCubtVtx[1];
			//	D3DXVec3Cross(&vNormal, &vSrc, &vDst);
			//	cout << "�� " << vNormal.x << " " << vNormal.y << " " << vNormal.z << endl;
			//}

			//dwVtxIdx[0] = 0;
			//dwVtxIdx[1] = 2;
			//dwVtxIdx[2] = 3;
			//if (D3DXIntersectTri(&pCubtVtx[dwVtxIdx[1]],
			//	&pCubtVtx[dwVtxIdx[0]],
			//	&pCubtVtx[dwVtxIdx[2]],
			//	&vRayPos, &vRayDir,
			//	&fU, &fV, &fDist))
			//{
			//	_vec3 vSrc = pCubtVtx[2] - pCubtVtx[3];
			//	_vec3 vDst = pCubtVtx[3] - pCubtVtx[0];
			//	D3DXVec3Cross(&vNormal, &vSrc, &vDst);
			//	cout << "�� " << vNormal.x << " " << vNormal.y << " " << vNormal.z << endl;
			//}

			//D3DXVec3Normalize(&vNormal, &vNormal);
			//D3DXVec3Normalize(vDir, vDir);

			//cout << vNormal.x << " " << vNormal.y << " " << vNormal.z << endl;

			//*vDir = *vDir - ((D3DXVec3Dot(vDir, &vNormal)) * vNormal);
			//return true;

#pragma endregion
		}
	}

	return -1;
}

_int CCollision::Wall_Collision_By_DotSliding(_vec3 * vChangeDir)
{
	CLayer* pLayer = Engine::Get_Layer(L"Layer_Wall");
	map<const _tchar*, CGameObject*> mapWall = pLayer->Get_GameObjectMap();

	CTransform*	pPlayerTransform = dynamic_cast<CTransform*>(Get_Component(L"Layer_Character", L"PLAYER", L"Proto_TransformCom", ID_DYNAMIC));
	CHitBox* pPlayerBox = dynamic_cast<CHitBox*>(Get_Component(L"Layer_Character", L"PLAYER", L"Proto_HitboxCom", ID_STATIC));

	CTransform* pPlayerBodyTransform = dynamic_cast<CTransform*>(Get_Component(L"Layer_Character", L"BODY", L"Proto_TransformCom", ID_DYNAMIC));

	_vec3 vPlayerPos;
	pPlayerTransform->Get_Info(INFO_POS, &vPlayerPos);

	for (auto iter : mapWall)
	{
		CTransform* pWallTransform = dynamic_cast<CTransform*>(iter.second->Get_Component(L"Proto_TransformCom", ID_DYNAMIC));
		NULL_CHECK_RETURN(pWallTransform, false);
		CHitBox* pWallBox = dynamic_cast<CHitBox*>(iter.second->Get_Component(L"Proto_HitboxCom", ID_STATIC));
		NULL_CHECK_RETURN(pWallTransform, false);

		m_pSrc->Get_MinMax(&m_vMin1, &m_vMax1);
		m_pDst->Get_MinMax(&m_vMin2, &m_vMax2);

		D3DXVec3TransformCoord(&m_vMin1, &m_vMin1, pPlayerTransform->Get_WorldMatrixPointer());
		D3DXVec3TransformCoord(&m_vMax1, &m_vMax1, pPlayerTransform->Get_WorldMatrixPointer());
		D3DXVec3TransformCoord(&m_vMin2, &m_vMin2, pWallTransform->Get_WorldMatrixPointer());
		D3DXVec3TransformCoord(&m_vMax2, &m_vMax2, pWallTransform->Get_WorldMatrixPointer());

		if (m_vMin1.x <= m_vMax2.x && m_vMax1.x >= m_vMin2.x &&
			m_vMin1.y <= m_vMax2.y && m_vMax1.y >= m_vMin2.y &&
			m_vMin1.z <= m_vMax2.z && m_vMax1.z >= m_vMin2.z)
		{
			_vec3 vWallPos, vWallRight, vWallUp, vWallLook;
			pWallTransform->Get_Info(INFO_POS, &vWallPos);
			pWallTransform->Get_Info(INFO_RIGHT, &vWallRight);
			pWallTransform->Get_Info(INFO_UP, &vWallUp);
			pWallTransform->Get_Info(INFO_LOOK, &vWallLook);

			_vec3	vWallAxis, vPlayerDir, vSliding;

			if ((vPlayerPos.x > vWallPos.x) && (m_vMin1.z > m_vMin2.z) && (m_vMax1.z < m_vMax2.z))
			{
				// ���� ������ �浹
				// Dir�� Look �����Ͽ� ��Į�� ���ϰ�
				// z�̵����� +�̸� z+�������� ��Į�󰪸�ŭ �̵�, z�̵����� -�̸� z-�������� ��Į�󰪸�ŭ �̵�

				vWallAxis = vWallLook;
				vPlayerDir = *vChangeDir;

				D3DXVec3Normalize(&vWallAxis, &vWallAxis);
				
				_float fScalar = D3DXVec3Dot(&vPlayerDir, &vWallAxis);

				vSliding = vWallAxis * fScalar;

				*vChangeDir = vSliding;

				return WALL_RIGHT;
			}
			if ((vPlayerPos.x < vWallPos.x) && (m_vMin1.z > m_vMin2.z) && (m_vMax1.z < m_vMax2.z))
			{
				// ���� ������ �浹
				// Dir�� Look �����Ͽ� ��Į�� ���ϰ�
				// z�̵����� +�̸� z+�������� ��Į�󰪸�ŭ �̵�, z�̵����� -�̸� z-�������� ��Į�󰪸�ŭ �̵�

				vWallAxis = vWallLook;
				vPlayerDir = *vChangeDir;

				D3DXVec3Normalize(&vWallAxis, &vWallAxis);

				_float fScalar = D3DXVec3Dot(&vPlayerDir, &vWallAxis);

				vSliding = vWallAxis * fScalar;

				*vChangeDir = vSliding;

				return WALL_LEFT;
			}
			if ((vPlayerPos.z > vWallPos.z) && (m_vMin1.x > m_vMin2.x) && (m_vMax1.x < m_vMax2.x))
			{
				// ���� ������ �浹
				// Dir�� Right �����Ͽ� ��Į�� ���ϰ�
				// x�̵����� +�̸� x+�������� ��Į�󰪸�ŭ �̵�, x�̵����� -�̸� x-�������� ��Į�󰪸�ŭ �̵�

				vWallAxis = vWallRight;
				vPlayerDir = *vChangeDir;

				D3DXVec3Normalize(&vWallAxis, &vWallAxis);

				_float fScalar = D3DXVec3Dot(&vPlayerDir, &vWallAxis);

				vSliding = vWallAxis * fScalar;

				*vChangeDir = vSliding;

				cout << "��" << endl;

				return WALL_FRONT;
			}
			if ((vPlayerPos.z < vWallPos.z) && (m_vMin1.x > m_vMin2.x) && (m_vMax1.x < m_vMax2.x))
			{
				// ���� ������ �浹
				// Dir�� Right �����Ͽ� ��Į�� ���ϰ�
				// x�̵����� +�̸� x+�������� ��Į�󰪸�ŭ �̵�, x�̵����� -�̸� x-�������� ��Į�󰪸�ŭ �̵�

				vWallAxis = vWallRight;
				vPlayerDir = *vChangeDir;

				D3DXVec3Normalize(&vWallAxis, &vWallAxis);

				_float fScalar = D3DXVec3Dot(&vPlayerDir, &vWallAxis);

				vSliding = vWallAxis * fScalar;

				*vChangeDir = vSliding;

				cout << "��" << endl;

				return WALL_BACK;
			}
		}
	}

	return -1;
}

CCollision * CCollision::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCollision* pInstance = new CCollision(pGraphicDev);

	if (FAILED(pInstance->Ready_Collision()))
	{
		MSG_BOX("Collision Create Fail");
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CCollision::Clone(void)
{
	return new CCollision(*this);
}

void CCollision::Free(void)
{
	CComponent::Free();
}
