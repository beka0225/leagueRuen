#pragma once
// This class only used for the Running game
#include "UIObject.h"
#include "Core.h"
enum{ RUN, JUMP, DOUBLEJUMP, BESHOT , FALL , HIGHFALL     };

class CPlayer
{
public:
	CPlayer(void);
	~CPlayer(void);

	void Init(int charactertype );
	void Uninit();
	void Render();
	void Process();
	void Jump();
	void JumpStart();

	int GetWidth(){return _width;}
	int GetHeight(){return _height;}
	
	void SetState(int val);
	void SetStartPosition(int y){ startpos = y; }
	void SetPositon(float x , float y);
	D3DXVECTOR3* GetPosition() { return &m_position; }
private:
	CUIObject* m_Run; // ÇãÂS
//	CUIObject* m_Jump;
//	CUIObject* m_DJump;
//	CUIObject* m_Beshot;
//	CUIObject* m_Fall;
//	CUIObject* m_HFall;	
	
	CUIObject** m_Current;
	
	float acc;
	bool isfall;
	bool isDjump;
	bool isJump;
	int m_State;
	int _width;
	int _height;
	float startpos;
	D3DXVECTOR3 m_position;
};

