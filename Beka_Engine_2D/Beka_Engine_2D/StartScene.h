#pragma once

#include "Scene.h"
#include "Core.h"
#include "FileIO.h"
#include "ValuesHeader.h"
#include "UIObject.h"
#include "BackGround.h"
#include "CameraManager.h"
#include "RunTileManager.h"
#include "Player.h"

class CStartScene : public CScene
{
public:
	CStartScene(void); // �� Ŭ������ ��� �ؽ��Ĺ� ������� �ʱ�ȭ
	~CStartScene(void); // �� Ŭ������ ��� ��������� �Ҵ�����

	bool Initialize(); // �ؽ��� ����
	void UnInitialize(); // �� ������ �Ҵ��� ��� ���� �޸𸮿��� ����

	bool TextureInitialize();
	void TextureUnInitialize();

	void PrepareInput(); // �Է��� �޴� �κ�
	void Process(); // ����� �ϴºκ�
	void Render(); // ȭ�鿡 �׸��� �κ� (��� �׸��� �ڵ�� �̰��� �;���)

private:
	DWORD m_CurrentCursor; // ���� ����Ű�� �ִ� ��ġ
	RunTileManager* m_tileManager;
	bool m_Click; // Ŭ�� �ߴ���

	float m_fStartTime;
	float m_fElapsedTime;

	CBackGround* BG1;
	CBackGround* BG2;

	CPlayer* m_player;

	CFileIO temp;
};