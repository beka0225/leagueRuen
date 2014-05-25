#pragma once
#include <vector>
#include "Tile.h"
#include "Singleton.h"

typedef struct TINFO
{
	D3DXVECTOR3 Pos;
	int width;
	int height;
}TINFO;

class CTileManager : public CSingleton<CTileManager>
{
public:
	CTileManager(void);
	~CTileManager(void);

	void init();
	void uninit();
	void TexInit(LPCWSTR filename);

	TINFO StartPos();
	TINFO GetTilePos(int num); 
	int stuffEnd(){ return m_TileStuff.size(); }

	void AddTexture();// Ÿ���� �߰��ϰ� ���� �� deafault�϶��� �⺻ Ÿ�Ϸ�
	void AddTile(int type , float G_x ,float G_y , float zbuffer );
	void AllTileErase();

	void Process();
	void Render();
	
private:
	std::vector<CTile*> m_TileStuff;
	std::vector<CTile*>::iterator tileiter;
	
	std::vector<ITexture*> m_TexStuff;        // Ÿ���� �������̱� ������
	std::vector<ITexture*>::iterator texiter;

	TINFO check;
};

#define TileManager() CSingleton<CTileManager>::InstancePtr()
