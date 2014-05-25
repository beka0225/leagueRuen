#include "Core.h"

#include "Direct3D.h"
#include "DirectInput.h"
#include "DirectSound.h"

#include "SceneManager.h"

#include "SceneHeader.h"
#include "TransitionManager.h"
#include "CameraManager.h"
#include "TileManager.h"
//#include "User.h"
//#include "StageManager.h"

CCore::CCore(void)
{
	m_hWnd		= NULL;

	m_dwFPS_Frames = 0;
	m_fFPS_LastTime = 0;
	m_FPS_Time = 0;

	m_fElapsedTime = 0;
	m_iFPS_Num = 0;

	m_Tick = 0;
	m_TickFix = 0;
	m_TickVal = Play;
}


CCore::~CCore(void)
{
}

bool CCore::Initialize( HWND hWnd, int Screen_width, int Screen_height, bool Windowed )
{
	srand( (unsigned)time(NULL) );
	m_hWnd = hWnd;
	m_ScreenWidth = Screen_width;
	m_ScreenHeight = Screen_height;

	// Direct3D ��ü �ʱ�ȭ
	if( FAILED( Direct3D()->Initialize( hWnd, Screen_width, Screen_height, Windowed ) ) )
	{
		return false;
	}

	// DirectInput �ʱ�ȭ
	if( FAILED( DirectInput()->InitInputDevice( hWnd ) ) )
	{
		MessageBox( hWnd, L"Input Device Error!", L"Error!", MB_OK );
		return false;
	}

	// DirectSound �ʱ�ȭ
	if( FAILED( DirectSound()->Initialize() ) )
	{
		MessageBox(hWnd, L"Direct Sound Device Error!", L"Error!", MB_OK );
		return false;
	}
	
	DirectInput()->TextureInitialize();
	DirectInput()->Initialize();

	// SceneManager�� ���� ���ʿ� �ε� �� ���� �ѱ��.
	TileManager()->init();
	Camera()->SetCamera();
	SceneManager()->ChangeScene( new CStartScene() );
	
	return true;
}

void CCore::UnInitialize()
{
	// ���� ��� ��ü�� ����.
	SceneManager()->DeleteScene();
	DirectInput()->UnInitialize();

	DirectInput()->ReleaseInputDevice();
	Direct3D()->UnInitialize();
	TransitionManager()->UnInitialize();

	//Destroy all Instance
	// ���Ǿ��� ��� ��ü�� ����.
	SceneManager()->DestroyInstance();

	DirectInput()->DestroyInstance();
	Direct3D()->DestroyInstance();

	TransitionManager()->DestroyInstance();

	TileManager()->uninit();
	TileManager()->DestroyInstance();
	Camera()->DestroyInstance();
	//User()->DestroyInstance();
}

bool CCore::ResolutionChange( int Screen_width, int Screen_height, bool Windowed )
{
	Core()->SetTickState(Stop);
	
	Direct3D()->UnInitialize();

	// Direct3D ��ü �ʱ�ȭ
	while ( FAILED( Direct3D()->Initialize( m_hWnd, Screen_width, Screen_height, Windowed, false ) ) )
	{
	//	std::cout << "Direct3D Initialize Retry..." << std::endl;
	}

	TransitionManager()->ReInitialize();
	SceneManager()->TextureUnInitialize();
	SceneManager()->TextureInitialize();


	Core()->SetTickState(Play);

	return true;
}

void CCore::PrepareInput()
{
	if ( TransitionManager()->GetTransitionOption() == 0 ) {
		SceneManager()->PrepareInput();
	}
}

void CCore::Process()
{
	this->FramePerSecond(); // ������ ���
	this->TickProcess();

	if ( TransitionManager()->GetTransitionOption() == 1 )
		TransitionManager()->SetTransition(1);
	else if ( TransitionManager()->GetTransitionOption() == 2 )
		TransitionManager()->SetTransition(2);

	TileManager()->Process();
	SceneManager()->Process();
	DirectInput()->MouseProcess();
	DirectInput()->CopyInputMemory(); // ��ǲ ������Ʈ, ���� ���� ����.
}

void CCore::Render()
{
	
	TransitionManager()->Render();
	SceneManager()->Render();
	TileManager()->Render();
	DirectInput()->MouseRender();	
}

void CCore::SetTickState( int val )
{
	if ( val == Stop )
	{
		m_TickFix = 0;
	}
	m_TickVal = val; 
}

void CCore::TickProcess()
{
	if ( m_TickVal == Stop )
	{
		m_TickFix = GetTickCount() - m_Tick;
	}
}

DWORD CCore::MyGetTickCount()
{
	m_Tick = GetTickCount() - m_TickFix;
	return m_Tick;
}

// �������� ��� �� �ִ� �Լ�
void CCore::FramePerSecond()
{
	if( m_dwFPS_Frames == 0 ) m_fFPS_LastTime = static_cast<float>( timeGetTime()/1000.f );

	m_fElapsedTime = static_cast<float>(timeGetTime()/1000.0f) - m_FPS_Time;
	m_FPS_Time = static_cast<float>( timeGetTime() / 1000.f );

	if( m_FPS_Time - m_fFPS_LastTime < 1.0f )
	{
		++m_dwFPS_Frames;
		//cout<<m_dwFPS_Frames<<endl;
	}
	else
	{
		m_iFPS_Num = static_cast<int>( m_dwFPS_Frames / ( m_FPS_Time - m_fFPS_LastTime ) );
		m_dwFPS_Frames = 0;
		m_fFPS_LastTime = m_FPS_Time;

		TCHAR Message[255];
		swprintf( Message, L"Now Frames : %f", m_fElapsedTime );
		SetWindowText( m_hWnd, Message );
	} 
}