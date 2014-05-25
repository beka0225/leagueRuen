#pragma once

#include "Transition.h"
#include "Singleton.h"
#include "Fade.h"
#include "FadeLeft.h"
#include "FadeRight.h"

namespace TransitionOption // ȭ�� ��ȯ�� �� �ɼ� ( ����, �����Ⱥ��̰�, �������̰�)
{
	// Off : ����
	// In :: ���� ���̰�
	// Out :: ���� �Ⱥ��̰�
	enum { Off, In, Out };
}

namespace TransitionType // ȭ���� � ������� ��ȯ�� ������
{
	// Empty : ����
	// Fade : �Ϲ����� ���̵�
	// FadeLeft : ���ʿ��� ���������� ���� �������� ���̵� ȿ�� (��ο������� �� �ݴ�)
	// FadeRight : �����ʿ��� �������� ���� �������� ���̵� ȿ�� (��ο������� �� �ݴ�)
	enum { Empty, Fade, FadeLeft, FadeRight };
}

class CTransitionManager : public CSingleton<CTransitionManager> // ȭ����ȯȿ�� (�� ȿ���� ����ҽ�  �ش� ���� Render()�κп� �� Ŭ������ Render()�Լ��� �߰� �ؾ���)
{
public:
	CTransitionManager(void);
	~CTransitionManager(void);

	void UnInitialize();

	void SetTransition( int TransitionOptionNum, short Speed = 7 ); //  ȭ����ȯ ȿ��
	inline int GetTransitionOption() { return m_TransitionOptionNum; } // ȭ����ȯȿ��

	inline long GetTransitionType() // ���� ȭ����ȯ Ÿ���� ����
	{ return m_CurrentTransitionType; }

	void TransitionChange( long TransitionType ); // ȭ����ȯ ȿ���� �Է¹��� ȿ���� �ٲ�

	void ReInitialize();

	void InitializeFill(); // ���� ȭ����ȯ ȿ�������� �ؽ��ĸ� ȭ���� ������ ��ġ��
	void InitializeUnFill(); // ���� ȭ����ȯ ȿ�������� �ؽ��ĸ� ȭ���� ������ ��ġ��

	void TransitionIn( short Speed ); // ���� ȭ����ȯ ȿ���� ���� �Ⱥ��̰�
	void TransitionOut( short Speed ); // ���� ȭ����ȯ ȿ���� ���� ���̰�

	void Render(); // ���� ( ȭ����ȯ ȿ���� ����Ϸ��� ������ �ش� �����ִ� Render()�Լ��� �߰��ؾ��� )

private:
	CTransition* m_CurrentTransition; // ���� ȭ����ȯ ȿ���� Ŭ����
	long m_CurrentTransitionType; // ���� ������ ȭ����ȯ ȿ��
	int m_TransitionOptionNum;
};

#define TransitionManager() CSingleton<CTransitionManager>::InstancePtr() // ȭ����ȯ ȿ�� �̱���
