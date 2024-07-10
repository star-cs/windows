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

    lpCommandLine�����ݸ��´������̵������С�����԰����κ������в�����

    lpProcessAttributes��ָ��SECURITY_ATTRIBUTES�ṹ��ָ�룬�ýṹȷ�����ص��½��̶������Ƿ���Ա��ӽ��̼̳С���˵�����ں˶���NULL��

    lpThreadAttributes����lpProcessAttributes���ƣ�������̶߳���

    bInheritHandles�������ֵΪTRUE�����½��̽��̳е��ý��̵����д򿪵ľ����

    dwCreationFlags��ָ���½��̵Ĵ�����־��������ֵ����CREATE_NEW_CONSOLE�������µĿ���̨���ڣ���CREATE_NO_WINDOW����ֹ�������ڣ���DETACHED_PROCESS���ӵ�ǰ��ҵ���������̣���

    lpEnvironment��ָ���½��̻������ָ�롣���ΪNULL�����½���ʹ�ø����̵Ļ�����

    lpCurrentDirectory���½��̵ĵ�ǰĿ¼������·�������ΪNULL�����½���ʹ�ø����̵ĵ�ǰĿ¼��

    lpStartupInfo��ָ��STARTUPINFO�ṹ��ָ�룬���������½��̵�������Ϣ�������̨���ڵĴ�С��λ�õȡ�

    lpProcessInformation��ָ��PROCESS_INFORMATION�ṹ��ָ�룬���ڽ����½��̵���Ϣ�������ID�����߳�ID��

# ���̼�ͨ�ŷ�ʽ

1 socket

2 ������

3 �ʲ�
    �з������Ϳͻ��˸���

4 �����ܵ�
    ���ӽ���֮���ͨ��

5 �����ܵ� 
    Socket ���ƣ�֧������֮�䲻ͬ���̵�ͨ��

6 Copy_data findwindows wm_copydata  ��Ϣ Sendmessage

