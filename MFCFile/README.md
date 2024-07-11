# C���Բ����ļ�

## fopen �ļ���ģʽ
"r" (Read)����ֻ����ʽ���ļ���`�ļ��������`����������ʧ�ܲ�����NULL��

"w" (Write)����д�뷽ʽ���ļ�������ļ����ڣ������ݽ����ض����㳤�ȣ�`����д`��������ļ������ڣ����������ļ���

"a" (Append)����`׷��`��ʽ���ļ�������ļ����ڣ�д������ݽ�����ӵ��ļ�ĩβ������ļ������ڣ����������ļ���

"r+" (Read/Write)���Զ�д��ʽ���ļ����ļ�������ڣ���������ʧ�ܲ�����NULL��

"w+" (Write/Read)���Զ�д��ʽ���ļ�������ļ����ڣ������ݽ����ض����㳤�ȣ�`����д`��������ļ������ڣ����������ļ���

"a+" (Append/Read)���Զ�д��ʽ���ļ���������"a"ģʽ������Ҳ���Զ�ȡ�ļ����ݡ� 


# �����ļ�������ʽ
```c++
void CMFCFileDlg::OnBnClickedWrfileBtn()
{
	// 1 C����д�ļ�
#if 0
	/*_ACRTIMP FILE* __cdecl fopen(
		_In_z_ char const* _FileName,
		_In_z_ char const* _Mode
	);*/

	FILE* pFile = fopen("1.txt", "a");
	if (pFile == NULL)
	{
		MessageBox("��ʧ��");
		return;
	}

	char szBuf[1024] = "C�����ļ�����";
	
	/*
	fwrite

	ptr��ָ��Ҫд�����ݵ��ڴ������ָ�롣
	size��ÿ��Ԫ�ص��ֽ�����С��
	nmemb��Ҫд���Ԫ��������
	stream��һ��ָ��FILE�ṹ��ָ�룬������Ҫд����ļ���
	*/

	if (fwrite(szBuf, 1, strlen(szBuf) + 1, pFile) <= 0)
	{
		MessageBox("д��ʧ��");
		return;
	}

	fclose(pFile);
#endif

	// 2 C++����д�ļ�
#if 0
	ofstream ofs("2.txt");
	char szBuf[1024] = "C++�����ļ�";
	ofs.write(szBuf, strlen(szBuf) + 1);
	ofs.close();
#endif 

	// 3 WIN32 API
#if 0
	HANDLE hFile;
	 
	/*
	"3.txt": �ļ�����
	GENERIC_WRITE : ����ķ���Ȩ�ޣ�����ΪдȨ�ޡ�
	NULL : ����ģʽ��NULL��ζ�Ų�������
	NULL : ��ȫ���ԣ�NULL��ζ��ʹ��Ĭ�ϰ�ȫ���ԡ�
	CREATE_NEW : ����ģʽ��CREATE_NEW��ζ������ļ��Ѵ�������ʧ�ܣ����򴴽����ļ���
	FILE_ATTRIBUTE_NORMAL : �ļ����ԣ�FILE_ATTRIBUTE_NORMAL��ʾ�����ļ���
	NULL : ģ���ļ������ͨ��ΪNULL��
	*/
	hFile = CreateFile("3.txt", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox("�����ļ�����ʧ��");
		return;
	}

	DWORD dwWrite;
	char szBuf[1024] = "WIN API �����ļ�";

/*
    hFile: �ļ������
    szBuf: Ҫд������ݻ�������
    strlen(szBuf): Ҫд����ֽ���������ʹ��strlen�����ַ������ȣ���������ֹ��\0����
    &dwWrite: д�������ʵ���ֽ�������д��˱�����
    NULL: �첽д����¼�������˴�Ϊͬ��д�룬����ΪNULL��
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
	// 1 C����д�ļ�
#if 0
	CString fileName = "1.txt";
	FILE* pFile = fopen(fileName, "r");
	if (pFile == NULL)
	{
		MessageBox("��ʧ��");
		return;
	}

	char szBuf[1024] = { 0 };

	fseek(pFile, 0, SEEK_END);		// fseek�������ƶ����ļ�β����
	int iFileLen = ftell(pFile);	//�õ��ļ�ָ��ĵ�ǰλ�á�
	
	fseek(pFile, 0, 0);

	int iLen = fread(szBuf, 1, iFileLen, pFile);

	fclose(pFile);
	MessageBox(szBuf, fileName, MB_OK);
#endif

	// 2 C++����д�ļ�
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
		MessageBox("�����ļ�����ʧ��");
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


	// MFC�߽ײ���
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

```