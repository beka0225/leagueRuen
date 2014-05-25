#include <io.h>  
#include <fcntl.h>  
#include <stdio.h>  
#include <iostream> 
#include <iomanip>

#include "Core.h"

#include "Direct3D.h"
#include "DirectInput.h"

#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)

#if defined(DEBUG) || defined(_DEBUG)
BOOL DEBUGMODE = TRUE;
#else
BOOL DEBUGMODE = FALSE;
#endif

extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow();

LRESULT CALLBACK MsgProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam );


// ������ �۾������� ����� �����ϴ� �ɺ��� ���.
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;


/////////////////////////////////////////////////////////////
// �ܼ�â ũ��� ��ġ
void __fastcall ConsoleResize(int x, int y, int px, int py)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO stCSBI;

	COORD stLCWS = GetLargestConsoleWindowSize(hStdOut);
	GetConsoleScreenBufferInfo(hStdOut, &stCSBI);

	_SMALL_RECT stSR;
	stSR.Top    = 0;
	stSR.Left   = 0;
	stSR.Right  = (short)x - 1;
	stSR.Bottom = (short)y - 1;

	stLCWS.X = (short)x;
	stLCWS.Y = (short)y;

	HWND hStdOutWnd = GetConsoleWindow();
	MoveWindow(hStdOutWnd, px, py, 0, 0, true);

	if(stCSBI.dwSize.X > x && stCSBI.dwSize.Y > y) {
		SetConsoleWindowInfo(hStdOut, TRUE, &stSR);
		SetConsoleScreenBufferSize(hStdOut, stLCWS);
	} else {
		SetConsoleScreenBufferSize(hStdOut, stLCWS);
		SetConsoleWindowInfo(hStdOut, TRUE, &stSR);
	}
}
///////////////////////////////////////////////////////////////////////////


INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR, INT )
{
	////////////////////////////////// Memory Leak Check
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF  );

	// Check Number
	if ( DEBUGMODE == TRUE )
	{
		//_CrtSetBreakAlloc( 1691 );
		//_CrtSetBreakAlloc( 141 );
		//_CrtSetBreakAlloc( 135 );
	}
	////////////////////////////////////////////////


	WNDCLASSEX wc = { sizeof( WNDCLASSEX ), CS_HREDRAW | CS_VREDRAW, MsgProc, 0L, 0L, hInstance, 
		LoadIcon( NULL, IDI_APPLICATION ), LoadCursor(NULL, IDC_ARROW ), NULL, NULL, L"Game Name", NULL };

	RegisterClassEx( &wc );

	
	// â�� �߾ӿ� �����ϱ� ���� �ڵ�
	RECT rt = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRect( &rt, WS_OVERLAPPEDWINDOW, true );
	int Wx = (GetSystemMetrics(SM_CXSCREEN) - (rt.right-rt.left)) ;
	int Wy = (GetSystemMetrics(SM_CYSCREEN) - (rt.bottom-rt.top))-40 ;



	HWND hWnd = CreateWindow( wc.lpszClassName, wc.lpszClassName, WS_OVERLAPPED | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU , 0, 0, 
		rt.right - rt.left, rt.bottom - rt.top, NULL, NULL, hInstance, NULL );

	///////////////////////////////////////////////////�ܼ�â
	
	AllocConsole();
	ConsoleResize( 100, 50, 0, 0 );
	int hCrtout = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE),_O_TEXT);  
	FILE *hout = _fdopen(hCrtout,"w");  
	*stdout = *hout;    
	int hCrtin = _open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE),_O_TEXT);  
	FILE *hin = _fdopen(hCrtin,"r");  
	*stdin = *hin;  
	setvbuf( stdin, NULL, _IONBF, 0 );
	 
	///////////////////////////////////////////////////�ܼ�â
	
	ShowWindow( hWnd, SW_SHOWDEFAULT );
	UpdateWindow( hWnd );

	SetCursor(NULL);

	// Initialize anything.
	// ��� �ʱ�ȭ�� �� ������ �̷������.
	if( ( Core()->Initialize( hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, true ) ) == false )
	{
		Core()->UnInitialize();
		
		DestroyWindow(hWnd);

		return -1;
	}

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));


	// PeekMessage�� ����ؼ� �޽����� ���� ��� ó���ϰ� �޽����� ���� �Ⱓ ���ȿ���
	// �ؿ��ִ� else ������ ���鼭 ���ӿ� �ʿ��� ó���� �Ѵ�.
	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0L, 0L, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			DirectInput()->KeyboardUpdate();
			DirectInput()->MouseUpdate();
			Core()->PrepareInput();
			Core()->Process();
			Direct3D()->Render();
			
			
		}
	}
	// ���η����� ����Ǹ� ���ӿ� ���̴� �޸𸮳� ���ҽ� ���� �����Ѵ�.
	//_fcloseall();
	Core()->UnInitialize();
	
	return 0;

}

LRESULT CALLBACK MsgProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam )
{
	switch( iMessage )
	{
	case WM_DESTROY:
		Core()->UnInitialize();
		PostQuitMessage( 0 );
		return 0;
	}

	return DefWindowProc( hWnd, iMessage, wParam, lParam );
}