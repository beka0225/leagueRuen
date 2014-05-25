#pragma once

#include "UIObject.h"
#include "Transition.h"

class CFade : public CTransition // �Ϲ����� ���̵�ȿ��
{
public:
	CFade(void);
	~CFade(void);

	void Initialize();
	void UnInitialize();

	void InitializeFill();  // ȭ���� ���� �ؽ��ĸ� CFade�������� ȭ���� ������ ��ġ��
	void InitializeUnFill(); // ȭ���� ���� �ؽ��ĸ� CFade�������� ȭ���� ������ ��ġ��
	void TransitionIn( short Speed, int& TransitionOption ); // ���� �Ⱥ��� ������
	void TransitionOut( short Speed, int& TransitionOption ); // ���� ����������

	void Render(); // CFade ���̵�ȿ���� ȭ�鿡 ����. (���̵� ȿ���� ����� �� ������ Render�κп� �߰��ؾ���)

private:
	CUIObject* FadeTex; // ���̵�ȿ�� �ؽ���

	short t1;
	DWORD dwTimeStart1;

	short t2;
	DWORD dwTimeStart2;
};