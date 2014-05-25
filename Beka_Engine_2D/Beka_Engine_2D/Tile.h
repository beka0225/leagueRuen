#pragma once

#include "UIObject.h"
#include "Cameramanager.h"
#include "Core.h"

//Ÿ�� Ÿ�� ����ϱ�
namespace TILE_TYPE
{
	enum
	{
		ON , BLOCK , LEFTUP , RIGHTIP, MOVED, // ����Ʈ /  ����Ʈ�� �ݴ�
	};
}

class CTile
{
public:
	CTile(void);
	~CTile(void);

	void init(LPCWSTR filename , float G_x , float G_y ,float zbuffer ,int type  );
	void init(LPITexture &iTex , float G_x , float G_y ,float zbuffer ,int type );
	void Render();
	void Process();
	
	void SetTex(LPITexture &iTex);
	void ConstMove(float x , float y);
	void SetConstPosition(float x , float y);
	void TileMove(float x , float y);
	int Getwidth(){return width;}
	int Getheigth(){return heigth;}
	int GetTileType(){ return Floortype; }
	LPITexture GetTex(){ return *m_iTexture; }
	D3DXVECTOR3 GetCurPos(){return m_Position;}		
	D3DXVECTOR3 GetConstPosition() { return m_constPosition; }

private:
	LPITexture*	m_iTexture; // for the memory
	D3DXMATRIX			m_matWorld;
	RECT				m_SrcRect;
	D3DXVECTOR3			m_Position;
	D3DXVECTOR3			m_constPosition;

	int width;
	int heigth;
	
	int Floortype;

};


