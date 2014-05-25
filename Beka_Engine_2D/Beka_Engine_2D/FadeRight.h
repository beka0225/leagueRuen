#pragma once

#include "UIObject.h"
#include "Transition.h"

class CFadeRight : public CTransition // �����ʿ��� �������� ���� �������� ���̵� ȿ�� (��ο������� �� �ݴ�)
{
public:
	CFadeRight(void);
	~CFadeRight(void);

	void Initialize();
	void UnInitialize();

	void InitializeFill(); // ȭ���� ���� �ؽ��ĸ� CFadeRight�������� ȭ���� ������ ��ġ��
	void InitializeUnFill(); // ȭ���� ���� �ؽ��ĸ� CFadeRight�������� ȭ���� ������ ��ġ��
	void TransitionIn( short Speed, int& TransitionOption ); // ���� ���̵���
	void TransitionOut( short Speed, int& TransitionOption ); // ���� �Ⱥ��̵���

	void Render(); // CFadeRight ���̵�ȿ���� ȭ�鿡 ����. (���̵� ȿ���� ����� �� ������ Render�κп� �߰��ؾ���)

private:
	CUIObject* m_FadeTex; // ���̵�ȿ�� �ؽ��� (�簢��)
	CUIObject* m_FadeTex2; // ���̵�ȿ�� �ؽ��� (�׶���Ʈ)

	float PosX1;
	float PosX2;
};

#define FadeRight() CSingleton<CFadeRight>::InstancePtr() // CFadeRight �̱���

