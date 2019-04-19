#include<windows.h>
#include<stdio.h>

LRESULT CALLBACK WinSunProc(
	HWND hwnd, //handle to window 窗口的句柄
	UINT uMsg, //message identifier 消息标识符
	WPARAM wParam, //first message parameter 第一个消息参数
	LPARAM lParam   //second message parameter 第二个消息参数
);  //回调函数


//写程序的入口点函数
int WINAPI WinMain(
	HINSTANCE hInstance,                         //handle to current instance 处理当前实例
	HINSTANCE hPrevInstance,                     //handle to previous instance 处理上一个实例
	LPSTR lpCmdLine,                             //commannd line 命令行
	int nShowCmd                                 //show state显示状态，说明主应用程序窗口是最小化，最大化还是正常显示
)

{
	WNDCLASS wndcls;          //实例化
	wndcls.cbClsExtra = 0;    //额外的类的附加字节数
	wndcls.cbWndExtra = 0;    //窗口额外的附加字节数

	//HGDIOBJ GetStockObject(int fnObject);检索预定义的备用笔、刷子、字体或者调色板的句柄
	//BLACK_BRUSH 指黑色画刷
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);     //背景颜色，GetStockObject()函数的返回值是一个HGDIOBJ格式的，强制转换成HBRUSH格式的赋值

	//LoadCursor载入指定的光标类型
	//原形：HCURSOR LoadCursor(HINSTANCE hlnstance，LPCTSTR lpCursorName);
	//hlnstance标识一个模块事例，它的可执行文件包含要载入的光标,lpCursorName光标资源名
	wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);                   //光标的类型 IDC_CROSS代表十字光标

	// LoadIcon函数已经被LoadImage替代
	wndcls.hIcon = LoadIcon(NULL, IDI_ERROR);        //图标
	wndcls.hInstance = hInstance;                    //应用程序的实例号
	wndcls.lpfnWndProc = WinSunProc;                 //窗口过程函数
	wndcls.lpszClassName = "热爱游戏";               //类名
	wndcls.lpszMenuName = NULL;                      //菜单名
	wndcls.style = CS_HREDRAW | CS_VREDRAW;          //水平重画和垂直重画

	RegisterClass(&wndcls);                          //注册窗口类

	HWND hwnd;                                      //实例化一个句柄

	//建立一个窗口
	hwnd = CreateWindow("热爱游戏", "我喜欢玩儿游戏！！！", WS_OVERLAPPEDWINDOW, 0, 0, 600, 400, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);                //显示窗口
	UpdateWindow(hwnd);  //更新窗口
	MSG msg;   //消息机制
	while (GetMessage(&msg, NULL, 0, 0))            //消息循环
	{
		TranslateMessage(&msg);                     //将传来的消息翻译
		DispatchMessage(&msg);                      //消息派遣
	}
	return 0;
}



LRESULT CALLBACK WinSunProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)

{
	switch (uMsg) {
	case WM_CHAR:
		char szChar[20];
		sprintf_s(szChar, "char is %d", wParam);                    //sprintf_s和sprintf的区别
		MessageBox(hwnd, szChar, "游戏", 0);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, "mouse clicked", "游戏", 0);
		HDC hdc;
		hdc = GetDC(hwnd);
		TextOut(hdc, 0, 50, "我为游戏狂", strlen("我为游戏狂"));
		ReleaseDC(hwnd, hdc);
		break;

	case WM_PAINT:
		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hwnd, &ps);
		TextOut(hDC, 0, 0, "我喜欢玩儿黑暗之魂3", strlen("我喜欢玩儿黑暗之魂3"));
		EndPaint(hwnd, &ps);
		break;

	case WM_CLOSE:
		if (IDYES == MessageBox(hwnd, "是否真的结束？", "游戏", MB_YESNO))
		{
			DestroyWindow(hwnd);                                    //销毁窗口
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}