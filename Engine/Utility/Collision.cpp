#include "..\Header\Collision.h"

USING(Engine)

CCollision::CCollision(LPDIRECT3DDEVICE9 pGraphicDev)
	:CComponent(pGraphicDev)
{
}

CCollision::CCollision(const CCollision & rhs)
	:CCollision(m_pGraphicDev)
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
	return _bool();
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
