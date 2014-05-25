#pragma once

#define V(p) { if( (p) == false ) { return false; } }

class CScene // ���� ����Ŭ������ ���� ���� ���� �ݵ�� �� Ŭ������ ����ؼ� ����� ��.
{
public:
	CScene(void);
	virtual ~CScene(void);

	virtual bool Initialize() = 0;
	virtual void UnInitialize() = 0;

	virtual bool TextureInitialize() = 0;
	virtual void TextureUnInitialize() = 0;

	virtual void PrepareInput() = 0;
	virtual void Process() = 0;
	virtual void Render() = 0;
};