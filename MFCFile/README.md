# C语言操作文件

## fopen 文件打开模式
"r" (Read)：以只读方式打开文件。`文件必须存在`，否则函数将失败并返回NULL。

"w" (Write)：以写入方式打开文件。如果文件存在，其内容将被截断至零长度（`重新写`）；如果文件不存在，将创建新文件。

"a" (Append)：以`追加`方式打开文件。如果文件存在，写入的数据将被添加到文件末尾；如果文件不存在，将创建新文件。

"r+" (Read/Write)：以读写方式打开文件。文件必须存在，否则函数将失败并返回NULL。

"w+" (Write/Read)：以读写方式打开文件。如果文件存在，其内容将被截断至零长度（`重新写`）；如果文件不存在，将创建新文件。

"a+" (Append/Read)：以读写方式打开文件，类似于"a"模式，但是也可以读取文件内容。 


# 四种文件操作方式
```c++
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

```