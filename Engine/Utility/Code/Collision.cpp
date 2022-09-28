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

_bool CCollision::Wall_Collision(void)
{
	CLayer* pLayer = Engine::Get_Layer(L"Layer_Wall");
	map<const _tchar*, CGameObject*> mapWall = pLayer->Get_GameObjectMap();

	CTransform*	pPlayerTransform = dynamic_cast<CTransform*>(Get_Component(L"Layer_Character", L"PLAYER", L"Proto_TransformCom", ID_DYNAMIC));
	CHitBox* pPlayerBox = dynamic_cast<CHitBox*>(Get_Component(L"Layer_Character", L"PLAYER", L"Proto_HitboxCom", ID_STATIC));

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
			cout << "Wall Collision" << endl;
			return true;
		}
	}

	return false;
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
