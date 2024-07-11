# ����Process

## CreateProcess

������ fork() + exec()

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

    lpApplicationName��Ҫִ�е�ģ�飨��ִ���ļ��������ơ�

    lpCommandLine�����ݸ��´������̵������С�����԰����κ� �����в��� ��

    lpProcessAttributes��ָ��SECURITY_ATTRIBUTES�ṹ��ָ�룬�ýṹȷ�����ص��½��̶������Ƿ���Ա��ӽ��̼̳С���˵�����ں˶���NULL��

    lpThreadAttributes����lpProcessAttributes���ƣ�������̶߳���

    bInheritHandles�������ֵΪTRUE�����½��̽��̳е��ý��̵����д򿪵ľ����

    dwCreationFlags��ָ���½��̵Ĵ�����־��������ֵ����CREATE_NEW_CONSOLE�������µĿ���̨���ڣ���CREATE_NO_WINDOW����ֹ�������ڣ���DETACHED_PROCESS���ӵ�ǰ��ҵ���������̣���

    lpEnvironment��ָ���½��̻������ָ�롣���ΪNULL�����½���ʹ�ø����̵Ļ�����

    lpCurrentDirectory���½��̵ĵ�ǰĿ¼������·�������ΪNULL�����½���ʹ�ø����̵ĵ�ǰĿ¼��

    lpStartupInfo��ָ��STARTUPINFO�ṹ��ָ�룬���������½��̵�������Ϣ�������̨���ڵĴ�С��λ�õȡ�

    lpProcessInformation��ָ��PROCESS_INFORMATION�ṹ��ָ�룬���ڽ����½��̵���Ϣ�������ID�����߳�ID��

# ���̼�ͨ�ŷ�ʽ

## 1 socket
    UDP TCP

## 2 ������
```c++
OpenClipboard();

EmptyClipboard();

SetClipboardData(CF_TEXT, hClip);   �ļ���ʽ��ָ��һ�������ڴ��ָ��

HANDLE hClip = GetClipboardData(CF_TEXT);   �õ�ָ�������ڴ��ָ��

CloseClipboard();
```

## 3 �ʲ�
    �з������Ϳͻ��˸�������ã����424�ֽڣ����ؽ��̼�ͨ�ţ�����ͨ��ʹ��UDP�����ɿ�����  
    `���򣬷���˽��գ��ͻ��˷���`��
```C++
//���ն� �����ʲ�

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
//���Ͷ� CreateFile����

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

## 4 �����ܵ�
    `���ӽ���֮���ͨ��`
```c++
//���������ܵ������ӽ��̡�

	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);

	if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0))			//1. CreatePipe
	{
		MessageBox(_T("�����ܵ�����ʧ��"));
		return;
	}

	//�����ӽ���
	STARTUPINFO strStartupInfo;									//��������ṹ���������½��̵�������Ϊ
	memset(&strStartupInfo, 0, sizeof(strStartupInfo));

	strStartupInfo.cb = sizeof(strStartupInfo);					//�ṹ��Ĵ�С�����뱻��ʼ��Ϊsizeof(STARTUPINFO)��
	strStartupInfo.dwFlags = STARTF_USESTDHANDLES;				//ָ����ν��ͽṹ���������Ա�����磬STARTF_USESHOWWINDOW���ƴ��������ʾ��STARTF_USESTDHANDLES�������ض����׼����/�����
	strStartupInfo.hStdInput = hReadPipe;
	strStartupInfo.hStdOutput = hWritePipe;
	strStartupInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);

	PROCESS_INFORMATION szProcessInformation;					//�洢��CreateProcess�����������½��̵���Ϣ
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
//���Ͷ�
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
//���ն�
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

## 5 �����ܵ� 
    Socket ���ƣ�֧������֮�䲻ͬ���̵�ͨ��
