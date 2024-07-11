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

    lpCommandLine：传递给新创建进程的命令行。这可以包括任何 命令行参数 。

    lpProcessAttributes：指向SECURITY_ATTRIBUTES结构的指针，该结构确定返回的新进程对象句柄是否可以被子进程继承。（说明是内核对象，NULL）

    lpThreadAttributes：与lpProcessAttributes类似，但针对线程对象。

    bInheritHandles：如果此值为TRUE，则新进程将继承调用进程的所有打开的句柄。

    dwCreationFlags：指定新进程的创建标志。常见的值包括CREATE_NEW_CONSOLE（创建新的控制台窗口）、CREATE_NO_WINDOW（防止创建窗口）和DETACHED_PROCESS（从当前作业对象分离进程）。

    lpEnvironment：指向新进程环境块的指针。如果为NULL，则新进程使用父进程的环境。

    lpCurrentDirectory：新进程的当前目录的完整路径。如果为NULL，则新进程使用父进程的当前目录。

    lpStartupInfo：指向STARTUPINFO结构的指针，用于设置新进程的启动信息，如控制台窗口的大小、位置等。

    lpProcessInformation：指向PROCESS_INFORMATION结构的指针，用于接收新进程的信息，如进程ID和主线程ID。

# 进程间通信方式

## 1 socket
    UDP TCP

## 2 剪贴板
```c++
OpenClipboard();

EmptyClipboard();

SetClipboardData(CF_TEXT, hClip);   文件格式，指向一块数据内存的指针

HANDLE hClip = GetClipboardData(CF_TEXT);   得到指向数据内存的指针

CloseClipboard();
```

## 3 邮槽
    有服务器和客户端概念（不常用，最大424字节，本地进程间通信，网络通信使用UDP（不可靠））  
    `单向，服务端接收，客户端发送`。
```C++
//接收端 创建邮槽

	LPCTSTR szSlotName = TEXT("\\\\.\\mailslot\\Mymailslot");
	HANDLE hSlot = CreateMailslot(szSlotName,						//CreateMailslot
		0,
		MAILSLOT_WAIT_FOREVER,
		NULL);

	char szBuf[1024] = { 0 };

	DWORD dwRead;
	if (!ReadFile(hSlot, szBuf, 100, &dwRead, NULL))				//ReadFile
	{
		MessageBox("Read Failed!!!");
		return;
	}

	TRACE("#########dwRead = %d\n", dwRead);
	MessageBox(szBuf);
```

```c++
//发送端 CreateFile连接

	LPCTSTR szSlotName = TEXT("\\\\.\\mailslot\\Mymailslot");
	HANDLE hMailSlot = CreateFile(szSlotName, FILE_GENERIC_WRITE,					//CreateFile
			FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	char szBuf[1024] = "Hello MailSlot";

	DWORD dwWriet;
	if (!WriteFile(hMailSlot, szBuf, strlen(szBuf) + 1, &dwWriet, NULL))			//WriteFile
	{
		MessageBox("WriteFile Failed!!!");
		return;
	}
	CloseHandle(hMailSlot);															//CloseHandle
```

## 4 匿名管道
    `父子进程之间的通信`
```c++
//创建匿名管道，父子进程。

	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);

	if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0))			//1. CreatePipe
	{
		MessageBox(_T("匿名管道创建失败"));
		return;
	}

	//创建子进程
	STARTUPINFO strStartupInfo;									//设置这个结构体来控制新进程的启动行为
	memset(&strStartupInfo, 0, sizeof(strStartupInfo));

	strStartupInfo.cb = sizeof(strStartupInfo);					//结构体的大小，必须被初始化为sizeof(STARTUPINFO)。
	strStartupInfo.dwFlags = STARTF_USESTDHANDLES;				//指定如何解释结构体的其他成员。例如，STARTF_USESHOWWINDOW控制窗口如何显示，STARTF_USESTDHANDLES允许你重定向标准输入/输出。
	strStartupInfo.hStdInput = hReadPipe;
	strStartupInfo.hStdOutput = hWritePipe;
	strStartupInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);

	PROCESS_INFORMATION szProcessInformation;					//存储由CreateProcess函数创建的新进程的信息
	memset(&szProcessInformation, 0, sizeof(szProcessInformation));

	int iRet = CreateProcess(									//2. CreateProcess
		_T("Process_Community_Client.exe"),
		NULL,
		NULL,
		NULL,
		TRUE,
		0,
		NULL,   
		NULL,
		&strStartupInfo,
		&szProcessInformation
	);
```

