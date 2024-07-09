#include <windows.h>
#include <stdio.h>

void test_CreateProcess()
{
    WINBASEAPI
        BOOL
        WINAPI
        CreateProcessW(
            _In_opt_ LPCWSTR lpApplicationName, //NULL
            _Inout_opt_ LPWSTR lpCommandLine,
            _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
            _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
            _In_ BOOL bInheritHandles,
            _In_ DWORD dwCreationFlags,
            _In_opt_ LPVOID lpEnvironment,
            _In_opt_ LPCWSTR lpCurrentDirectory,
            _In_ LPSTARTUPINFOW lpStartupInfo,
            _Out_ LPPROCESS_INFORMATION lpProcessInformation
        );

    // 命令行 拉起网站。L"\"...\...\xxx.exe"..."
    TCHAR szCommandLine[] = L"\"C:\\Program Files\\Google\\Chrome\\Application\\Chrome.exe\"http://www.github.com/star-cs";

    STARTUPINFOW strStartupInfo;
    memset(&strStartupInfo, 0, sizeof(strStartupInfo));
    strStartupInfo.cb = sizeof(strStartupInfo);

    PROCESS_INFORMATION szProcessInformation;
    memset(&szProcessInformation, 0, sizeof(szProcessInformation));

    bool bRet = CreateProcess(NULL,
        szCommandLine,
        NULL,
        NULL,
        FALSE,                         //是否继承父进程的句柄
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &strStartupInfo,
        &szProcessInformation
    );

    if (bRet)
    {
        printf("Create Sucess bRet = %d\n", bRet);
        WaitForSingleObject(szProcessInformation.hThread, 3000);
        printf("Create Sucess szProcessInformation.hProcess = %d\n", szProcessInformation.hProcess);
        printf("Create Sucess szProcessInformation.hThread = %d\n", szProcessInformation.hThread);
        printf("Create Sucess szProcessInformation.dwProcessId = %d\n", szProcessInformation.dwProcessId);
        printf("Create Sucess szProcessInformation.dwThreadId = %d\n", szProcessInformation.dwThreadId);

        CloseHandle(szProcessInformation.hProcess);
        CloseHandle(szProcessInformation.hThread);
        szProcessInformation.hProcess = nullptr;
        szProcessInformation.hThread = nullptr;
        szProcessInformation.dwProcessId = 0;
        szProcessInformation.dwThreadId = 0;
    }
    else
    {
        printf("Create Failed bRet = %d，errorno = %d\n", bRet, GetLastError());
    }
}


int main()
{
    

    return 0;
}