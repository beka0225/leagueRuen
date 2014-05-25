#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include "Singleton.h"

typedef struct _Size
{
	int Width;
	int Height;
} Size;

class CDirect3D : public CSingleton<CDirect3D>
{
public:
	CDirect3D(void);
	~CDirect3D(void);

	// Direct3D9, Direct3DDevice, D3DXSPRITE ��ü�� �����ϰ� �ʱ�ȭ�Ѵ�.
	HRESULT		Initialize( HWND hWnd, int Screen_width, int Screen_height, bool Windowed, bool mBox = true );

	// Direct3D9, Direct3DDevice, D3DXSPRITE ��ü�� �����Ѵ�.
	void		UnInitialize();

	void		Render(); // �׸���

	inline LPDIRECT3D9			GetD3D9()		{ return m_pD3D9; }
	inline LPDIRECT3DDEVICE9	GetD3D9Device() { return m_pDevice; }
	inline LPDIRECT3DDEVICE9*	GetLPD3D9Device() { return &m_pDevice; }
	inline LPD3DXSPRITE			GetD3D9Sprite()	{ return m_pSprite; }

private :
	LPDIRECT3D9				m_pD3D9;
	LPDIRECT3DDEVICE9		m_pDevice;
	LPD3DXSPRITE			m_pSprite;
};

#define Direct3D() CSingleton<CDirect3D>::InstancePtr()
