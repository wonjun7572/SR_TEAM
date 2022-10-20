#ifndef Engine_Struct_h__
#define Engine_Struct_h__

namespace Engine
{
	typedef	struct tagVertexColor
	{
		_vec3		vPos;
		_ulong		dwColor;

	}VTXCOL;

	const _ulong	FVF_COL = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;

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
		_vec3		vNormal;
	}VTXCUBE;

	const _ulong	FVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0) | D3DFVF_NORMAL ;		// D3DFVF_TEXCOORDSIZE3 : �ؽ�ó�� UV���� FLOAT �� 3���� ũ�⸸ŭ�̸�, ��ȣ���� ���� 0�� �ǹ̴� ���� ���ؽ��� �ؽ�ó UV ���� �������� �� �� �ִµ� ���� 0��° ���� ���� �����ϰڴٴ� �ǹ��̴�.

	typedef struct tagVertexCubeTex2
	{
		_vec3		vPos;
		_vec2		vTexUV;

	}VTXCUBE2;

	const _ulong	FVF_CUBE2 = D3DFVF_XYZ | D3DFVF_TEX1;

	typedef struct tagParticle 
	{
		_vec3	vPos;
		_ulong	dwColor;
	}PARTICLE;

	const _ulong	FVF_PARTICLE = D3DFVF_XYZ | D3DFVF_DIFFUSE;

	typedef	struct tagAttribute
	{
		_vec3  vPos;
		_vec3  vVelocity;
		_vec3  vAcceleration;
		_float fLifeTime;
		_float fAge;
		_ulong dwColor;
		_ulong dwColorFade;
		_bool  bAlive;
	}ATTRIBUTE;

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
		_float		fHp;				// ü���� ����
		_float		fMaxHp;
		_float		fDefence;				// ������ ����
		_float		fMaxDefence;
		_int		iGunTexture;			// �� UI ������ ����
	}ABILITY;

	typedef struct tagGunAbility
	{
		_float		fBulletAttack;
		_float		fBulletRate;	  // �Ѿ� �ӵ�
		_float		fRemainBulletCnt; // ���� �Ѿ� ���� 
		_float		fBulletCount;	  // �Ѿ� ���� ���ѿ�
		_bool		bShoot;
	}GUNABILITY;

	typedef struct tagMonsterState
	{
		std::wstring strObjTag;	// UI ���� ���� �̸� ã���ַ���
		_int   iLevel;
		_float fCurrentHp;
		_float fMaxHp;
		_float fDamage;
	}MONSTERABILITY;
	
	typedef struct tagMiddeMonster
	{
		std::wstring strObjTag;
		_float fCurrentHp;
		_float fMaxHp;
		_float fDamage;
	}MIDDLEBOSSABILITY;


	typedef struct tagKraken
	{
		std::wstring strObjTag;
		_float fCurrentHp;
		_float fMaxHp;
		_float fDamage;

	}KRAKENABILITY;


	typedef struct tagTerret
	{
		std::wstring strObjTag;
		_float fCurrentHp;
		_float fMaxHp;
		_float fDamage;
	}TERRETABILITY;
}


#endif // Engine_Struct_h__
