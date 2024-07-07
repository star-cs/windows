#include <process.h>
#include <stdio.h>
#include <windows.h>

unsigned WINAPI fun(void* arg)
{
	int cnt = *((int*)arg);
	printf("id = %d，cnt = %d\n", GetCurrentThreadId(), cnt);
	return 0;
}

DWORD WINAPI fun2(LPVOID arg)
{
	int cnt = *((int*)arg);
	printf("子线程id = %d，cnt = %d\n", GetCurrentThreadId(), cnt);
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
	unsigned int tid;
	int num = 3;
#if 0
	_beginthreadex(NULL, 0, &fun, (void*)&num, 0, &tid);
	_beginthreadex(NULL, 0, &fun, (void*)&num, 0, &tid);
	_beginthreadex(NULL, 0, &fun, (void*)&num, 0, &tid);
#else 
	HANDLE hThread;
	DWORD dwThreadID;
	hThread = CreateThread(NULL, 0, fun2, &num, 0, &dwThreadID);
	printf("主线程id = %d，cnt = %d\n", GetCurrentThreadId(), num);
	CloseHandle(hThread);
#endif

	Sleep(5000);		//毫秒单位
	system("pause");
	return 0;
}