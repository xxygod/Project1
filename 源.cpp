#include<windows.h>
#include<stdio.h>

LRESULT CALLBACK WinSunProc(
	HWND hwnd, //handle to window ���ڵľ��
	UINT uMsg, //message identifier ��Ϣ��ʶ��
	WPARAM wParam, //first message parameter ��һ����Ϣ����
	LPARAM lParam   //second message parameter �ڶ�����Ϣ����
);  //�ص�����


//д�������ڵ㺯��
int WINAPI WinMain(
	HINSTANCE hInstance,                         //handle to current instance ����ǰʵ��
	HINSTANCE hPrevInstance,                     //handle to previous instance ������һ��ʵ��
	LPSTR lpCmdLine,                             //commannd line ������
	int nShowCmd                                 //show state��ʾ״̬��˵����Ӧ�ó��򴰿�����С������󻯻���������ʾ
)

{
	WNDCLASS wndcls;          //ʵ����
	wndcls.cbClsExtra = 0;    //�������ĸ����ֽ���
	wndcls.cbWndExtra = 0;    //���ڶ���ĸ����ֽ���

	//HGDIOBJ GetStockObject(int fnObject);����Ԥ����ı��ñʡ�ˢ�ӡ�������ߵ�ɫ��ľ��
	//BLACK_BRUSH ָ��ɫ��ˢ
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);     //������ɫ��GetStockObject()�����ķ���ֵ��һ��HGDIOBJ��ʽ�ģ�ǿ��ת����HBRUSH��ʽ�ĸ�ֵ

	//LoadCursor����ָ���Ĺ������
	//ԭ�Σ�HCURSOR LoadCursor(HINSTANCE hlnstance��LPCTSTR lpCursorName);
	//hlnstance��ʶһ��ģ�����������Ŀ�ִ���ļ�����Ҫ����Ĺ��,lpCursorName�����Դ��
	wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);                   //�������� IDC_CROSS����ʮ�ֹ��

	// LoadIcon�����Ѿ���LoadImage���
	wndcls.hIcon = LoadIcon(NULL, IDI_ERROR);        //ͼ��
	wndcls.hInstance = hInstance;                    //Ӧ�ó����ʵ����
	wndcls.lpfnWndProc = WinSunProc;                 //���ڹ��̺���
	wndcls.lpszClassName = "�Ȱ���Ϸ";               //����
	wndcls.lpszMenuName = NULL;                      //�˵���
	wndcls.style = CS_HREDRAW | CS_VREDRAW;          //ˮƽ�ػ��ʹ�ֱ�ػ�

	RegisterClass(&wndcls);                          //ע�ᴰ����

	HWND hwnd;                                      //ʵ����һ�����

	//����һ������
	hwnd = CreateWindow("�Ȱ���Ϸ", "��ϲ�������Ϸ������", WS_OVERLAPPEDWINDOW, 0, 0, 600, 400, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);                //��ʾ����
	UpdateWindow(hwnd);  //���´���
	MSG msg;   //��Ϣ����
	while (GetMessage(&msg, NULL, 0, 0))            //��Ϣѭ��
	{
		TranslateMessage(&msg);                     //����������Ϣ����
		DispatchMessage(&msg);                      //��Ϣ��ǲ
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
		sprintf_s(szChar, "char is %d", wParam);                    //sprintf_s��sprintf������
		MessageBox(hwnd, szChar, "��Ϸ", 0);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, "mouse clicked", "��Ϸ", 0);
		HDC hdc;
		hdc = GetDC(hwnd);
		TextOut(hdc, 0, 50, "��Ϊ��Ϸ��", strlen("��Ϊ��Ϸ��"));
		ReleaseDC(hwnd, hdc);
		break;

	case WM_PAINT:
		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hwnd, &ps);
		TextOut(hDC, 0, 0, "��ϲ������ڰ�֮��3", strlen("��ϲ������ڰ�֮��3"));
		EndPaint(hwnd, &ps);
		break;

	case WM_CLOSE:
		if (IDYES == MessageBox(hwnd, "�Ƿ���Ľ�����", "��Ϸ", MB_YESNO))
		{
			DestroyWindow(hwnd);                                    //���ٴ���
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