# 创建线程
CreateThread 和 _beginthreadex 都是用来创建线程的函数，但它们分别属于不同的库和层次：

    CreateThread
        来源：CreateThread 是 Windows API 的一部分，直接在操作系统级别创建线程。
        功能：它提供了创建和管理线程的基本功能，包括设置线程优先级、线程安全性、线程上下文等。
        使用：通常用于需要直接访问底层系统功能或与 Windows API 紧密集成的应用程序中。
        资源管理：CreateThread 不会自动管理与线程相关联的 CRT 资源，如错误号 (errno) 或其他线程局部存储变量。

    _beginthreadex
        来源：_beginthreadex 是 Microsoft C Runtime (CRT) 库的一部分，它是对 CreateThread 的封装，提供了更高层次的线程创建功能。
        功能：除了提供基本的线程创建功能外，_beginthreadex 还负责初始化和清理 CRT 环境，确保每个线程都有其自己的 CRT 状态。
        使用：在使用 C/C++ 编译器（如 Visual C++）编写的程序中，推荐使用 _beginthreadex，因为它处理了与线程相关的 CRT 资源管理，防止内存泄漏。
        资源管理：_beginthreadex 内部会为每个新线程分配一个数据结构（通常称为 tiddata），用于存储线程特有的 CRT 数据。当线程结束时，通过 _endthreadex 函数自动清理这些资源。

主要区别总结：

    库依赖：CreateThread 直接调用 Windows API，而 _beginthreadex 是 CRT 的一部分，它内部调用了 CreateThread。
    资源管理：_beginthreadex 处理了线程特有的 CRT 资源管理，包括分配和释放线程数据结构，而 CreateThread 则不负责这些任务。
    线程局部存储：_beginthreadex 保证每个线程都有自己的 CRT 环境，包括线程局部的错误号和其他全局变量，避免了多线程间的数据冲突。
    调用建议：在使用 Microsoft Visual C++ 编译器时，建议使用 _beginthreadex 和 _endthreadex 来创建和结束线程，以确保正确处理 CRT 资源。

两种函数在线程回调函数设置上的主要区别：
当使用CreateThread创建线程时，你需要提供一个线程入口点（回调函数），这个函数的原型应该如下：
```c++
DWORD WINAPI ThreadFunction(LPVOID lpParameter);
```
其中DWORD WINAPI表明这是一个使用stdcall调用约定的函数，返回类型为DWORD，参数是一个LPVOID类型，代表传递给线程的参数。


_beginthreadex是Microsoft Visual C++运行时库（CRT）提供的线程创建函数，它实际上是CreateThread的一个封装，提供了额外的功能和便利性。_beginthreadex函数的回调函数原型更灵活，可以是任何返回类型和参数列表的函数，因为CRT会处理好转换和包装的工作。 
_beginthreadex的回调函数并不需要遵循特定的调用约定或返回类型，你可以像普通函数一样定义它，例如：
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
_beginthreadex会自动调用一个名为_threadstartex的内部函数，该函数会接收你的线程函数作为参数，并处理必要的上下文切换和初始化工作。
其他区别

除了回调函数的设置之外，_beginthreadex和CreateThread还有以下主要区别：

    _beginthreadex会在堆上分配一个与线程相关的数据块（_tiddata），用于保存线程的本地数据，这有助于在使用C运行时库函数时避免线程间的冲突。
    当使用_beginthreadex创建的线程结束时，会自动调用_exitthreadex函数来清理线程数据，避免内存泄漏。
    CreateThread不进行上述的自动管理，需要程序员更加细致地处理线程生命周期和资源管理。

总的来说，_beginthreadex提供了一个更高级别的接口，适用于那些使用Visual C++运行时库的程序，而CreateThread则提供了一个更底层的接口，适用于那些需要直接控制线程创建和管理的场景。



