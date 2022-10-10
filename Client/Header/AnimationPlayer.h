#pragma once
#include "GameObject.h"

/*

�ִϸ��̼��� �޴� ��� ������Ʈ�� ���� �⺻ ����
1. �̵�, �浹 �� ���� ���� ���� ������ HitBox�� �����Ѵ�.
2. �ִϸ��̼��� ��Ʈ�ڽ��� ����ٴϸ� �Է¹޴� Ű�� Ȥ�� Ʈ���ſ� ���� �ܼ� �ִϸ��̼Ǹ� �����ϵ��� �Ѵ�.
3. ���� �ִϸ��̼� �������� ���� ������ ���� �ִϸ��̼� �������� �ҷ����� ������� �������ε� �� �ִϸ��̼Ǹ��� �ҷ����� ��Ʈ���� �����
>> Ȥ�� �ش� ��Ŀ� ���� �� ���� �ذ���� ������ ��õ��...
4. �ִϸ��̼��� �ӵ��� Ŭ���̾�Ʈ���� ���� ����

*/

BEGIN(Engine)

class CHitBox;
class CTransform;
class CCalculator;
class CCollision;
class CCubeCol;

END

class CAnimationPlayer : public CGameObject
{
private:
	explicit CAnimationPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CAnimationPlayer();

public:
	virtual		HRESULT		Ready_Object(void);
	virtual		_int		Update_Object(const _float& fTimeDelta);
	virtual		void		LateUpdate_Object(void);
	virtual		void		Render_Object(void);

private:
	void					Key_Input(void);					//	Ű���� �Է�
	HRESULT					Build(void);						//	ó�� ���۽� �ҷ��� ��
	void					Look_Direction(void);

private:
	HRESULT					Add_Component(void);

	CHitBox*				m_pHitbox = nullptr;
	CTransform*				m_pTransform = nullptr;
	CCalculator*			m_pCalculator = nullptr;
	CCollision*				m_pCollision = nullptr;

	CCubeCol*				m_pCubeCol = nullptr;
	CTransform*				m_pRotationTrans = nullptr;

private:
	_vec3					vDir = { 0.f ,0.f ,0.f };
	_float					m_fTimeDelta = 0.f;					//	������Ʈ �̿��� ���������� �ð����� ����ϱ� ����
	_bool					m_bFirst = true;					//	�� �ҷ����⿡ ���� 1ȸ�� �����ϵ��� �ϱ� ����
	_float					m_AnimationTime = 0.f;				//	fTimeDelta�� ���������� �ִϸ��̼��� ������ ���� ����

	PLAYERSTATEID			m_STATE;
	PLAYERWALKID			m_WALK;
	PLAYERSTOPID			m_STOP;

private:
	void					Sync_Animation(PLAYERSTATEID eID);				//	�̰� ���� �Ⱦ��ϴ�
	void					Load_Animation(wstring FileName);				//	���� �ִϸ��̼� ���� ��ȯ �����̽��� �޾ƿ��� �Լ�
	void					Run_Animation(const _float& AnimationSpeed);	//	�ִϸ��̼� ����

private:
	void					Walk_Animation_Run(void);						//	���ҿ� ���� �߰� �Լ� ����
	void					Stop_Animation_Run(void);

private:
	list<char*>							m_CharList;				// char��������
	list<_tchar*>						m_TcharList;			// tchar��������

public:
	static CAnimationPlayer* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void	Free(void);
};

