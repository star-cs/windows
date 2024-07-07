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

WaitForSingleObject(
    _In_ HANDLE hHandle,
    _In_ DWORD dwMilliseconds
    );

# WaitForMultipleObjects
WaitForMultipleObjects(
		_In_ DWORD nCount,								句柄个数
		_In_reads_(nCount) CONST HANDLE * lpHandles,	句柄的组
		_In_ BOOL bWaitAll,								TRUE等待所有的内核对象，FALSE任意一个内核对象发出信号
		_In_ DWORD dwMilliseconds						等待时间
	);
# Mutex
## CreateMutex(NULL, FALSE, NULL)
CreateMutexW(
		_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,	安全属性
		_In_ BOOL bInitialOwner,							互斥对象所有者，TRUE立即拥有互斥体
		_In_opt_ LPCWSTR lpName								指向互斥对象名的指针名称
	);

## ReleaseMutex()
ReleaseMutex(
    _In_ HANDLE hMutex
    );


# 事件对象 类似于 条件变量（pthread_cond_t）

## CreateEventW()
CreateEventW(
    _In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,   //安全属性 NULL
    _In_ BOOL bManualReset,                             //复位方式 TRUE 必须用 ResetEvent手动复原 FALSE 自动还原为无信号状态
    _In_ BOOL bInitialState,                            //初始状态 TRUE 初始状态为有信号状态 FALSE无信号状态
    _In_opt_ LPCWSTR lpName                             //对象名称 NULL无名
    );

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

