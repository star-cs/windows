
// Process_CommunityDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Process_Community.h"
#include "Process_CommunityDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProcessCommunityDlg 对话框



CProcessCommunityDlg::CProcessCommunityDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROCESS_COMMUNITY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProcessCommunityDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CProcessCommunityDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RECV, &CProcessCommunityDlg::OnBnClickedButtonRecv)
	ON_BN_CLICKED(IDC_CREATE_BTN, &CProcessCommunityDlg::OnBnClickedCreateBtn)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CProcessCommunityDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CProcessCommunityDlg 消息处理程序

BOOL CProcessCommunityDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CProcessCommunityDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CProcessCommunityDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CProcessCommunityDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HANDLE hReadPipe;
HANDLE hWritePipe;
HANDLE hNamedPipe;

void CProcessCommunityDlg::OnBnClickedButtonRecv()
{
#if 0
	// 邮槽
	LPCTSTR szSlotName = TEXT("\\\\.\\mailslot\\Mymailslot");
	HANDLE hSlot = CreateMailslot(szSlotName,
		0,
		MAILSLOT_WAIT_FOREVER,
		NULL);

	if (hSlot == INVALID_HANDLE_VALUE)
	{
		TRACE("CreateMailslot failed with %d \n", GetLastError());
		return;
	}

	char szBuf[1024] = { 0 };

	DWORD dwRead;
	if (!ReadFile(hSlot, szBuf, 100, &dwRead, NULL))
	{
		MessageBox("Read Failed!!!");
		return;
	}

	TRACE("#########dwRead = %d\n", dwRead);
	MessageBox(szBuf);
#endif

#if 0
	//匿名管道
	char szBuf[100] = { 0 };
	DWORD dwRead;
	TRACE("Begin ReadFile");
	if (!ReadFile(hReadPipe, szBuf, 100, &dwRead, NULL))
	{
		MessageBox(_T("读取数据失败"));
		CloseHandle(hNamedPipe);
		return;
	}
	CloseHandle(hNamedPipe);
	MessageBox(szBuf);
#endif

	//命名管道
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
}

void CProcessCommunityDlg::OnBnClickedButtonSend()
{
	//匿名管道
#if 0
	char szBuf[1024] = "Unnamed Pipe Comming From Server";
	DWORD dwRead;
	if (!WriteFile(hWritePipe, szBuf, strlen(szBuf) + 1, &dwRead, NULL))
	{
		MessageBox("WriteFile Failed!!!");
		CloseHandle(hWritePipe);
	}

#endif

	//命名管道
	char szBuf[1024] = "Named Pipe Comming From Server";
	DWORD dwRead;
	if (!WriteFile(hNamedPipe, szBuf, strlen(szBuf) + 1, &dwRead, NULL))
	{
		MessageBox("WriteFile Failed!!!");
		CloseHandle(hNamedPipe);
		return;
	}
	CloseHandle(hNamedPipe);
}


void CProcessCommunityDlg::OnBnClickedCreateBtn()
{
#if 0
	// 匿名管道
	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);

	if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0))
	{
		MessageBox(_T("匿名管道创建失败"));
		return;
	}

	//创建子进程
	STARTUPINFO strStartupInfo;
	memset(&strStartupInfo, 0, sizeof(strStartupInfo));

	strStartupInfo.cb = sizeof(strStartupInfo);
	strStartupInfo.dwFlags = STARTF_USESTDHANDLES;
	strStartupInfo.hStdInput = hReadPipe;
	strStartupInfo.hStdOutput = hWritePipe;
	strStartupInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);

	PROCESS_INFORMATION szProcessInformation;
	memset(&szProcessInformation, 0, sizeof(szProcessInformation));

	int iRet = CreateProcess(
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

	if (iRet)
	{
		CloseHandle(szProcessInformation.hProcess);
		CloseHandle(szProcessInformation.hThread);
		szProcessInformation.dwProcessId = 0;
		szProcessInformation.dwThreadId = 0;
		szProcessInformation.hThread = NULL;
		szProcessInformation.hProcess = NULL;
	}
	else
	{
		CloseHandle(hReadPipe);
		CloseHandle(hWritePipe);

		hReadPipe = NULL;
		hWritePipe = NULL;
		
		MessageBox(_T("创建子进程失败"));
		return;
	}
#endif 

	// 命名管道	服务端
	LPCTSTR szPipeName = TEXT("\\\\.\\pipe\\myPipe"); //和邮槽类似
	//PIPE_ACCESS_DUPLEX 全双工 ， FILE_FLAG_OVERLAPPED异步  的通信
	hNamedPipe = CreateNamedPipe(szPipeName, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
		PIPE_TYPE_BYTE, 1, 1024, 1024, 0, NULL);

	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		TRACE("CreateNamePipe failed with &d\n", GetLastError());
		MessageBox(_T("创建命名管道失败"));
		return;
	}

	//手动重置
	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
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
	ZeroMemory(&ovlap, sizeof(OVERFLOW));
	ovlap.hEvent = hEvent;

	if (!ConnectNamedPipe(hNamedPipe, &ovlap))
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
	if (WaitForSingleObject(hEvent, INFINITE) == WAIT_FAILED)
	{
		MessageBox(_T("等待对象失败"));
		CloseHandle(hNamedPipe);
		CloseHandle(hEvent);
		hNamedPipe = NULL;
		hEvent = NULL;
		return;
	}

}


