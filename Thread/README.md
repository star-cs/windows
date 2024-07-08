# �����߳�
CreateThread �� _beginthreadex �������������̵߳ĺ����������Ƿֱ����ڲ�ͬ�Ŀ�Ͳ�Σ�

    CreateThread
        ��Դ��CreateThread �� Windows API ��һ���֣�ֱ���ڲ���ϵͳ���𴴽��̡߳�
        ���ܣ����ṩ�˴����͹����̵߳Ļ������ܣ����������߳����ȼ����̰߳�ȫ�ԡ��߳������ĵȡ�
        ʹ�ã�ͨ��������Ҫֱ�ӷ��ʵײ�ϵͳ���ܻ��� Windows API ���ܼ��ɵ�Ӧ�ó����С�
        ��Դ����CreateThread �����Զ��������߳�������� CRT ��Դ�������� (errno) �������ֲ߳̾��洢������

    _beginthreadex
        ��Դ��_beginthreadex �� Microsoft C Runtime (CRT) ���һ���֣����Ƕ� CreateThread �ķ�װ���ṩ�˸��߲�ε��̴߳������ܡ�
        ���ܣ������ṩ�������̴߳��������⣬_beginthreadex �������ʼ�������� CRT ������ȷ��ÿ���̶߳������Լ��� CRT ״̬��
        ʹ�ã���ʹ�� C/C++ ���������� Visual C++����д�ĳ����У��Ƽ�ʹ�� _beginthreadex����Ϊ�����������߳���ص� CRT ��Դ������ֹ�ڴ�й©��
        ��Դ����_beginthreadex �ڲ���Ϊÿ�����̷߳���һ�����ݽṹ��ͨ����Ϊ tiddata�������ڴ洢�߳����е� CRT ���ݡ����߳̽���ʱ��ͨ�� _endthreadex �����Զ�������Щ��Դ��

��Ҫ�����ܽ᣺

    ��������CreateThread ֱ�ӵ��� Windows API���� _beginthreadex �� CRT ��һ���֣����ڲ������� CreateThread��
    ��Դ����_beginthreadex �������߳����е� CRT ��Դ��������������ͷ��߳����ݽṹ���� CreateThread �򲻸�����Щ����
    �ֲ߳̾��洢��_beginthreadex ��֤ÿ���̶߳����Լ��� CRT �����������ֲ߳̾��Ĵ���ź�����ȫ�ֱ����������˶��̼߳�����ݳ�ͻ��
    ���ý��飺��ʹ�� Microsoft Visual C++ ������ʱ������ʹ�� _beginthreadex �� _endthreadex �������ͽ����̣߳���ȷ����ȷ���� CRT ��Դ��

���ֺ������̻߳ص����������ϵ���Ҫ����
��ʹ��CreateThread�����߳�ʱ������Ҫ�ṩһ���߳���ڵ㣨�ص������������������ԭ��Ӧ�����£�
```c++
DWORD WINAPI ThreadFunction(LPVOID lpParameter);
```
����DWORD WINAPI��������һ��ʹ��stdcall����Լ���ĺ�������������ΪDWORD��������һ��LPVOID���ͣ������ݸ��̵߳Ĳ�����


_beginthreadex��Microsoft Visual C++����ʱ�⣨CRT���ṩ���̴߳�����������ʵ������CreateThread��һ����װ���ṩ�˶���Ĺ��ܺͱ����ԡ�_beginthreadex�����Ļص�����ԭ�͸����������κη������ͺͲ����б�ĺ�������ΪCRT�ᴦ���ת���Ͱ�װ�Ĺ����� 
_beginthreadex�Ļص�����������Ҫ��ѭ�ض��ĵ���Լ���򷵻����ͣ����������ͨ����һ�������������磺
```c++
unsigned int __cdecl _beginthreadex(
    void *security,
    unsigned stack_size,
    unsigned (__stdcall *start_address)(void *),
    void *arglist,
    unsigned initflag,
    unsigned *thrdaddr
);

void MyThreadFunction(void* pParameter);
```
_beginthreadex���Զ�����һ����Ϊ_threadstartex���ڲ��������ú������������̺߳�����Ϊ�������������Ҫ���������л��ͳ�ʼ��������
��������

