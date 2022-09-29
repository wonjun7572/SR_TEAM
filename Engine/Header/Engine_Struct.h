#ifndef Engine_Struct_h__
#define Engine_Struct_h__

namespace Engine
{
	typedef	struct tagVertexColor
	{
		_vec3		vPos;
		_ulong		dwColor;

	}VTXCOL;

	const _ulong		FVF_COL = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;


	typedef struct tagVertexTex
	{
		_vec3		vPos;
		_vec3		vNormal;
		_vec2		vTexUV;

	}VTXTEX;

	const _ulong		FVF_TEX = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

	typedef struct tagVertexCubeTex
	{
		_vec3		vPos;
		_vec3		vTexUV;

	}VTXCUBE;

	const _ulong		FVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);		// D3DFVF_TEXCOORDSIZE3 : �ؽ�ó�� UV���� FLOAT �� 3���� ũ�⸸ŭ�̸�, ��ȣ���� ���� 0�� �ǹ̴� ���� ���ؽ��� �ؽ�ó UV ���� �������� �� �� �ִµ� ���� 0��° ���� ���� �����ϰڴٴ� �ǹ��̴�.


	typedef	struct tagIndex16
	{
		_ushort			_0;
		_ushort			_1;
		_ushort			_2;

	}INDEX16;

	typedef	struct tagIndex32
	{
		_ulong		_0;
		_ulong		_1;
		_ulong		_2;

	}INDEX32;

	typedef struct tagAbility
	{
		_int		iHp;			// ü���� ����
		_int		iDefence;		// ������ ����
		_int		iGun;			// �� UI ������ ����
	}ABILITY;

	typedef struct tagGunAbility
	{
		_float		fBulletRate;	  // �Ѿ� �ӵ�
		_float		fRemainBulletCnt; // ���� �Ѿ� ���� 
		_float		fBulletCount;	  // �Ѿ� ���� ���ѿ�
	}GUNABILITY;

	typedef struct tagMonsterState
	{
		_int iLevel;
		_float fCurrentHp;
		_float fMaxHp;
		_float fDamage;
	}MONSTERABILITY;

	//typedef struct tagParticle
	//{
	//	_vec3		Position;
	//	D3DCOLOR	Color;
	//	_float		Size;
	//	static const DWORD FVF_PARTICLE;
	//}PARTICLE;
	//const DWORD PARTICLE::FVF_PARTICLE = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE;

	//typedef	struct tagAttribute
	//{
	//	_vec3 Position;
	//	_vec3 Velocity;
	//	_vec3 Acceleration;
	//	_float lifeTime;
	//	_float Age;
	//	D3DXCOLOR	Color;
	//	D3DXCOLOR	ColorFade;
	//	_bool		isAlive;
	//}ATTRIBUTE;
}


#endif // Engine_Struct_h__