```C++
//发送端
	HANDLE hWritePipe = GetStdHandle(STD_OUTPUT_HANDLE);					//GetStdHandle

	char szBuf[1024] = "Unnamed Pipe Going From Client";
	DWORD dwWriet;
	if (!WriteFile(hWritePipe, szBuf, strlen(szBuf) + 1, &dwWriet, NULL))	//WriteFile
	{
		MessageBox("WriteFile Failed!!!");
		CloseHandle(hWritePipe);
		return;
	}
	CloseHandle(hWritePipe);												//CloseHandle
```

```c++
//接收端
	HANDLE hReadPipe = GetStdHandle(STD_INPUT_HANDLE);						//GetStdHandle

	char szBuf[1024] = { 0 };
	DWORD dwRead;
	if (!ReadFile(hReadPipe, szBuf, sizeof(szBuf), &dwRead, NULL))			//ReadFile
	{
		MessageBox("ReadFile Failed!!!");
		CloseHandle(hReadPipe);
		return;
	}
	CloseHandle(hReadPipe);													//CloseHandle
	MessageBox(szBuf);
```

## 5 命名管道 
    Socket 相似，支持网络之间不同进程的通信
```c++
	//创建 命名管道
	LPCTSTR szPipeName = TEXT("\\\\.\\pipe\\myPipe");	//和邮槽类似

	//PIPE_ACCESS_DUPLEX 全双工 ， FILE_FLAG_OVERLAPPED异步  的通信 ， PIPE_TYPE_BYTE 字节流
	hNamedPipe = CreateNamedPipe(szPipeName, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,		//1. CreateNamedPipe
		PIPE_TYPE_BYTE, 1, 1024, 1024, 0, NULL);

	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		TRACE("CreateNamePipe failed with &d\n", GetLastError());
		MessageBox(_T("创建命名管道失败"));
		return;
	}

	//手动重置
	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);									//2. CreateEvent
	if (NULL == hEvent)
	{
		MessageBox(_T("创建事件失败"));
		CloseHandle(hNamedPipe);
		hNamedPipe = NULL;
		return;
	}

	// 用于异步 I/O 操作的结构。
	
	/*OVERLAPPED结构体成员
	Internal: 供系统使用的内部指针。
	InternalHigh : 另一个供系统使用的内部指针。
	Offset : 文件偏移量的低32位，用于异步文件操作。
	OffsetHigh : 文件偏移量的高32位。
	Pointer : 应用程序定义的指针，可以指向任何数据结构，如工作项的上下文信息。
	hEvent : 一个事件句柄，I / O 完成时会被信号量设置。*/

	OVERLAPPED ovlap;
	ZeroMemory(&ovlap, sizeof(OVERLAPPED));
	ovlap.hEvent = hEvent;

	if (!ConnectNamedPipe(hNamedPipe, &ovlap))												//3. ConnectNamedPipe
	{
		if (ERROR_IO_PENDING != GetLastError())
		{
			MessageBox(_T("等待客户端链接失败"));
			CloseHandle(hNamedPipe);
			CloseHandle(hEvent);
			hNamedPipe = NULL;
			hEvent = NULL;
			return;
		}
	}	
	if (WaitForSingleObject(hEvent, INFINITE) == WAIT_FAILED)								//4. WaitForSingleObject
	{
		MessageBox(_T("等待对象失败"));
		CloseHandle(hNamedPipe);
		CloseHandle(hEvent);
		hNamedPipe = NULL;
		hEvent = NULL;
		return;
	}
```

```c++
//连接命名管道
	LPCTSTR szNamedPipeName = TEXT("\\\\.\\pipe\\myPipe");

	if (0 == WaitNamedPipe(szNamedPipeName, NMPWAIT_WAIT_FOREVER))
	{
		MessageBox(_T("当前没有可以利用的管道"));
		return;
	}

	HANDLE hNamedPipe = CreateFile(szNamedPipeName, GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		TRACE("CreateFile Failed with %d\n", GetLastError());
		MessageBox(_T("打开命名管道失败！"));
		hNamedPipe = NULL;
		return;
	}
```

```c++
//发送端
	char szBuf[1024] = "Named Pipe Comming From Server";
	DWORD dwRead;
	if (!WriteFile(hNamedPipe, szBuf, strlen(szBuf) + 1, &dwRead, NULL))
	{
		MessageBox("WriteFile Failed!!!");
		CloseHandle(hNamedPipe);
		return;
	}
	CloseHandle(hNamedPipe);
```

```c++
//接收端
	char szBuf[100] = { 0 };
	DWORD dwRead;
	TRACE("Begin ReadFile");
	if (!ReadFile(hNamedPipe, szBuf, 100, &dwRead, NULL))
	{
		MessageBox(_T("读取数据失败"));
		CloseHandle(hNamedPipe);
		return;
	}
	MessageBox(szBuf);
	CloseHandle(hNamedPipe);
```

