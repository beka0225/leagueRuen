#pragma once

#include "Tile.h"
#include "Texture.h"
#include "Core.h"
#include <cstdlib>
#include "ValuesHeader.h"

class RunTileManager
{
public:
	RunTileManager(void);
	~RunTileManager(void);

	void Init(LPWSTR _path);
	void Uninit();

	void Render();
	void Process();

	int GetHowlongfall(){return howlongfall;}
	int GetWidth(){return _width;}
	int GetHeight(){return _height;}
	void SectorSwap();
	void SectorReset();
	D3DXVECTOR3 GetFallPosition();
	D3DXVECTOR3 GetHurdlePosition();

private:
	CTile* sector2[15];
	CTile* sector1[15];
	CTile* fall[3];
	CTile* Hurdle;

	CTexture* m_HuddleTex[3];
	CTexture* m_fallTex;
	CTexture* m_tileTex;
	
	int h_type;
	int howlongfall;

	bool ishurdle;
	bool isfallused;
	int _width;
	int _height;
	int i;
};

