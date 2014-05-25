#pragma once

#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "Singleton.h"

using namespace std;

enum
{
	Play, Stop
};


// ������ �߾Ӱ����� ���� ����
// ������ �ʱ�ȭ, ����, �׸���, ó�� ���� ���� �����Ѵ�.
// �̱���ȭ �Ǿ��ֱ� ������ Core.h�� �߰��ϸ� ��𼭵� ���� �����ϴ�.

class CCore : public CSingleton<CCore>
{
public:
	CCore(void);
	~CCore(void);

	bool			Initialize( HWND hWnd, int Screen_width, int Screen_height, bool Windowed ); // �������ڵ�, â�� ũ��, â������� ��üȭ�������� �޾Ƽ� �ش� �����쿡 ���̷�Ʈx �� �ʱ�ȭ
	void			UnInitialize(); // ��� ����

	bool			ResolutionChange ( int Screen_width, int Screen_height, bool Windowed );

	void			PrepareInput(); // Ű���� ���콺 ���� ����� �Է� ó��
	void			Process(); // �ǵ����̸� ��� ó���� �̰���
	void			Render(); // ��� (��� �׸��� �ڵ�� �̰���)

	inline HWND		GetMainHWND() { return m_hWnd; } // ���� �������� �ڵ��� ��ȯ.
	inline int		GetScreenWidth() { return m_ScreenWidth; } // ���� ������ ȭ���� ���̸� ��ȯ
	inline int		GetScreenHeight() { return m_ScreenHeight; } // ���� ������ ȭ���� ���̸� ��ȯ.

	DWORD			MyGetTickCount();
	void			SetTickState( int val );
	void			TickProcess();

	void			FramePerSecond(); // ������ ��� �Լ�
	float			GetElapsedTime() { return m_fElapsedTime; } // �� �������� ����ϱ� ������ ����ð��� ��ȯ�ϴ� �Լ�

	int Random( int Start, int End ) { return (rand()%End+Start+1)-Start;  }
private:
	HWND	m_hWnd; // ���� �������� �ڵ�

	int		m_ScreenWidth; // â�� ũ�� x
	int		m_ScreenHeight; // â�� ũ�� y
	
	// �������� ��꿡 ���Ǵ� ������
	DWORD	m_dwFPS_Frames;
	float	m_fFPS_LastTime;
	float	m_FPS_Time;

	float	m_fElapsedTime;
	int		m_iFPS_Num;

	int		m_TransitionOption; // ȭ�� ��ȯ�� ����

	DWORD	m_Tick;
	DWORD	m_TickFix;
	int		m_TickVal;

};

#define Core() CSingleton<CCore>::InstancePtr()
