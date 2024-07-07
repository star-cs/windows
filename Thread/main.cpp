#include <process.h>
#include <stdio.h>
#include <windows.h>

unsigned WINAPI fun(void* arg)
{
	int cnt = *((int*)arg);
	printf("id = %d��cnt = %d\n", GetCurrentThreadId(), cnt);
	return 0;
}

DWORD WINAPI fun2(LPVOID arg)
{
	int cnt = *((int*)arg);
	Sleep(10000);
	printf("���߳�id = %d��cnt = %d\n", GetCurrentThreadId(), cnt);
	return 0;
}

int Num = 0;
unsigned WINAPI threadInc(void* arg)
{
	int temp = Num;
	Sleep(1);
	temp++;
	Num = temp;
	printf("���߳�id = %d��Num = %d\n", GetCurrentThreadId(), temp);

	return 0;
}

int main()
{
	
	//_In_opt_  void* _Security,							
	//	_In_      unsigned                 _StackSize,		
	//	_In_      _beginthreadex_proc_type _StartAddress,	
	//	_In_opt_  void* _ArgList,							
	//	_In_      unsigned                 _InitFlag,
	//	_Out_opt_ unsigned* _ThrdAddr
	
	
#if 0
	int num = 100;
	int id;
	hThread = (HANDLE)_beginthreadex(NULL, 0, &fun, (void*)&num, 0, &id);
	//_beginthreadex(NULL, 0, &fun, (void*)&num, 0, &tid);
	//_beginthreadex(NULL, 0, &fun, (void*)&num, 0, &tid);

#elif 0
	int num = 100;
	HANDLE hThread;
	DWORD dwThreadID;
	int wr;
	hThread = CreateThread(NULL, 0, fun2, &num, 0, &dwThreadID);
	printf("���߳�id = %d��cnt = %d\n", GetCurrentThreadId(), num);

	if (wr = WaitForSingleObject(hThread, INFINITE) == WAIT_FAILED)	//�ȴ�ʱ�䣨���뵥λ��INFINITE�������ڵȴ���ֱ������״̬�ı䣻0���������Զ���״̬�����ȴ���
	{
		printf("thread wait error");
		return -1;
	}

	CloseHandle(hThread);

#elif 0
	/*WaitForMultipleObjects(
		_In_ DWORD nCount,								�������
		_In_reads_(nCount) CONST HANDLE * lpHandles,	�������
		_In_ BOOL bWaitAll,								TRUE�ȴ����е��ں˶���FALSE����һ���ں˶��󷢳��ź�
		_In_ DWORD dwMilliseconds						�ȴ�ʱ��
	);*/

	const int NUM_THREAD = 100;
	HANDLE tHandles[NUM_THREAD];
	int i;
	for (int i = 0; i < NUM_THREAD; i++)
	{
		tHandles[i] = (HANDLE)_beginthreadex(NULL, 0, threadInc, NULL, 0, NULL);
	}

	WaitForMultipleObjects(NUM_THREAD, tHandles, TRUE, INFINITE);

#elif 0
	/*CreateMutexW(
		_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,	��ȫ����
		_In_ BOOL bInitialOwner,							������������ߣ�TRUE����ӵ�л�����
		_In_opt_ LPCWSTR lpName								ָ�򻥳��������ָ������
	);*/

	/*CreateMutex();
	WaitForSingleObject();
	ReleaseMutex();*/

#else
	//�¼�����
	CreateEvent();


#endif


	Sleep(5000);		//���뵥λ
	system("pause");
	return 0;
}