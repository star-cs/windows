
// MFCFileDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCFile.h"
#include "MFCFileDlg.h"
#include "afxdialogex.h"
#include <io.h>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;


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


// CMFCFileDlg 对话框



CMFCFileDlg::CMFCFileDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCFILE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCFileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_WRFILE_BTN, &CMFCFileDlg::OnBnClickedWrfileBtn)
	ON_BN_CLICKED(IDC_REFILE_BTN, &CMFCFileDlg::OnBnClickedRefileBtn)
END_MESSAGE_MAP()


// CMFCFileDlg 消息处理程序

BOOL CMFCFileDlg::OnInitDialog()
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

void CMFCFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCFileDlg::OnPaint()
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
HCURSOR CMFCFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCFileDlg::OnBnClickedWrfileBtn()
{
	// 1 C语言写文件
#if 0
	/*_ACRTIMP FILE* __cdecl fopen(
		_In_z_ char const* _FileName,
		_In_z_ char const* _Mode
	);*/

	FILE* pFile = fopen("1.txt", "a");
	if (pFile == NULL)
	{
		MessageBox("打开失败");
		return;
	}

	char szBuf[1024] = "C语言文件操作";
	
	/*
	fwrite

	ptr：指向要写入数据的内存区域的指针。
	size：每个元素的字节数大小。
	nmemb：要写入的元素数量。
	stream：一个指向FILE结构的指针，代表你要写入的文件。
	*/

	if (fwrite(szBuf, 1, strlen(szBuf) + 1, pFile) <= 0)
	{
		MessageBox("写入失败");
		return;
	}

	fclose(pFile);
#endif

	// 2 C++语言写文件
#if 0
	ofstream ofs("2.txt");
	char szBuf[1024] = "C++操作文件";
	ofs.write(szBuf, strlen(szBuf) + 1);
	ofs.close();
#endif 

	// 3 WIN32 API
#if 0
	HANDLE hFile;
	 
	/*
	"3.txt": 文件名。
	GENERIC_WRITE : 请求的访问权限，这里为写权限。
	NULL : 共享模式，NULL意味着不允许共享。
	NULL : 安全属性，NULL意味着使用默认安全属性。
	CREATE_NEW : 创建模式，CREATE_NEW意味着如果文件已存在则函数失败，否则创建新文件。
	FILE_ATTRIBUTE_NORMAL : 文件属性，FILE_ATTRIBUTE_NORMAL表示常规文件。
	NULL : 模板文件句柄，通常为NULL。
	*/
	hFile = CreateFile("3.txt", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox("创建文件对象失败");
		return;
	}

	DWORD dwWrite;
	char szBuf[1024] = "WIN API 操作文件";

/*
    hFile: 文件句柄。
    szBuf: 要写入的数据缓冲区。
    strlen(szBuf): 要写入的字节数，这里使用strlen计算字符串长度（不包括终止符\0）。
    &dwWrite: 写入操作的实际字节数将被写入此变量。
    NULL: 异步写入的事件句柄，此处为同步写入，所以为NULL。
*/
	WriteFile(hFile, szBuf, strlen(szBuf), &dwWrite, NULL);

	CloseHandle(hFile);
#endif 

	// 4 MFC
	CFile file("4.txt", CFile::modeCreate | CFile::modeWrite);
	char szBuf[1024] = "MFC --- ";
	file.Write(szBuf, strlen(szBuf));
	file.Close();
}

void CMFCFileDlg::OnBnClickedRefileBtn()
{
	// 1 C语言写文件
#if 0
	CString fileName = "1.txt";
	FILE* pFile = fopen(fileName, "r");
	if (pFile == NULL)
	{
		MessageBox("打开失败");
		return;
	}

	char szBuf[1024] = { 0 };

	fseek(pFile, 0, SEEK_END);		// fseek函数，移动到文件尾部。
	int iFileLen = ftell(pFile);	//得到文件指针的当前位置。
	
	fseek(pFile, 0, 0);

	int iLen = fread(szBuf, 1, iFileLen, pFile);

	fclose(pFile);
	MessageBox(szBuf, fileName, MB_OK);
#endif

	// 2 C++语言写文件
#if 0
	ifstream ifs("2.txt");
	char szBuf[1024] = {0};
	ifs.read(szBuf, sizeof(szBuf));
	ifs.close();
	MessageBox(szBuf, "2.txt", MB_OK);
#endif 

	// 3 WIN32 API
#if 0
	HANDLE hFile;
	hFile = CreateFile("3.txt", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox("创建文件对象失败");
		return;
	}

	DWORD dwRead;
	char szBuf[1024] = { 0 };

	ReadFile(hFile, szBuf, sizeof(szBuf), &dwRead, NULL);

	CloseHandle(hFile);

	MessageBox(szBuf, "3.txt", MB_OK);
#endif 

	// 4 MFC
	/*CFile file("4.txt", CFile::modeRead);
	char szBuf[1024] = { 0 };
	DWORD dwFileLen;
	dwFileLen = file.GetLength();
	file.Read(szBuf, dwFileLen);
	file.Close();
	MessageBox(szBuf, "4.txt", MB_OK);*/


	// MFC高阶操作
	CFileDialog fileDlg(TRUE);
	fileDlg.m_ofn.lpstrTitle = "Test";
	fileDlg.m_ofn.lpstrFilter = "Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";
	if (IDOK == fileDlg.DoModal())
	{
		CFile file(fileDlg.GetFileName(), CFile::modeRead);
		char szBuf[1024] = { 0 };
		DWORD dwFileLen;
		dwFileLen = file.GetLength();
		file.Read(szBuf, dwFileLen);
		file.Close();
		MessageBox(szBuf, "4.txt", MB_OK);
	}
}
