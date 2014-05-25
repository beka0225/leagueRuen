#pragma once

#include "Direct3D.h"
#include <vector>

typedef struct _ITexture
{
	LPDIRECT3DTEXTURE9 _Texture;
	D3DXIMAGE_INFO _imageifo;
}ITexture, *LPITexture;
// �� ����ü���� �ؽ��Ŀ� �̹����� ũ�Ⱑ ����ִ�.

class CTexture
{
public:
	CTexture(void);
	~CTexture(void);
	bool LoadTexture();
	bool LoadTexture( LPITexture );
	bool LoadTexture( LPWSTR filename ); // �ؽ��ĸ� �߰���, . �׸��� GetTexture()�� �ؽ��ĸ� ���Ѵ�.
	LPITexture& GetTexture(){ return m_Texture;} // �ؽ��� ����, �Ű������� �߰��� ������
	void ReleaseTexture(); 
private:
	LPITexture m_Texture;
};