## 6 Copy_data findwindows wm_copydata  消息 Sendmessage （MFC中最常用，最重要，灵活，只需拿到窗口句柄）
```c++
	//发送端
	CString strWindowsTitle = _T("服务端");
	CString strMsg = _T("COPYDATA");
	// 利用标题拿到句柄
	HWND hWnd = ::FindWindow(NULL, strWindowsTitle.GetBuffer(0));									//1. ::FindWindow

	if (hWnd != NULL && IsWindow(hWnd))
	{
		//数据的封装
		COPYDATASTRUCT cpd;
		cpd.dwData = 0;
		cpd.cbData = strMsg.GetLength() * sizeof(TCHAR);	//大小
		cpd.lpData = (PVOID)strMsg.GetBuffer(0);			//指针

		//hWnd 接收端
		//AfxGetApp()->m_pMainWnd 是 MFC 中用于获取应用程序主窗口句柄的表达式 (数据来源)
		//(LPARAM)&cpd: 这是 lParam 参数，它包含了一个指向 COPYDATASTRUCT 结构的指针。cpd 必须是 COPYDATASTRUCT 类型，它包含了数据的大小和数据本身。

		::SendMessage(hWnd, WM_COPYDATA, (WPARAM)(AfxGetApp()->m_pMainWnd), (LPARAM)&cpd);			//2. ::SendMessage
	}		
	strWindowsTitle.ReleaseBuffer();
	strMsg.ReleaseBuffer();
```

```c++
	//创建一个接收信号，接收CopyData消息

BOOL CProcessCommunityDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	//接收CopyData消息
	LPCTSTR szText = (LPCTSTR)(pCopyDataStruct->lpData);
	DWORD dwLength = (DWORD)pCopyDataStruct->cbData;
	TCHAR szRecvText[1024] = { 0 };
	memcpy(szRecvText, szText, dwLength);
	//szRecvText 应该是消息文本，而 _T("Y") 应该是标题文本，MB_OK 则是消息框的按钮和样式标志
	MessageBox(szRecvText, _T("Y"), MB_OK);
	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}
```


# 通信方式的比较
1. 剪切板和匿名管道只能实现`同一机器的两个进程通信`，而不能实现网络进程之间的通信。
2. 邮槽是基于广播的，可以一对多发送。但只能一个发送，一个接收，要想同时发送接收，须写两次代码。邮槽的缺点传输的数据量很小424 字节以下。
3. 命名管道和邮槽可以进行网络通信。`命名管道只能是点对点的单一通信`。
4. WM_COPY_DATA 封装数据和解析数据。非常方便。如果数据量大，建议用命名管道。  



# 匿名管道 命名管道

匿名管道（通常在 Unix/Linux 系统中称为无名管道或 FIFO 管道）和命名管道在概念上有相似之处，但它们的使用方式和行为有所不同。

在 Unix/Linux 系统中，匿名管道是通过 pipe() 系统调用创建的，它创建了一对特殊的文件描述符：一个用于写入（通常为 1），另一个用于读取（通常为 0）。这种管道存在于内存中，通常用于进程间通信（IPC），特别是父子进程之间的通信。匿名管道的特点是半双工，也就是说，数据只能在一个方向上流动——从写端到读端。

当你使用匿名管道时，通常需要首先有进程在读端等待，然后才能从写端发送数据。这是因为匿名管道具有先进先出（FIFO）的特性，如果写端在没有任何进程读取的情况下发送数据，数据可能会被丢弃（如果管道缓冲区满了）或导致写操作阻塞（直到有读取操作或管道缓冲区有足够的空间）。

然而，这并不意味着你必须在发送数据前始终等待接收方。你可以在写端使用非阻塞模式，这样写操作不会阻塞，而是立即返回，如果管道缓冲区满则返回一个错误（通常是 EAGAIN 或 EWOULDBLOCK）。这允许发送方在无需等待接收方的情况下继续执行其他任务。

在 Windows 系统中，命名管道提供了更复杂的特性，包括全双工通信和异步 I/O 支持，这使得它们在功能上与 Unix/Linux 系统中的套接字更接近。命名管道允许同时读写，而且可以通过适当的配置支持多路通信。

总之，匿名管道在 Unix/Linux 系统中通常是半双工的，需要有读端等待才能有效发送数据，但这可以通过使用非阻塞模式来灵活处理。而在 Windows 系统中，命名管道提供了更高级的功能，包括全双工通信和异步操作。


