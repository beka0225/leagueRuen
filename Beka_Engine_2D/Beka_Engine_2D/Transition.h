#pragma once

class CTransition
{
public:
	CTransition(void);
	virtual ~CTransition(void);

	virtual void Initialize() = 0;
	virtual void UnInitialize() = 0;
	virtual void InitializeFill() = 0;
	virtual void InitializeUnFill() = 0;
	virtual void TransitionIn( short Speed, int& TransitionOption ) = 0; // ��ο��� ȭ�鿡�� ���� �������
	virtual void TransitionOut( short Speed, int& TransitionOption ) = 0; // ��Ҵ� ȭ�鿡�� ���� ��ο�����
	virtual void Render() = 0;
};

