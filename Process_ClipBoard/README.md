# ������ͨ��
```c++

void CProcessClipBoardDlg::OnBnClickedSendButton()
{
	// �򿪼�����
	if (OpenClipboard())
	{
		EmptyClipboard();
		char* szSendBuf;
		
		CString strSend;
		GetDlgItemTextA(IDC_EDIT_SEND, strSend);

		//�����ڴ�����ڴ����ľ������hclip��ָ��һ���ڴ�ռ䡣
		HANDLE hClip = GlobalAlloc(GMEM_MOVEABLE, strSend.GetLength() + 1);

		//����ȫ���ڴ�飬��ȡ���ַ����������ת��Ϊchar*
		szSendBuf = (char*)GlobalLock(hClip);

		//����strSend�е����ݵ�szSendBufָ����ڴ���
		strcpy(szSendBuf, strSend); 
		GlobalUnlock(hClip);

		SetClipboardData(CF_TEXT, hClip);

		CloseClipboard();
	}
}


void CProcessClipBoardDlg::OnBnClickedRecvButton()
{
	// ���ռ�����
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

