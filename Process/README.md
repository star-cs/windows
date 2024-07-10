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

