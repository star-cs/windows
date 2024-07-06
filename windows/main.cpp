#include <windows.h>
#include <stdio.h>

LPCTSTR clsName = "My";
LPCTSTR msgName = "欢迎学习win32";

LRESULT CALLBACK MyWinProc(
    HWND hwnd,          //窗口的句柄
    UINT uMsg,          //消息
    WPARAM wParam,      //其他消息信息    wParam 参数的内容取决于 uMsg 参数的值。
    LPARAM lParam       //其他消息信息    lParam 参数的内容取决于 uMsg 参数的值。
);

// a设计一个窗口类 b注册窗口类 c创建窗口 d显示以及更新窗口 e循环等待消息


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

    //a设计一个窗口类
    // 1 定义和配置窗口对象
    //https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/ns-winuser-wndclassa
    WNDCLASS wndcls;    //包含由 RegisterClass 函数注册的窗口类属性。
    wndcls.cbClsExtra = NULL;   //要根据窗口类结构分配的额外字节数。 系统将字节初始化为零。
    wndcls.cbWndExtra = NULL;   //在窗口实例之后分配的额外字节数。 系统将字节初始化为零。 如果应用程序使用 WNDCLASS 注册使用资源文件中的 CLASS 指令创建的对话框，则必须将此成员设置为 DLGWINDOWEXTRA。
    wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //类背景画笔的句柄。 
    wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);  //类游标的句柄。就是鼠标光标
    wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION); //图标
    wndcls.hInstance = hInstance;   //实例
    //定义交互响应
    wndcls.lpfnWndProc = MyWinProc; //指向窗口过程的指针
    //定义窗口代号
    wndcls.lpszClassName = clsName; //窗口类名
    wndcls.lpszMenuName = NULL; //类菜单的资源名称。NULL，则属于此类的窗口没有默认菜单。
    wndcls.style = CS_HREDRAW | CS_VREDRAW; //窗口类样式

    //b注册窗口类
    RegisterClass(&wndcls);

    //c创建窗口
    HWND hwnd;
    hwnd = CreateWindow(clsName, msgName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    //d显示以及更新窗口
    ShowWindow(hwnd , SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    //e消息循环
    //GetMessage只有在接收到WM_QUIT才会返回0
    //TranslateMessage翻译消息，WM_KEYDOWN和WM_KEYUP合并为WM_CHAR的消息。
    MSG msg;
    while (GetMessage(&msg, NULL, NULL, NULL))  
    {
        TranslateMessage(&msg); 
        DispatchMessage(&msg);
    }

    return msg.wParam;

}


LRESULT CALLBACK MyWinProc(
    HWND hwnd,          //窗口的句柄
    UINT uMsg,          //消息
    WPARAM wParam,      //其他消息信息    wParam 参数的内容取决于 uMsg 参数的值。
    LPARAM lParam       //其他消息信息    lParam 参数的内容取决于 uMsg 参数的值。
)
{
    //uMsg消息类型
    int ret;
    HDC hdc;
    switch (uMsg)
    {
    case WM_CHAR:
        char szChar[20];
        sprintf_s(szChar, "您刚才按下了：%c", wParam);
        MessageBox(hwnd, szChar, "char", NULL);
        break;

    case WM_LBUTTONDOWN:
        MessageBox(hwnd, "检测鼠标左键按下了", "msg", NULL);
        break;

    case WM_PAINT:
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwnd, &ps);
        TextOut(hdc, 0, 0, "www.baidu.com", strlen("www.baidu.com"));
        EndPaint(hwnd, &ps);
        MessageBox(hwnd, "重绘", "msg", NULL);
        break;

    case WM_CLOSE:
        ret = MessageBox(hwnd, "是否真的结束？", "msg", MB_YESNO);
        if (ret == IDYES)
        {
            DestroyWindow(hwnd);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);     //发送WM_QUIT
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}