���˻ص�����������֮�⣬_beginthreadex��CreateThread����������Ҫ����

    _beginthreadex���ڶ��Ϸ���һ�����߳���ص����ݿ飨_tiddata�������ڱ����̵߳ı������ݣ�����������ʹ��C����ʱ�⺯��ʱ�����̼߳�ĳ�ͻ��
    ��ʹ��_beginthreadex�������߳̽���ʱ�����Զ�����_exitthreadex�����������߳����ݣ������ڴ�й©��
    CreateThread�������������Զ�������Ҫ����Ա����ϸ�µش����߳��������ں���Դ����

�ܵ���˵��_beginthreadex�ṩ��һ�����߼���Ľӿڣ���������Щʹ��Visual C++����ʱ��ĳ��򣬶�CreateThread���ṩ��һ�����ײ�Ľӿڣ���������Щ��Ҫֱ�ӿ����̴߳����͹���ĳ�����



# WaitForSingleObject
WaitForSingleObject�������ڵȴ��������͵��ں˶��󣬰����������ڻ�������Mutex�����¼���Event�����ź�����Semaphore���Լ��̵߳ȡ�
```C++
WaitForSingleObject(
    _In_ HANDLE hHandle,
    _In_ DWORD dwMilliseconds
    );
```
# WaitForMultipleObjects
```C++
WaitForMultipleObjects(
		_In_ DWORD nCount,								�������
		_In_reads_(nCount) CONST HANDLE * lpHandles,	�������
		_In_ BOOL bWaitAll,								TRUE�ȴ����е��ں˶���FALSE����һ���ں˶��󷢳��ź�
		_In_ DWORD dwMilliseconds						�ȴ�ʱ��
	);
```

# Mutex
## CreateMutex(NULL, FALSE, NULL)
```C++
WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
CreateMutexW(
		_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,	��ȫ����
		_In_ BOOL bInitialOwner,							������������ߣ�TRUE����ӵ�л�����
		_In_opt_ LPCWSTR lpName								ָ�򻥳��������ָ������
	);
```

## ReleaseMutex()
```C++
WINBASEAPI
BOOL
WINAPI
ReleaseMutex(
    _In_ HANDLE hMutex
    );
```

# �¼����� ������ ����������pthread_cond_t��

## CreateEventW()
```C++
WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
CreateEventW(
    _In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,   //��ȫ���� NULL
    _In_ BOOL bManualReset,                             //��λ��ʽ TRUE ������ ResetEvent�ֶ���ԭ FALSE �Զ���ԭΪ���ź�״̬
    _In_ BOOL bInitialState,                            //��ʼ״̬ TRUE ��ʼ״̬Ϊ���ź�״̬ FALSE���ź�״̬
    _In_opt_ LPCWSTR lpName                             //�������� NULL����
    );
```
�ֶ������¼� (Manual Reset Event)
��һ���ֶ������¼���������ͨ��SetEvent�������������Ա������ź�״̬��ֱ��ĳ���̻߳������ʽ�ص���ResetEvent�����������û�δ����״̬������ζ���������̶߳��ڵȴ�ͬһ���ֶ������¼���һ���¼������������еȴ����̶߳��������ѣ����¼��ᱣ���ڴ���״̬��ֱ�����ֶ����á�

�Զ������¼� (Auto Reset Event)
���֮�£���һ���Զ������¼�����������ֻ�ᱣ�����ź�״ֱ̬����һ���ȴ������̱߳����ѣ�֮���¼����Զ����û�δ����״̬������ζ���������̶߳��ڵȴ�ͬһ���Զ������¼���ֻ�е�һ�������ѵ��̻߳����ִ�У��������߳̽������ȴ���ֱ���¼��ٴα�������

ʹ�ó�����
- �ֶ������¼�ͨ��������Ҫ����߳���Ӧͬһ�¼������������һ��������ɵı�־�����еȴ��������̶߳���Ҫ��֪ͨ��
- �Զ������¼�ͨ�������ź��������ã�����һ��������ɣ�ֻ����һ���ȴ��̼߳���ִ�У���ɺ��ٵȴ���һ���źš�


## SetEvent()   
����Ϊ���ź�״̬

## ResetEvent()
����Ϊ���ź�״̬

## WaitForSingleObject()�����¼�����


# �ں˶���
1. �ں˶���
Windows ��ÿ���ں˶���ֻ��һ���ڴ�飬���ɲ���ϵͳ�ں˷��䣬��ֻ���ɲ���ϵͳ�ں˽��з��ʣ�Ӧ�ó��������ڴ��ж�λ��Щ���ݽṹ��ֱ�Ӹ��������ݡ�
����ڴ����һ�����ݽṹ�����Աά�����������ص���Ϣ�� 
������Ա(��ȫ��������ʹ�ü���)�������ں˶����еģ����������Ա���ǲ�ͬ���Ͷ������еġ� 
CreateFile  
��:file �ļ�����event �¼�����process ���̡�thread �̡߳�mutex ��������iocompletationport ��ɶ˿�(windows ������)��mailslot �ʲۺ� registryע����

2. �ں˶����ʹ�ü�����������
�ں˶�����������ǲ���ϵͳ�ںˣ����ǽ��̡�����֮Ҳ����˵�������˳����ں˶���һ�������١� 
����ϵͳ�ں�ͨ���ں˶����ʹ�ü�����֪����ǰ�ж��ٸ���������ʹ��һ���ض����ں˶��� 
���δ����ں˶���ʹ�ü���Ϊ1������һ�����̻�ø��ں˶���ķ���Ȩ֮��ʹ�ü�����1�� 
����ں˶����ʹ�ü����ݼ�Ϊ0������ϵͳ�ں˾ͻ����ٸ��ں˶���
Ҳ����˵�ں˶����ڵ�ǰ�����д��������ǵ�ǰ�����˳�ʱ���ں˶����п��ܱ�����һ�����̷��ʡ�
��ʱ�������˳�ֻ����ٵ�ǰ���̶����õ������ں˶����ʹ�ü���������������������̶��ں˶����ʹ�ü���(��ʹ���ں˶����ɵ�ǰ���̴���)��
��ô�ں˶����ʹ�ü���δ�ݼ�Ϊ0������ϵͳ�ں˲������ٸ��ں˶���

3. �����ں˶���
Windows �ṩ��һ�麯�����в����ں˶��󡣳ɹ�����һ�������ں˶���ĺ����󣬻᷵��һ�����������ʾ�����������ں˶��󣬿��ɽ����е��κ��߳�ʹ�á�
��32 λ�����У������һ��32 λֵ���� 64 λ�����о����һ�� 64λֵ�����ǿ���ʹ��Ψһ��ʶ�ں˶���ľ���������ں˲����������ں˶�����в�����

4. �ں˶������������͵Ķ���
Windows �����г����ں˶������������͵Ķ��󣬱��細�ڣ��˵�������ȣ���Щ�����û������ GDI����
Ҫ�����ں˶�������ں˶�����򵥵ķ�ʽ���ǲ鿴�����������ĺ������������д����ں˶���ĺ�������һ����������ָ����ȫ���ԵĲ�����

5. CloseHandle �ں˶���û���٣�������ͨ�� threadId ����
```C++
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
	headle2 = OpenThread(THREAD_QUERY_INFORMATION, FALSE, threadId);	//ͨ��threadId���ؾ��
	headle2 = OpenThread(THREAD_QUERY_INFORMATION, FALSE, threadId);
	headle2 = OpenThread(THREAD_QUERY_INFORMATION, FALSE, threadId);

	return 0;
}
```


# �ź���
## CreateSemaphore

```c++
WINBASEAPI
HANDLE
WINAPI
CreateSemaphoreW(
    _In_opt_ LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
    _In_ LONG lInitialCount,                            //�ź�������ĳ�ʼ����ֵ
    _In_ LONG lMaximumCount,                            //�ź�������ļ������ֵ
    _In_opt_ LPCWSTR lpName
    );

```

## ReleaseSemaphore
```c++
WINBASEAPI
BOOL
WINAPI
ReleaseSemaphore(
    _In_ HANDLE hSemaphore,
    _In_ LONG lReleaseCount,
    _Out_opt_ LPLONG lpPreviousCount
    );
```

