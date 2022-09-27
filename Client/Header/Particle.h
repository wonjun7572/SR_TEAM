#pragma once
#include "Engine_Include.h"
#include "Export_Function.h"




USING(Engine)

class CParticle
{
public:
	CParticle();
	virtual ~CParticle();



	virtual bool Init(LPDIRECT3DDEVICE9* pGraphicDev, char* texFileName);
	virtual void Reset();
	virtual void ResetParticle(ATTIBUTE* attribute);
	virtual void AddParticle();
	virtual void Update(_float fTimeDelta) = 0;


	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

	_bool IsEmpty();
	_bool IsDead();
	
protected:
	virtual void RemoveDeadParticles();

protected:
	LPDIRECT3DDEVICE9*		m_pGraphicDev;
	_vec3					m_vOrigin;
	_float					m_fEmitRate;
	_float					m_fSize;
	LPDIRECT3DTEXTURE9*		m_pVertex;
	LPDIRECT3DVERTEXBUFFER9* m_pVertexBuffer;
	std::list<Attribute*>	m_Particle;
	_int					m_MaxParticles;

	DWORD					_vbSize;
	DWORD					_vbOffset;
	DWORD					_vbBatchSize;
	
};