```c++
	//���� �����ܵ�
	LPCTSTR szPipeName = TEXT("\\\\.\\pipe\\myPipe");	//���ʲ�����

	//PIPE_ACCESS_DUPLEX ȫ˫�� �� FILE_FLAG_OVERLAPPED�첽  ��ͨ�� �� PIPE_TYPE_BYTE �ֽ���
	hNamedPipe = CreateNamedPipe(szPipeName, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,		//1. CreateNamedPipe
		PIPE_TYPE_BYTE, 1, 1024, 1024, 0, NULL);

	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		TRACE("CreateNamePipe failed with &d\n", GetLastError());
		MessageBox(_T("���������ܵ�ʧ��"));
		return;
	}

	//�ֶ�����
	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);									//2. CreateEvent
	if (NULL == hEvent)
	{
		MessageBox(_T("�����¼�ʧ��"));
		CloseHandle(hNamedPipe);
		hNamedPipe = NULL;
		return;
	}

	// �����첽 I/O �����Ľṹ��
	
	/*OVERLAPPED�ṹ���Ա
	Internal: ��ϵͳʹ�õ��ڲ�ָ�롣
	InternalHigh : ��һ����ϵͳʹ�õ��ڲ�ָ�롣
	Offset : �ļ�ƫ�����ĵ�32λ�������첽�ļ�������
	OffsetHigh : �ļ�ƫ�����ĸ�32λ��
	Pointer : Ӧ�ó������ָ�룬����ָ���κ����ݽṹ���繤�������������Ϣ��
	hEvent : һ���¼������I / O ���ʱ�ᱻ�ź������á�*/

	OVERLAPPED ovlap;
	ZeroMemory(&ovlap, sizeof(OVERLAPPED));
	ovlap.hEvent = hEvent;

	if (!ConnectNamedPipe(hNamedPipe, &ovlap))												//3. ConnectNamedPipe
	{
		if (ERROR_IO_PENDING != GetLastError())
		{
			MessageBox(_T("�ȴ��ͻ�������ʧ��"));
			CloseHandle(hNamedPipe);
			CloseHandle(hEvent);
			hNamedPipe = NULL;
			hEvent = NULL;
			return;
		}
	}	
	if (WaitForSingleObject(hEvent, INFINITE) == WAIT_FAILED)								//4. WaitForSingleObject
	{
		MessageBox(_T("�ȴ�����ʧ��"));
		CloseHandle(hNamedPipe);
		CloseHandle(hEvent);
		hNamedPipe = NULL;
		hEvent = NULL;
		return;
	}
```

```c++
//���������ܵ�
	LPCTSTR szNamedPipeName = TEXT("\\\\.\\pipe\\myPipe");

	if (0 == WaitNamedPipe(szNamedPipeName, NMPWAIT_WAIT_FOREVER))
	{
		MessageBox(_T("��ǰû�п������õĹܵ�"));
		return;
	}

	HANDLE hNamedPipe = CreateFile(szNamedPipeName, GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		TRACE("CreateFile Failed with %d\n", GetLastError());
		MessageBox(_T("�������ܵ�ʧ�ܣ�"));
		hNamedPipe = NULL;
		return;
	}
```

```c++
//���Ͷ�
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
//���ն�
	char szBuf[100] = { 0 };
	DWORD dwRead;
	TRACE("Begin ReadFile");
	if (!ReadFile(hNamedPipe, szBuf, 100, &dwRead, NULL))
	{
		MessageBox(_T("��ȡ����ʧ��"));
		CloseHandle(hNamedPipe);
		return;
	}
	MessageBox(szBuf);
	CloseHandle(hNamedPipe);
```

## 6 Copy_data findwindows wm_copydata  ��Ϣ Sendmessage ��MFC����ã�����Ҫ����ֻ���õ����ھ����
```c++
	//���Ͷ�
	CString strWindowsTitle = _T("�����");
	CString strMsg = _T("COPYDATA");
	// ���ñ����õ����
	HWND hWnd = ::FindWindow(NULL, strWindowsTitle.GetBuffer(0));									//1. ::FindWindow

	if (hWnd != NULL && IsWindow(hWnd))
	{
		//���ݵķ�װ
		COPYDATASTRUCT cpd;
		cpd.dwData = 0;
		cpd.cbData = strMsg.GetLength() * sizeof(TCHAR);	//��С
		cpd.lpData = (PVOID)strMsg.GetBuffer(0);			//ָ��

		//hWnd ���ն�
		//AfxGetApp()->m_pMainWnd �� MFC �����ڻ�ȡӦ�ó��������ھ���ı��ʽ (������Դ)
		//(LPARAM)&cpd: ���� lParam ��������������һ��ָ�� COPYDATASTRUCT �ṹ��ָ�롣cpd ������ COPYDATASTRUCT ���ͣ������������ݵĴ�С�����ݱ���

		::SendMessage(hWnd, WM_COPYDATA, (WPARAM)(AfxGetApp()->m_pMainWnd), (LPARAM)&cpd);			//2. ::SendMessage
	}		
	strWindowsTitle.ReleaseBuffer();
	strMsg.ReleaseBuffer();
```