# �ؼ�����Σ�Ӧ�ò㣩
`CRITICAL_SECTION` �� Windows ����ϵͳ������ʵ�������������һ�����ݽṹ�����ڱ���������Դ���ܶ��̻߳����µĲ������ʡ�
����Ҫ���û�ģʽ���ṩ���ٵ��̼߳�ͬ�����ƣ����������ͬ��ԭ��绥�������¼������������ȣ���`CRITICAL_SECTION` �Ŀ�����С����Ϊ����Ҫ�����ڴ������ṩ��ԭ�Ӳ�����ʵ�֡�

### ʹ�÷���

1. **��ʼ��**����ʹ��ǰ�������ȳ�ʼ�� `CRITICAL_SECTION` �ṹ�������ͨ������ `InitializeCriticalSection` ������ɡ�

2. **�����ٽ���**�����߳���Ҫ�����ܱ����Ĺ�����Դʱ������Ҫ���� `EnterCriticalSection` ���������ʹ�̻߳�ö� `CRITICAL_SECTION` ������Ȩ���Ӷ���ֹ�����߳̽���ͬһ�ٽ�����

3. **�뿪�ٽ���**�����߳���ɶԹ�����Դ�Ĳ�������Ӧ���� `LeaveCriticalSection` �����ͷŶ� `CRITICAL_SECTION` ������Ȩ�����������߳̽��롣

4. **����**���ڲ�����Ҫ `CRITICAL_SECTION` ʱ��Ӧ���� `DeleteCriticalSection` �������ͷŷ������Դ��

### ʾ������

```cpp
#include <windows.h>

CRITICAL_SECTION g_criticalSection;

void InitCriticalSection() {
    InitializeCriticalSection(&g_criticalSection);
}

void EnterCS() {
    EnterCriticalSection(&g_criticalSection);
}

void LeaveCS() {
    LeaveCriticalSection(&g_criticalSection);
}

void CleanupCS() {
    DeleteCriticalSection(&g_criticalSection);
}

int main() {
    InitCriticalSection();

    // ���̻߳����£�ÿ���߳��ڷ��ʹ�����Դǰ����� EnterCS()
    // �ڷ��ʽ�������� LeaveCS()

    CleanupCS();
    return 0;
}
```

### ע������

- `CRITICAL_SECTION` ���ǿ�����ģ�����ζ���̲߳������Ѿ�ӵ�� `CRITICAL_SECTION` ��������ٴν���ͬһ�� `CRITICAL_SECTION`��
- ����֧�ֳ�ʱ�����һ���߳���ͼ�����Ѿ�����һ���̳߳��е� `CRITICAL_SECTION`����ô���߳̽�һֱ�ȴ�ֱ���������Ȩ��
- `CRITICAL_SECTION` ���ǿ���̵ģ���ֻ���ڴ������Ľ�����ʹ�ã����ܱ����������е��̷߳��ʡ�
- ʹ�ò������ܻᵼ���������������ƶ��߳�Ӧ��ʱ����Ҫ��ϸ����ͬ�����ԡ�

�ܵ���˵��`CRITICAL_SECTION` ��һ�ֿ��ٶ��򵥵��߳�ͬ�����ƣ��ʺ����ڱ�����ʱ����ʵĹ�����Դ�����ڸ��ӻ�����ܵĶ��߳�Ӧ���У�������Ҫ����ʹ�ø��߼���ͬ��ԭ��绥���������������ȡ�


# �����߳�ͬ���ıȽ��ܽ�
����Mutex���¼�Event���ؼ������criticalSection���ź���Semaphore

����Mutex���¼�Event���ź���Semaphore �����ں˶����ٶ����������ڶ�������еĸ����̼߳����ͬ����

�ؼ������criticalSection���û���ʽ�£��ٶȿ졣
��ʱʹ��ʱ�����׽�������״̬����Ϊ�ڵȴ�����ؼ������ʱ�޷��趨��ʱֵ��
ֻ���ڱ����̡� 

ͨ�����ڱ�д���̳߳�����Ҫʵ���߳�ͬ��ʱ����ѡ�ؼ�����Σ�
��������ʹ�ñȽϼ�������� MFC������ʹ�õĻ�����������Ĺ��캯�� Init,�е��� InitializeCriticalsection������
�ڸ�������������е��� DeleteCriticalSection ������
�����豣���Ĵ���ǰ�����EnterCriticalSection ������
�ڷ��������豣������Դ�󣬵��� LeaveCriticalSection ������



