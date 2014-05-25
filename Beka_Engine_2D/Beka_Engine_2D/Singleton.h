#ifndef Singleton
#define Singleton

template <typename T> class CSingleton
{
public:
	// �Լ��� ó�� ȣ�� �� ���� ���� �����Ҵ��� �Ͽ� �Ҵ�� ��ü�� ��ȯ�ϸ�
	// �ι� ° ���ʹ� �̹� �Ҵ�Ǿ� �ִ� �޸��� �ּҸ� ��ȯ�Ѵ�.
	static T* InstancePtr()
	{
		if( m_Instance == 0 )
		{
			m_Instance = new T;
		}
		return m_Instance;
	}

	// �޸𸮸� �����ϰ� �����͸� NULL�� �ʱ�ȭ�Ѵ�.
	static void DestroyInstance()
	{
		if( m_Instance != 0 )
		{
			delete m_Instance;
			m_Instance = 0;
		}
	}

private:
	static T* m_Instance;
};

// m_Instance ������ NULL�� �ʱ�ȭ �� �ֱ� ���� �ڵ�
template <typename T> T* CSingleton<T>::m_Instance = 0;

#endif