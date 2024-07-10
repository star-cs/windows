# 进程Process

## CreateProcess

类似于 fork() + exec()

```c++
WINBASEAPI
BOOL
WINAPI
CreateProcessW(
    _In_opt_ LPCSTR lpApplicationName,
    _Inout_opt_ LPSTR lpCommandLine,
    _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,     
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ BOOL bInheritHandles,
    _In_ DWORD dwCreationFlags,
    _In_opt_ LPVOID lpEnvironment,
    _In_opt_ LPCSTR lpCurrentDirectory,
    _In_ LPSTARTUPINFOA lpStartupInfo,
    _Out_ LPPROCESS_INFORMATION lpProcessInformation
    );
```

    lpApplicationName：要执行的模块（可执行文件）的名称。

    lpCommandLine：传递给新创建进程的命令行。这可以包括任何命令行参数。

    lpProcessAttributes：指向SECURITY_ATTRIBUTES结构的指针，该结构确定返回的新进程对象句柄是否可以被子进程继承。（说明是内核对象，NULL）

    lpThreadAttributes：与lpProcessAttributes类似，但针对线程对象。

    bInheritHandles：如果此值为TRUE，则新进程将继承调用进程的所有打开的句柄。

    dwCreationFlags：指定新进程的创建标志。常见的值包括CREATE_NEW_CONSOLE（创建新的控制台窗口）、CREATE_NO_WINDOW（防止创建窗口）和DETACHED_PROCESS（从当前作业对象分离进程）。

    lpEnvironment：指向新进程环境块的指针。如果为NULL，则新进程使用父进程的环境。

    lpCurrentDirectory：新进程的当前目录的完整路径。如果为NULL，则新进程使用父进程的当前目录。

    lpStartupInfo：指向STARTUPINFO结构的指针，用于设置新进程的启动信息，如控制台窗口的大小、位置等。

    lpProcessInformation：指向PROCESS_INFORMATION结构的指针，用于接收新进程的信息，如进程ID和主线程ID。

# 进程间通信方式

1 socket

2 剪贴板

3 邮槽
    有服务器和客户端概念

4 匿名管道
    父子进程之间的通信

5 命名管道 
    Socket 相似，支持网络之间不同进程的通信


6 Copy_data findwindows wm_copydata  消息 Sendmessage

# 匿名管道 命名管道

匿名管道（通常在 Unix/Linux 系统中称为无名管道或 FIFO 管道）和命名管道在概念上有相似之处，但它们的使用方式和行为有所不同。

在 Unix/Linux 系统中，匿名管道是通过 pipe() 系统调用创建的，它创建了一对特殊的文件描述符：一个用于写入（通常为 1），另一个用于读取（通常为 0）。这种管道存在于内存中，通常用于进程间通信（IPC），特别是父子进程之间的通信。匿名管道的特点是半双工，也就是说，数据只能在一个方向上流动——从写端到读端。

当你使用匿名管道时，通常需要首先有进程在读端等待，然后才能从写端发送数据。这是因为匿名管道具有先进先出（FIFO）的特性，如果写端在没有任何进程读取的情况下发送数据，数据可能会被丢弃（如果管道缓冲区满了）或导致写操作阻塞（直到有读取操作或管道缓冲区有足够的空间）。

然而，这并不意味着你必须在发送数据前始终等待接收方。你可以在写端使用非阻塞模式，这样写操作不会阻塞，而是立即返回，如果管道缓冲区满则返回一个错误（通常是 EAGAIN 或 EWOULDBLOCK）。这允许发送方在无需等待接收方的情况下继续执行其他任务。

在 Windows 系统中，命名管道提供了更复杂的特性，包括全双工通信和异步 I/O 支持，这使得它们在功能上与 Unix/Linux 系统中的套接字更接近。命名管道允许同时读写，而且可以通过适当的配置支持多路通信。

总之，匿名管道在 Unix/Linux 系统中通常是半双工的，需要有读端等待才能有效发送数据，但这可以通过使用非阻塞模式来灵活处理。而在 Windows 系统中，命名管道提供了更高级的功能，包括全双工通信和异步操作。
