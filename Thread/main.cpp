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
	Sleep(10000);
	printf("子线程id = %d，cnt = %d\n", GetCurrentThreadId(), cnt);
	return 0;
}

int Num = 0;
unsigned WINAPI threadInc(void* arg)
{
	int temp = Num;
	Sleep(1);
	temp++;
	Num = temp;
	printf("子线程id = %d，Num = %d\n", GetCurrentThreadId(), temp);

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
	printf("主线程id = %d，cnt = %d\n", GetCurrentThreadId(), num);

	if (wr = WaitForSingleObject(hThread, INFINITE) == WAIT_FAILED)	//等待时间（毫秒单位）INFINITE：无限期等待，直到对象状态改变；0：立即测试对象状态而不等待。
	{
		printf("thread wait error");
		return -1;
	}

	CloseHandle(hThread);

#elif 0
	/*WaitForMultipleObjects(
		_In_ DWORD nCount,								句柄个数
		_In_reads_(nCount) CONST HANDLE * lpHandles,	句柄的组
		_In_ BOOL bWaitAll,								TRUE等待所有的内核对象，FALSE任意一个内核对象发出信号
		_In_ DWORD dwMilliseconds						等待时间
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
		_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,	安全属性
		_In_ BOOL bInitialOwner,							互斥对象所有者，TRUE立即拥有互斥体
		_In_opt_ LPCWSTR lpName								指向互斥对象名的指针名称
	);*/

	/*CreateMutex();
	WaitForSingleObject();
	ReleaseMutex();*/

#else
	//事件对象
	CreateEvent();


#endif


	Sleep(5000);		//毫秒单位
	system("pause");
	return 0;
}