# WaitForSingleObject
WaitForSingleObject可以用于等待各种类型的内核对象，包括但不限于互斥量（Mutex）、事件（Event）、信号量（Semaphore）以及线程等。
```C++
WaitForSingleObject(
    _In_ HANDLE hHandle,
    _In_ DWORD dwMilliseconds
    );
```
# WaitForMultipleObjects
```C++
WaitForMultipleObjects(
		_In_ DWORD nCount,								句柄个数
		_In_reads_(nCount) CONST HANDLE * lpHandles,	句柄的组
		_In_ BOOL bWaitAll,								TRUE等待所有的内核对象，FALSE任意一个内核对象发出信号
		_In_ DWORD dwMilliseconds						等待时间
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
		_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,	安全属性
		_In_ BOOL bInitialOwner,							互斥对象所有者，TRUE立即拥有互斥体
		_In_opt_ LPCWSTR lpName								指向互斥对象名的指针名称
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

# 事件对象 类似于 条件变量（pthread_cond_t）

## CreateEventW()
```C++
WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
CreateEventW(
    _In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,   //安全属性 NULL
    _In_ BOOL bManualReset,                             //复位方式 TRUE 必须用 ResetEvent手动复原 FALSE 自动还原为无信号状态
    _In_ BOOL bInitialState,                            //初始状态 TRUE 初始状态为有信号状态 FALSE无信号状态
    _In_opt_ LPCWSTR lpName                             //对象名称 NULL无名
    );
```
手动重置事件 (Manual Reset Event)
当一个手动重置事件被触发（通过SetEvent函数），它可以保持在信号状态，直到某个线程或进程显式地调用ResetEvent函数将其重置回未触发状态。这意味着如果多个线程都在等待同一个手动重置事件，一旦事件被触发，所有等待的线程都将被唤醒，但事件会保持在触发状态，直到被手动重置。

自动重置事件 (Auto Reset Event)
相比之下，当一个自动重置事件被触发后，它只会保持在信号状态直到第一个等待它的线程被唤醒，之后事件会自动重置回未触发状态。这意味着如果多个线程都在等待同一个自动重置事件，只有第一个被唤醒的线程会继续执行，而其他线程将继续等待，直到事件再次被触发。

使用场景：
- 手动重置事件通常用于需要多个线程响应同一事件的情况，比如一个工作完成的标志，所有等待工作的线程都需要被通知。
- 自动重置事件通常用于信号量的作用，比如一个工作完成，只允许一个等待线程继续执行，完成后再等待下一个信号。


## SetEvent()   
设置为有信号状态

## ResetEvent()
设置为无信号状态

## WaitForSingleObject()请求事件对象。


# 内核对象
1. 内核对象
Windows 中每个内核对象都只是一个内存块，它由操作系统内核分配，并只能由操作系统内核进行访问，应用程序不能在内存中定位这些数据结构并直接更改其内容。
这个内存块是一个数据结构，其成员维护着与对象相关的信息。 
少数成员(安全描述符和使用计数)是所有内核对象都有的，但大多数成员都是不同类型对象特有的。 
CreateFile  
如:file 文件对象、event 事件对象、process 进程、thread 线程、mutex 互斥量、iocompletationport 完成端口(windows 服务器)、mailslot 邮槽和 registry注册表等

2. 内核对象的使用计数与生命期
内核对象的所有者是操作系统内核，而非进程。换言之也就是说当进程退出，内核对象不一定会销毁。 
操作系统内核通过内核对象的使用计数，知道当前有多少个进程正在使用一个特定的内核对象。 
初次创建内核对象，使用计数为1。当另一个进程获得该内核对象的访问权之后，使用计数加1。 
如果内核对象的使用计数递减为0，操作系统内核就会销毁该内核对象。
也就是说内核对象在当前进程中创建，但是当前进程退出时，内核对象有可能被另外一个进程访问。
这时，进程退出只会减少当前进程对引用的所有内核对象的使用计数，而不会减少其他进程对内核对象的使用计数(即使该内核对象由当前进程创建)。
那么内核对象的使用计数未递减为0，操作系统内核不会销毁该内核对象。

3. 操作内核对象
Windows 提供了一组函数进行操作内核对象。成功调用一个创建内核对象的函数后，会返回一个句柄，它表示了所创建的内核对象，可由进程中的任何线程使用。
在32 位进程中，句柄是一个32 位值，在 64 位进程中句柄是一个 64位值。我们可以使用唯一标识内核对象的句柄，调用内核操作函数对内核对象进行操作。

4. 内核对象与其他类型的对象
Windows 进程中除了内核对象还有其他类型的对象，比如窗口，菜单，字体等，这些属于用户对象和 GDI对象。
要区分内核对象与非内核对象，最简单的方式就是查看创建这个对象的函数，几乎所有创建内核对象的函数都有一个允许我们指定安全属性的参数。

5. CloseHandle 内核对象还没销毁，还可以通过 threadId 操作
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
	headle2 = OpenThread(THREAD_QUERY_INFORMATION, FALSE, threadId);	//通过threadId返回句柄
	headle2 = OpenThread(THREAD_QUERY_INFORMATION, FALSE, threadId);
	headle2 = OpenThread(THREAD_QUERY_INFORMATION, FALSE, threadId);

	return 0;
}
```


# 信号量
## CreateSemaphore

```c++
WINBASEAPI
HANDLE
WINAPI
CreateSemaphoreW(
    _In_opt_ LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
    _In_ LONG lInitialCount,                            //信号量对象的初始计数值
    _In_ LONG lMaximumCount,                            //信号量对象的计数最大值
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

# 关键代码段（应用层）
`CRITICAL_SECTION` 是 Windows 操作系统中用于实现轻量级互斥的一种数据结构，用于保护共享资源免受多线程环境下的并发访问。
它主要在用户模式下提供快速的线程间同步机制，相比于其他同步原语（如互斥量、事件、条件变量等），`CRITICAL_SECTION` 的开销较小，因为它主要依赖于处理器提供的原子操作来实现。

### 使用方法

1. **初始化**：在使用前，必须先初始化 `CRITICAL_SECTION` 结构。这可以通过调用 `InitializeCriticalSection` 函数完成。

2. **进入临界区**：当线程想要访问受保护的共享资源时，它需要调用 `EnterCriticalSection` 函数。这会使线程获得对 `CRITICAL_SECTION` 的所有权，从而阻止其他线程进入同一临界区。

3. **离开临界区**：当线程完成对共享资源的操作后，它应调用 `LeaveCriticalSection` 函数释放对 `CRITICAL_SECTION` 的所有权，允许其他线程进入。

4. **清理**：在不再需要 `CRITICAL_SECTION` 时，应调用 `DeleteCriticalSection` 函数来释放分配的资源。

### 示例代码

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

    // 多线程环境下，每个线程在访问共享资源前需调用 EnterCS()
    // 在访问结束后调用 LeaveCS()

    CleanupCS();
    return 0;
}
```

### 注意事项

- `CRITICAL_SECTION` 不是可重入的，这意味着线程不能在已经拥有 `CRITICAL_SECTION` 的情况下再次进入同一个 `CRITICAL_SECTION`。
- 它不支持超时，如果一个线程试图进入已经被另一个线程持有的 `CRITICAL_SECTION`，那么该线程将一直等待直到获得所有权。
- `CRITICAL_SECTION` 不是跨进程的，它只能在创建它的进程中使用，不能被其他进程中的线程访问。
- 使用不当可能会导致死锁，因此在设计多线程应用时，需要仔细考虑同步策略。

总的来说，`CRITICAL_SECTION` 是一种快速而简单的线程同步机制，适合用于保护短时间访问的共享资源，但在复杂或高性能的多线程应用中，可能需要考虑使用更高级的同步原语，如互斥量、条件变量等。


# 各种线程同步的比较总结
互斥Mutex，事件Event，关键代码段criticalSection，信号量Semaphore

互斥Mutex，事件Event，信号量Semaphore 属于内核对象，速度慢，可以在多个进程中的各个线程间进行同步。

关键代码段criticalSection在用户方式下，速度快。
当时使用时，容易进入死锁状态，因为在等待进入关键代码段时无法设定超时值。
只能在本进程。 

通常，在编写多线程程序并需要实现线程同步时，首选关键代码段，
由于它的使用比较简单如果是在 MFC程序中使用的话，可以在类的构造函数 Init,中调用 InitializeCriticalsection函数；
在该类的析构函数中调用 DeleteCriticalSection 函数，
在所需保护的代码前面调用EnterCriticalSection 函数，
在访问完所需保护的资源后，调用 LeaveCriticalSection 函数。



