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

���ִ� C++ ����У����Ƽ�ʹ�� C++11 ��׼���е� <thread>�����ṩ�˸��߼���������ʹ���ҿ�ƽ̨���̹߳���ӿڡ�

# WaitForSingleObject
WaitForSingleObject�������ڵȴ��������͵��ں˶��󣬰����������ڻ�������Mutex�����¼���Event�����ź�����Semaphore���Լ��̵߳ȡ�

WaitForSingleObject(
    _In_ HANDLE hHandle,
    _In_ DWORD dwMilliseconds
    );

# WaitForMultipleObjects
WaitForMultipleObjects(
		_In_ DWORD nCount,								�������
		_In_reads_(nCount) CONST HANDLE * lpHandles,	�������
		_In_ BOOL bWaitAll,								TRUE�ȴ����е��ں˶���FALSE����һ���ں˶��󷢳��ź�
		_In_ DWORD dwMilliseconds						�ȴ�ʱ��
	);
# Mutex
## CreateMutex(NULL, FALSE, NULL)
CreateMutexW(
		_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,	��ȫ����
		_In_ BOOL bInitialOwner,							������������ߣ�TRUE����ӵ�л�����
		_In_opt_ LPCWSTR lpName								ָ�򻥳��������ָ������
	);

## ReleaseMutex()
ReleaseMutex(
    _In_ HANDLE hMutex
    );


# �¼����� ������ ����������pthread_cond_t��

## CreateEventW()
CreateEventW(
    _In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,   //��ȫ���� NULL
    _In_ BOOL bManualReset,                             //��λ��ʽ TRUE ������ ResetEvent�ֶ���ԭ FALSE �Զ���ԭΪ���ź�״̬
    _In_ BOOL bInitialState,                            //��ʼ״̬ TRUE ��ʼ״̬Ϊ���ź�״̬ FALSE���ź�״̬
    _In_opt_ LPCWSTR lpName                             //�������� NULL����
    );

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

