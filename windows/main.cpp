#include <windows.h>
#include <stdio.h>

LPCTSTR clsName = "My";
LPCTSTR msgName = "��ӭѧϰwin32";

LRESULT CALLBACK MyWinProc(
    HWND hwnd,          //���ڵľ��
    UINT uMsg,          //��Ϣ
    WPARAM wParam,      //������Ϣ��Ϣ    wParam ����������ȡ���� uMsg ������ֵ��
    LPARAM lParam       //������Ϣ��Ϣ    lParam ����������ȡ���� uMsg ������ֵ��
);

// a���һ�������� bע�ᴰ���� c�������� d��ʾ�Լ����´��� eѭ���ȴ���Ϣ


int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd
)
{
    /*UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCWSTR     lpszMenuName;
    LPCWSTR     lpszClassName;*/

    //a���һ��������
    // 1 ��������ô��ڶ���
    //https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/ns-winuser-wndclassa
    WNDCLASS wndcls;    //������ RegisterClass ����ע��Ĵ��������ԡ�
    wndcls.cbClsExtra = NULL;   //Ҫ���ݴ�����ṹ����Ķ����ֽ����� ϵͳ���ֽڳ�ʼ��Ϊ�㡣
    wndcls.cbWndExtra = NULL;   //�ڴ���ʵ��֮�����Ķ����ֽ����� ϵͳ���ֽڳ�ʼ��Ϊ�㡣 ���Ӧ�ó���ʹ�� WNDCLASS ע��ʹ����Դ�ļ��е� CLASS ָ����ĶԻ�������뽫�˳�Ա����Ϊ DLGWINDOWEXTRA��
    wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //�౳�����ʵľ���� 
    wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);  //���α�ľ�������������
    wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION); //ͼ��
    wndcls.hInstance = hInstance;   //ʵ��
    //���彻����Ӧ
    wndcls.lpfnWndProc = MyWinProc; //ָ�򴰿ڹ��̵�ָ��
    //���崰�ڴ���
    wndcls.lpszClassName = clsName; //��������
    wndcls.lpszMenuName = NULL; //��˵�����Դ���ơ�NULL�������ڴ���Ĵ���û��Ĭ�ϲ˵���
    wndcls.style = CS_HREDRAW | CS_VREDRAW; //��������ʽ

    //bע�ᴰ����
    RegisterClass(&wndcls);

    //c��������
    HWND hwnd;
    hwnd = CreateWindow(clsName, msgName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    //d��ʾ�Լ����´���
    ShowWindow(hwnd , SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    //e��Ϣѭ��
    //GetMessageֻ���ڽ��յ�WM_QUIT�Ż᷵��0
    //TranslateMessage������Ϣ��WM_KEYDOWN��WM_KEYUP�ϲ�ΪWM_CHAR����Ϣ��
    MSG msg;
    while (GetMessage(&msg, NULL, NULL, NULL))  
    {
        TranslateMessage(&msg); 
        DispatchMessage(&msg);
    }

    return msg.wParam;

}


LRESULT CALLBACK MyWinProc(
    HWND hwnd,          //���ڵľ��
    UINT uMsg,          //��Ϣ
    WPARAM wParam,      //������Ϣ��Ϣ    wParam ����������ȡ���� uMsg ������ֵ��
    LPARAM lParam       //������Ϣ��Ϣ    lParam ����������ȡ���� uMsg ������ֵ��
)
{
    //uMsg��Ϣ����
    int ret;
    HDC hdc;
    switch (uMsg)
    {
    case WM_CHAR:
        char szChar[20];
        sprintf_s(szChar, "���ղŰ����ˣ�%c", wParam);
        MessageBox(hwnd, szChar, "char", NULL);
        break;

    case WM_LBUTTONDOWN:
        MessageBox(hwnd, "���������������", "msg", NULL);
        break;

    case WM_PAINT:
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwnd, &ps);
        TextOut(hdc, 0, 0, "www.baidu.com", strlen("www.baidu.com"));
        EndPaint(hwnd, &ps);
        MessageBox(hwnd, "�ػ�", "msg", NULL);
        break;

    case WM_CLOSE:
        ret = MessageBox(hwnd, "�Ƿ���Ľ�����", "msg", MB_YESNO);
        if (ret == IDYES)
        {
            DestroyWindow(hwnd);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);     //����WM_QUIT
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}