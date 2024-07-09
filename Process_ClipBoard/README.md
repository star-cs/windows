# 剪贴板通信
```c++

void CProcessClipBoardDlg::OnBnClickedSendButton()
{
	// 打开剪贴板
	if (OpenClipboard())
	{
		EmptyClipboard();
		char* szSendBuf;
		
		CString strSend;
		GetDlgItemTextA(IDC_EDIT_SEND, strSend);

		//分配内存对象，内存对象的句柄就是hclip，指向一块内存空间。
		HANDLE hClip = GlobalAlloc(GMEM_MOVEABLE, strSend.GetLength() + 1);

		//锁定全局内存块，获取其地址并将其类型转换为char*
		szSendBuf = (char*)GlobalLock(hClip);

		//复制strSend中的内容到szSendBuf指向的内存中
		strcpy(szSendBuf, strSend); 
		GlobalUnlock(hClip);

		SetClipboardData(CF_TEXT, hClip);

		CloseClipboard();
	}
}


void CProcessClipBoardDlg::OnBnClickedRecvButton()
{
	// 接收剪贴板
	if (OpenClipboard())
	{
		if (IsClipboardFormatAvailable(CF_TEXT))
		{
			char* szRecvBuf;
			HANDLE hClip = GetClipboardData(CF_TEXT);

			szRecvBuf = (char*)GlobalLock(hClip);
			
			SetDlgItemTextA(IDC_EDIT_RECV, szRecvBuf);

			GlobalUnlock(hClip);
		}
		CloseClipboard();
	}
}
```

