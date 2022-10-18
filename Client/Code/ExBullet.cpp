#include "stdafx.h"
#include "..\Header\ExBullet.h"
#include "PoolMgr.h"
#include "Explosion.h"

CExBullet::CExBullet(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CExBullet::~CExBullet()
{
}

HRESULT CExBullet::Ready_Object(const _vec3 * pPos, const _vec3 * pDir, _float _fSpeed)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransCom->Set_Scale(0.1f, 0.1f, 1.f);
	m_pTransCom->m_vInfo[INFO_POS] = *pPos;
	m_pTransCom->Static_Update();

	m_pHitboxTransCom->Set_Scale(0.1f, 0.1f, 0.1f);
	m_pHitboxTransCom->m_vInfo[INFO_POS] = *pPos;
	m_pHitboxTransCom->Static_Update();

	m_vDirection = *pDir;
	m_fSpeed = _fSpeed;

	return S_OK;
}

_int CExBullet::Update_Object(const _float & fTimeDelta)
{
	if (m_bDead)
	{
		_vec3 vPos;
		m_pTransCom->Get_Info(INFO_POS, &vPos);

		_tchar* szName = new _tchar[256]{};
		wstring wName = L"Explosion_%d";

		wsprintfW(szName, wName.c_str(), g_iExplosion);
		m_TcharList.push_back(szName);

		g_iExplosion++;

		// À§Ä¡ ¹Ù²ãÁà¾ßÇÔ
		CGameObject* pGameObject = CExplosion::Create(m_pGraphicDev, _vec3(vPos.x, vPos.y, vPos.z), szName);
		NULL_CHECK_RETURN(pGameObject, -1);
		CLayer* pLayer = Get_Layer(STAGE_SKILL);
		FAILED_CHECK_RETURN(pLayer->Add_GameList(pGameObject), -1);

		CPoolMgr::GetInstance()->Collect_ExBullet(this);
		return -1;
	}

	m_fTimeDelta += fTimeDelta;

	CGameObject::Update_Object(fTimeDelta);

	m_pTransCom->Move_Pos(&(m_vDirection * fTimeDelta * m_fSpeed));

	_vec3 vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);
	m_pHitboxTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);

	m_pTransCom->Chase_Target_By_Direction(&m_vDirection, 0.f, fTimeDelta);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return 0;
}

void CExBullet::LateUpdate_Object(void)
{
	Collision_check();

	CGameObject::LateUpdate_Object();
}

void CExBullet::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pCubeCol->Render_Buffer();

	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pHitboxTransCom->Get_WorldMatrixPointer());
	//m_pHitbox->Render_Buffer();
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void CExBullet::Set_Pos(const _vec3 & vPos)
{
	m_pTransCom->Set_Pos(vPos.x, vPos.y, vPos.z);
}

void CExBullet::Collision_check(void)
{
	CLayer* pLayer = Engine::Get_Layer(STAGE_WALL);
	map<const _tchar*, CGameObject*> mapWall = pLayer->Get_GameObjectMap();

	for (auto& iter : mapWall)
	{
		CTransform* pWallTransform = dynamic_cast<CTransform*>(iter.second->Get_Component(TRANSFORM_COMP, ID_DYNAMIC));
		NULL_CHECK_RETURN(pWallTransform, );
		CHitBox* pWallBox = dynamic_cast<CHitBox*>(iter.second->Get_Component(HITBOX_COMP, ID_STATIC));
		NULL_CHECK_RETURN(pWallBox, );

		if (m_pCollision->Collision_Square(this->m_pTransCom, this->m_pHitbox, pWallTransform, pWallBox))
		{
			m_bDead = true;
			return;
		}
	}

	_vec3 vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);

	if (vPos.y <= 0.f)
	{
		m_bDead = true;
	}

}

HRESULT CExBullet::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ TRANSFORM_COMP, pComponent });

	pComponent = m_pCubeCol = dynamic_cast<CCubeCol*>(Clone_Proto(CUBECOL_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ CUBECOL_COMP, pComponent });

	pComponent = m_pHitboxTransCom = dynamic_cast<CTransform*>(Clone_Proto(TRANSFORM_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"HitboxTransCom", pComponent });

	pComponent = m_pHitbox = dynamic_cast<CHitBox*>(Clone_Proto(HITBOX_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ HITBOX_COMP, pComponent });

	pComponent = m_pCollision = dynamic_cast<CCollision*>(Engine::Clone_Proto(COLLISION_COMP));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ COLLISION_COMP, pComponent });

	return S_OK;
}

CExBullet * CExBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 * pPos, const _vec3 * pDir, _float _fSpeed)
{
	CExBullet* pInstance = new CExBullet(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(pPos, pDir, _fSpeed)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CExBullet::Free(void)
{
	for (auto iter : m_TcharList)
	{
		Safe_Delete_Array(iter);
	}

	CGameObject::Free();
}