#pragma once

#include "UIObject.h"
#include "Transition.h"

class CFadeLeft : public CTransition // ���ʿ��� ���������� ���� �������� ���̵� ȿ�� (��ο������� �� �ݴ�)
{
public:
	CFadeLeft(void);
	~CFadeLeft(void);

	void Initialize();
	void UnInitialize();

	void InitializeFill(); // ȭ���� ���� �ؽ��ĸ� CFadeLeft�������� ȭ���� ������ ��ġ��
	void InitializeUnFill(); // ȭ���� ���� �ؽ��ĸ� CFadeLeft�������� ȭ���� ������ ��ġ��
	void TransitionIn( short Speed, int& TransitionOption ); // ���� ���̵���
	void TransitionOut( short Speed, int& TransitionOption ); // ���� �Ⱥ��̵���

	void Render(); // CFadeLeft ���̵�ȿ���� ȭ�鿡 ����. (���̵� ȿ���� ����� �� ������ Render�κп� �߰��ؾ���)

private:
	CUIObject* FadeTex; // ���̵�ȿ�� �ؽ��� (�簢��)
	CUIObject* FadeTex2; // ���̵�ȿ�� �ؽ���(�׶���Ʈ)

	float PosX1;
	float PosX2;
};

#define FadeLeft() CSingleton<CFadeLeft>::InstancePtr() // CFadeLeft �̱���

