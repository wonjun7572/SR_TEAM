#include "stdafx.h"
#include "..\Header\LetterBox.h"

static _int	iLetterBoxCnt = 0;

CLetterBox::CLetterBox(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}


CLetterBox::~CLetterBox()
{
}

HRESULT CLetterBox::Ready_Object(_tchar* tDialogue, _int iIndex)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Font(m_pGraphicDev, L"Letterbox2", L"Roboto-Bold", 15, 25, FW_EXTRABOLD), E_FAIL);
	m_strLetter2 = tDialogue;
	
	return S_OK;
}

_int CLetterBox::Update_Object(const _float & fTimeDelta)
{
	CGameObject::Update_Object(fTimeDelta);
	 Add_RenderGroup(RENDER_UI, this);

	return 0;
}

void CLetterBox::LateUpdate_Object(void)
{
	CGameObject::LateUpdate_Object();
}

void CLetterBox::Render_Object(void)
{

	//m_pGraphicDev->SetTransform(D3DTS_WORLD, m_TranformCom->Get_WorldMatrixPointer());
	Begin_OrthoProj();
	//m_pRcCom->Render_Buffer();
	_float fA = sizeof(m_strLetter2);
	Engine::Render_Font(L"Letterbox2", m_strLetter2.c_str(), &(_vec2(WINCX/4-fA*fA*0.15, WINCY/2)), D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	End_OrthoProj();
}

HRESULT CLetterBox::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pRcCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pRcCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pComponent });

	pComponent = m_pFontTexture = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_ButtonPlayTexture"));
	NULL_CHECK_RETURN(m_pFontTexture, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Layer_Mapping", pComponent });

	pComponent = m_TranformCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_TranformCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });
	return S_OK;
}

void CLetterBox::Begin_OrthoProj()
{
	_matrix matWorld, matView, matProj, matOrtho;
	m_pGraphicDev->GetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	memcpy(&m_matWorld, &matWorld, sizeof(_matrix));
	memcpy(&m_matView, &matView, sizeof(_matrix));
	memcpy(&m_matProj, &matProj, sizeof(_matrix));

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	matView.m[0][0] = 55.f; // 이미지 가로
	matView.m[1][1] = 55.f;   // 이미지 세로
	matView.m[2][2] = 1.f;
	matView.m[3][0] = m_TranformCom->m_vInfo[INFO_POS].x ;
	matView.m[3][1] = m_TranformCom->m_vInfo[INFO_POS].y ;
	

	D3DXMatrixOrthoLH(&matOrtho, WINCX, WINCY, 0.f, 1.f);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matOrtho);
}

void CLetterBox::End_OrthoProj()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

CLetterBox * CLetterBox::Create(LPDIRECT3DDEVICE9 pGraphicDev, _tchar* tDialogue, _int iIndex)
{
	CLetterBox* pInstance = new CLetterBox(pGraphicDev);

	if (FAILED(pInstance->Ready_Object(tDialogue, iIndex)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CLetterBox::Free(void)
{
	CGameObject::Free();

}

