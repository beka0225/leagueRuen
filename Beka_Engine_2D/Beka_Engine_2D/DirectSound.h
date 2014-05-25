#pragma once

#include <Windows.h>
#include <vector>
#include <mmsystem.h>
#include <dsound.h>
#include "Singleton.h"

#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"winmm.lib")

class CDirectSound : public CSingleton<CDirectSound>
{
public:
	CDirectSound(void);
	~CDirectSound(void);

	
	
	HRESULT Initialize();
	void UnInitialize();
	void UnInitialize( int val );

	HRESULT Load_WaveFile( LPWSTR File_name ); // wav������ �ҷ��´�.
	void Set_Volume( LONG lVolume = 100 ); // �������� �⺻�� 100
	void Set_PlusVolume( LONG lVolume ); // �������� �⺻�� 100
	void Original_Set_Volume( LONG lVolume = -10000);
	void Play_Sound(); // ���
	void Play_Sound( int fileindex, bool bloop = false ); // ���������� �����ϰ� �ִ� ���Ϳ��� fileindex�� ���� ��ġ�� �ִ� ������ ���, �ݺ���� �Ұ�����
	void Stop_Sound(); // ����
	void Stop_Sound( int fileindex ); // ���������� �����ϰ� �ִ� ���Ϳ��� fileindex�� ���� ��ġ�� �ִ� ������ ����
	inline int GetVolume() { return m_Volume; }

private:
	int m_Volume;
	LPDIRECTSOUND							m_lpDirectSound; // DirectSound ��ü
	std::vector< LPDIRECTSOUNDBUFFER >		m_SoundRepository; // ���������� �����ϴ� ����
};

#define DirectSound() CSingleton<CDirectSound>::InstancePtr()