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

int test01()
{
	//_In_opt_  void* _Security,							
	//	_In_      unsigned                 _StackSize,		
	//	_In_      _beginthreadex_proc_type _StartAddress,	
	//	_In_opt_  void* _ArgList,							
	//	_In_      unsigned                 _InitFlag,
	//	_Out_opt_ unsigned* _ThrdAddr

	int num = 100;
	unsigned int id;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &fun, (void*)&num, 0, &id);
	//_beginthreadex(NULL, 0, &fun, (void*)&num, 0, &tid);
	//_beginthreadex(NULL, 0, &fun, (void*)&num, 0, &tid);
	return 0;
}

int test02() 
{
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
	return 0;
}

int test03()
{
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
	return 0;
}

int test04()
{
	/*CreateMutexW(
		_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,	安全属性
		_In_ BOOL bInitialOwner,							互斥对象所有者，TRUE立即拥有互斥体
		_In_opt_ LPCWSTR lpName								指向互斥对象名的指针名称
	);*/

	/*CreateMutex();
	WaitForSingleObject();
	ReleaseMutex();*/
	return 0;
}


int num = 100;
HANDLE hEvent;
unsigned WINAPI SellTicketA(void* arg)
{
	while (1)
	{
		WaitForSingleObject(hEvent, INFINITE);
		if (num > 0)
		{
			Sleep(10);
			num--;
			printf("A remain %d\n", num);
		}
		else
			break;
		SetEvent(hEvent);
	}
	return 0;
}

unsigned WINAPI SellTicketB(void* arg)
{
	while (1)
	{
		WaitForSingleObject(hEvent, INFINITE);
		if (num > 0)
		{
			Sleep(10);
			num--;
			printf("B remain %d\n", num);
		}
		else
			break;
		SetEvent(hEvent);
	}
	return 0;
}

int test05()
{
	HANDLE hThread1, hThread2;

	hThread1 = (HANDLE)_beginthreadex(NULL, 0, SellTicketA, NULL, 0, NULL);
	hThread2 = (HANDLE)_beginthreadex(NULL, 0, SellTicketB, NULL, 0, NULL);

	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	SetEvent(hEvent);

	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);

	ResetEvent(hEvent);

	CloseHandle(hEvent);

	return 0;
}


DWORD WINAPI ThreadProc(LPVOID arg)
{
	printf("I am comming ... ");
	while(1){}
	return 0;
}

int test06()
{
	HANDLE hThread;
	HANDLE headle2;
	DWORD threadId;

	hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, &threadId);
	CloseHandle(hThread);	
	headle2 = OpenThread(THREAD_QUERY_INFORMATION, FALSE, threadId);	//通过threadId返回句柄
	headle2 = OpenThread(THREAD_QUERY_INFORMATION, FALSE, threadId);
	headle2 = OpenThread(THREAD_QUERY_INFORMATION, FALSE, threadId);

	return 0;
}


#include <semaphore>

static HANDLE semOne;
static HANDLE semTwo;

unsigned WINAPI Read(void* arg)
{
	for (int i = 0; i < 5; i++)
	{
		WaitForSingleObject(semOne, INFINITE);
		printf("Read\n");
		ReleaseSemaphore(semTwo, 1, NULL);
	}
	return NULL;
}

unsigned WINAPI Accu(void* arg)
{
	for (int i = 0; i < 5; i++)
	{
		WaitForSingleObject(semTwo, INFINITE);
		printf("Accu\n");
		ReleaseSemaphore(semOne, 1, NULL);
	}
	return NULL;
}

void test07()
{
	HANDLE hThread1 = nullptr, hThread2 = nullptr;
	semOne = CreateSemaphore(NULL, 0, 2, NULL);
	semTwo = CreateSemaphore(NULL, 2, 2, NULL);

	hThread1 = (HANDLE)_beginthreadex(NULL, 0, Read, NULL, 0, NULL);
	hThread1 = (HANDLE)_beginthreadex(NULL, 0, Accu, NULL, 0, NULL);
	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);

	CloseHandle(semOne);
	CloseHandle(semTwo);

	system("pause");
}


int tot = 100;
CRITICAL_SECTION g_cs;

DWORD WINAPI SellA(void* arg)
{
	while (1)
	{
		EnterCriticalSection(&g_cs);
		if (tot > 0)
		{
			Sleep(1);
			tot--;
			printf("A reamain %d\n", tot);
			LeaveCriticalSection(&g_cs);
		}
		else
		{
			LeaveCriticalSection(&g_cs);
			break;
		}
	}
	return 0;
}

DWORD WINAPI SellB(void* arg)
{
	while (1)
	{
		EnterCriticalSection(&g_cs);
		if (tot > 0)
		{
			Sleep(1);
			tot--;
			printf("B reamain %d\n", tot);
			LeaveCriticalSection(&g_cs);
		}
		else
		{
			LeaveCriticalSection(&g_cs);
			break;
		}
	}
	return 0;
}

void test08()
{
	HANDLE hThreadA, hThreadB;
	hThreadA = CreateThread(NULL, 0, &SellA, NULL, 0, NULL);
	hThreadB = CreateThread(NULL, 0, &SellB, NULL, 0, NULL);
	CloseHandle(hThreadA);
	CloseHandle(hThreadB);

	InitializeCriticalSection(&g_cs);
	Sleep(40000);
	DeleteCriticalSection(&g_cs);
}


int main()
{
	//test01();
	//test02();
	//test03();
	//test057
	//test06();
	//test07();
	test08();

	system("pause");
	return 0;
}