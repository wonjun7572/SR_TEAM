#include "..\..\Header\Shader.h"



CShader::CShader(LPDIRECT3DDEVICE9 pGraphicDev)
	:CComponent(pGraphicDev)
{
}

CShader::CShader(const CShader & rhs)
	:CComponent(rhs), m_pEffect(rhs.m_pEffect)
{
	m_pEffect->AddRef();
}

HRESULT CShader::Ready_Shader(const _tchar* ShaderFileName)
{
	D3DXCreateEffectFromFile(m_pGraphicDev, ShaderFileName, nullptr, nullptr, 0, nullptr, &m_pEffect, nullptr);
	NULL_CHECK_RETURN(m_pEffect, E_FAIL);

	return S_OK;
}

void CShader::Begin_Shader(void)
{
	m_pEffect->Begin(nullptr, 0);
}

void CShader::End_Shader(void)
{
	m_pEffect->End();
}

CShader * CShader::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* ShaderFileName)
{
	CShader* pInstance = new CShader(pGraphicDev);

	if (FAILED(pInstance->Ready_Shader(ShaderFileName)))
	{
		MSG_BOX("Shader Component Create Fail");
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CShader::Clone(void)
{
	return new CShader(*this);
}

void CShader::Free(void)
{
	Safe_Release(m_pEffect);
	CComponent::Free();
}
