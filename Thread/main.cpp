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

int main()
{
	
	//_In_opt_  void* _Security,
	//	_In_      unsigned                 _StackSize,
	//	_In_      _beginthreadex_proc_type _StartAddress,
	//	_In_opt_  void* _ArgList,
	//	_In_      unsigned                 _InitFlag,
	//	_Out_opt_ unsigned* _ThrdAddr
	int num = 100;
	
#if 0
	int id;
	hThread = (HANDLE)_beginthreadex(NULL, 0, &fun, (void*)&num, 0, &id);
	//_beginthreadex(NULL, 0, &fun, (void*)&num, 0, &tid);
	//_beginthreadex(NULL, 0, &fun, (void*)&num, 0, &tid);
#else 
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
#endif

	

	Sleep(5000);		//���뵥λ
	system("pause");
	return 0;
}