```c++
	//����һ�������źţ�����CopyData��Ϣ

BOOL CProcessCommunityDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	//����CopyData��Ϣ
	LPCTSTR szText = (LPCTSTR)(pCopyDataStruct->lpData);
	DWORD dwLength = (DWORD)pCopyDataStruct->cbData;
	TCHAR szRecvText[1024] = { 0 };
	memcpy(szRecvText, szText, dwLength);
	//szRecvText Ӧ������Ϣ�ı����� _T("Y") Ӧ���Ǳ����ı���MB_OK ������Ϣ��İ�ť����ʽ��־
	MessageBox(szRecvText, _T("Y"), MB_OK);
	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}
```


# ͨ�ŷ�ʽ�ıȽ�
1. ���а�������ܵ�ֻ��ʵ��`ͬһ��������������ͨ��`��������ʵ���������֮���ͨ�š�
2. �ʲ��ǻ��ڹ㲥�ģ�����һ�Զ෢�͡���ֻ��һ�����ͣ�һ�����գ�Ҫ��ͬʱ���ͽ��գ���д���δ��롣�ʲ۵�ȱ�㴫�����������С424 �ֽ����¡�
3. �����ܵ����ʲۿ��Խ�������ͨ�š�`�����ܵ�ֻ���ǵ�Ե�ĵ�һͨ��`��
4. WM_COPY_DATA ��װ���ݺͽ������ݡ��ǳ����㡣����������󣬽����������ܵ���  



# �����ܵ� �����ܵ�

�����ܵ���ͨ���� Unix/Linux ϵͳ�г�Ϊ�����ܵ��� FIFO �ܵ����������ܵ��ڸ�����������֮���������ǵ�ʹ�÷�ʽ����Ϊ������ͬ��

�� Unix/Linux ϵͳ�У������ܵ���ͨ�� pipe() ϵͳ���ô����ģ���������һ��������ļ���������һ������д�루ͨ��Ϊ 1������һ�����ڶ�ȡ��ͨ��Ϊ 0�������ֹܵ��������ڴ��У�ͨ�����ڽ��̼�ͨ�ţ�IPC�����ر��Ǹ��ӽ���֮���ͨ�š������ܵ����ص��ǰ�˫����Ҳ����˵������ֻ����һ������������������д�˵����ˡ�

����ʹ�������ܵ�ʱ��ͨ����Ҫ�����н����ڶ��˵ȴ���Ȼ����ܴ�д�˷������ݡ�������Ϊ�����ܵ������Ƚ��ȳ���FIFO�������ԣ����д����û���κν��̶�ȡ������·������ݣ����ݿ��ܻᱻ����������ܵ����������ˣ�����д����������ֱ���ж�ȡ������ܵ����������㹻�Ŀռ䣩��

Ȼ�����Ⲣ����ζ��������ڷ�������ǰʼ�յȴ����շ����������д��ʹ�÷�����ģʽ������д�������������������������أ�����ܵ����������򷵻�һ������ͨ���� EAGAIN �� EWOULDBLOCK�����������ͷ�������ȴ����շ�������¼���ִ����������

�� Windows ϵͳ�У������ܵ��ṩ�˸����ӵ����ԣ�����ȫ˫��ͨ�ź��첽 I/O ֧�֣���ʹ�������ڹ������� Unix/Linux ϵͳ�е��׽��ָ��ӽ��������ܵ�����ͬʱ��д�����ҿ���ͨ���ʵ�������֧�ֶ�·ͨ�š�

��֮�������ܵ��� Unix/Linux ϵͳ��ͨ���ǰ�˫���ģ���Ҫ�ж��˵ȴ�������Ч�������ݣ��������ͨ��ʹ�÷�����ģʽ���������� Windows ϵͳ�У������ܵ��ṩ�˸��߼��Ĺ��ܣ�����ȫ˫��ͨ�ź��첽������


