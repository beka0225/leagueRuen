#include <windows.h>
#include "Direct3D.h"
#include "DirectInput.h"
#include "Core.h"


CDirect3D::CDirect3D(void)
{
	// ��ü�� ���� �� �� �������� ���� NULL�� �ʱ�ȭ
	m_pD3D9 = NULL;
	m_pDevice = NULL;
	m_pSprite = NULL;
}

CDirect3D::~CDirect3D(void)
{
}

HRESULT CDirect3D::Initialize( HWND hWnd, int Screen_width, int Screen_height, bool Windowed, bool mBox )
{
	// SDK�� ������ Ȯ���ϰ� Direct3D9 ��ü�� �����.
	if ( ( m_pD3D9 = Direct3DCreate9( D3D_SDK_VERSION ) ) == NULL )
	{
		if ( mBox == true )
		{
			MessageBox(hWnd, L"Direct3D Create Error!", L"Error!", MB_OK );
		}
		return E_FAIL;
	}

	////////////////////////////////////////////////////////
	// Parameter Seting 
	// Direct3D Device�� �Ӽ��� �����Ѵ�.
	////////////////////////////////////////////////////////
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof(d3dpp));

	d3dpp.BackBufferWidth = Screen_width;
	d3dpp.BackBufferHeight = Screen_height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = Windowed; // ȭ��
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; // ���� ����
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; // 

	//////////////////////////////////////////////////////////
	// Create IDirect3D Device9 Interface
	//////////////////////////////////////////////////////////
	HRESULT hr;

	hr = m_pD3D9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pDevice);
	if( FAILED( hr ) )
	{
		if ( mBox == true )
		{
			MessageBox( hWnd, L"Direct3D Create Device Error!", L"Error!", MB_OK );
		}
		return E_FAIL;
	}

	// D3DXSPRITE ��ü�� �����Ѵ�.
	if( FAILED( ::D3DXCreateSprite(m_pDevice, &m_pSprite) ) )
	{
		if ( mBox == true )
		{
			MessageBox( hWnd, L"Create Sprite Error!", L"Error!", MB_OK );
		}
		return E_FAIL;
	}

	m_pDevice->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, TRUE );
	m_pDevice->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, TRUE );

	return S_OK;
}

void CDirect3D::UnInitialize()
{
	if( m_pSprite != NULL )
	{
		m_pSprite->Release();
		m_pSprite = NULL;
	}

	if( m_pDevice != NULL )
	{
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	if( m_pD3D9 != NULL )
	{
		m_pD3D9->Release();
		m_pD3D9 = NULL;
	}
}

void CDirect3D::Render()
{
	if( NULL == m_pDevice) return;

	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_ARGB(255,255,255,255), 1.0f, 0);	// �ĸ� ���۸� �ش� �Ӽ����� �����.

	if( SUCCEEDED( m_pDevice->BeginScene() ) )
	{
		if( SUCCEEDED( m_pSprite->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK ) ) )
		{
			Core()->Render();
			//DirectInput()->MouseRender();
			// ��� �׸��� �ڵ�� �� ������ �;� �Ѵ�.
			//������ �ؽ��ĸ� ������ �ϴ°Ŵ� �ڼ��Ѱ��� �ϰ� �� �ʿ�� ���°� ����.
			m_pSprite->End();
		}
		m_pDevice->EndScene();
	}

	if ( FAILED(m_pDevice->Present(NULL, NULL, NULL, NULL)) )
	{
		if ( Core()->ResolutionChange( 1280, 720, true ) == true );
			//std::cout << "SUCCEED" << std::endl;
	}
}
