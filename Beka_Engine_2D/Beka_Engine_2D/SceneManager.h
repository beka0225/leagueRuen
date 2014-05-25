#pragma once

#include "Scene.h"
#include "Singleton.h"

// ���� ���� ���� ������ �ִ� Ŭ����. �̱���ȭ �Ǿ��ִ�.
// m_CurrentScene ������ ���� ���� �� ���� �ش� ���� ������Ʈ, �Է�ó��, �׸��⸦ �Ѵ�.

class CSceneManager : public CSingleton<CSceneManager> // ���� �����ϴ� Ŭ����
{
public:
	CSceneManager(void);
	~CSceneManager(void);

	void TextureInitialize();
	void TextureUnInitialize();

	void ChangeScene( CScene* scene ); // ȭ�鿡 ������ Ŭ������ ��ü��
	void DeleteScene(); // ���� ���õ����ִ¾� ����
	void PrepareInput(); // �Է�
	void Process();// ���
	void Render(); // ���� (��� �׸��� �Լ��� �̰����� �;���)
	CScene* GetCurrentScene() { return m_CurrentScene; }

private:
	CScene* m_CurrentScene; // �����
};

#define SceneManager() CSingleton<CSceneManager>::InstancePtr() // ���� �����ϴ� Ŭ���� (�̱���)