#include <Windows.h>
#include "resource.h"
#include <atlstr.h>
#include <thread>
#include <fstream>
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")	//����UI		//Change UI

CString version = L"TheClicker1.1";
CString add = L"https://github.com/JuAXi/TheClicker";

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define KEY_UP(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 0:1)

#define BUTTON1 5336
#define BUTTON2 5337
#define BUTTON3 5338
#define BUTTON4 5339
#define BUTTON_SURE 5340
#define BUTTON_SELECT_KEY 5341
#define BUTTON_CANCEL 5342
#define Input_Time 5343
#define Output_Name 5344
#define Input_Name 5345
#define BUTTON_OUTPUT 5346
#define BUTTON_INPUT 5347

#define minutes 60
#define time_interval 10
#define total_times minutes * 60 * (1000 / time_interval)

bool input_success = false;

struct Press
{
	int time;
	int key;
	Press* next = NULL;
};

int key_click = 1;
Press* key_press_head, * p_key_press0, * p_key_press1;
int count;
int click_count = 0;
bool* i_down;
POINT* point;
CString now_key_click = TEXT("��ǰ����Ϊ��");

const HFONT font = CreateFont(18, 9, 0, 0, 600, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"����");

void GetKey()
{
	bool is_continue = true;
	while (is_continue)
	{
		for (int i = 0; i < 254; i++)
		{
			if ((i < 3) || (i > 7 && i < 10) || (i > 11 && i < 14) || (i > 19 && i < 21) || (i > 31 && i < 58) || (i > 54 && i < 94) || (i > 94 && i < 124) || (i > 143 && i < 146) || (i > 159 && i < 166) || (i > 172 && i < 176) || (i > 185 && i < 223))
			{
				if (KEY_DOWN(i) == true)
				{
					key_click = i;
					is_continue = false;
					break;
				}
			}
			else
				continue;
		}
	}
	HWND tips = FindWindow(L"Tips", NULL);
	SendMessage(tips, WM_CLOSE, NULL, NULL);
}

void SetNowKeyClick()
{
	switch (key_click)
	{
	case 1:
		now_key_click = TEXT("��ǰ����Ϊ��LButton");
		now_key_click.ReleaseBuffer();
		break;
	case 2:
		now_key_click = TEXT("��ǰ����Ϊ��RButton");
		now_key_click.ReleaseBuffer();
		break;
	case 8:
		now_key_click = TEXT("��ǰ����Ϊ��Back");
		now_key_click.ReleaseBuffer();
		break;
	case 9:
		now_key_click = TEXT("��ǰ����Ϊ��Tab");
		now_key_click.ReleaseBuffer();
		break;
	case 12:
		now_key_click = TEXT("��ǰ����Ϊ��Clear");
		now_key_click.ReleaseBuffer();
		break;
	case 13:
		now_key_click = TEXT("��ǰ����Ϊ��Enter");
		now_key_click.ReleaseBuffer();
		break;
	case 19:
		now_key_click = TEXT("��ǰ����Ϊ��Pause");
		now_key_click.ReleaseBuffer();
		break;
	case 20:
		now_key_click = TEXT("��ǰ����Ϊ��Caps Lock");
		now_key_click.ReleaseBuffer();
		break;
	case 32:
		now_key_click = TEXT("��ǰ����Ϊ��Space");
		now_key_click.ReleaseBuffer();
		break;
	case 33:
		now_key_click = TEXT("��ǰ����Ϊ��Page Up");
		now_key_click.ReleaseBuffer();
		break;
	case 34:
		now_key_click = TEXT("��ǰ����Ϊ��Page Down");
		now_key_click.ReleaseBuffer();
		break;
	case 35:
		now_key_click = TEXT("��ǰ����Ϊ��End");
		now_key_click.ReleaseBuffer();
		break;
	case 36:
		now_key_click = TEXT("��ǰ����Ϊ��Home");
		now_key_click.ReleaseBuffer();
		break;
	case 37:
		now_key_click = TEXT("��ǰ����Ϊ��Left Arrow");
		now_key_click.ReleaseBuffer();
		break;
	case 38:
		now_key_click = TEXT("��ǰ����Ϊ��Up Arrow");
		now_key_click.ReleaseBuffer();
		break;
	case 39:
		now_key_click = TEXT("��ǰ����Ϊ��Right Arrow");
		now_key_click.ReleaseBuffer();
		break;
	case 40:
		now_key_click = TEXT("��ǰ����Ϊ��Down Arrow");
		now_key_click.ReleaseBuffer();
		break;
	case 41:
		now_key_click = TEXT("��ǰ����Ϊ��Select");
		now_key_click.ReleaseBuffer();
		break;
	case 42:
		now_key_click = TEXT("��ǰ����Ϊ��Print");
		now_key_click.ReleaseBuffer();
		break;
	case 43:
		now_key_click = TEXT("��ǰ����Ϊ��Excute");
		now_key_click.ReleaseBuffer();
		break;
	case 44:
		now_key_click = TEXT("��ǰ����Ϊ��Snapshot");
		now_key_click.ReleaseBuffer();
		break;
	case 45:
		now_key_click = TEXT("��ǰ����Ϊ��Insert");
		now_key_click.ReleaseBuffer();
		break;
	case 46:
		now_key_click = TEXT("��ǰ����Ϊ��Delete");
		now_key_click.ReleaseBuffer();
		break;
	case 47:
		now_key_click = TEXT("��ǰ����Ϊ��Help");
		now_key_click.ReleaseBuffer();
		break;
	case 48:
		now_key_click = TEXT("��ǰ����Ϊ��0");
		now_key_click.ReleaseBuffer();
		break;
	case 49:
		now_key_click = TEXT("��ǰ����Ϊ��1");
		now_key_click.ReleaseBuffer();
		break;
	case 50:
		now_key_click = TEXT("��ǰ����Ϊ��2");
		now_key_click.ReleaseBuffer();
		break;
	case 51:
		now_key_click = TEXT("��ǰ����Ϊ��3");
		now_key_click.ReleaseBuffer();
		break;
	case 52:
		now_key_click = TEXT("��ǰ����Ϊ��4");
		now_key_click.ReleaseBuffer();
		break;
	case 53:
		now_key_click = TEXT("��ǰ����Ϊ��5");
		now_key_click.ReleaseBuffer();
		break;
	case 54:
		now_key_click = TEXT("��ǰ����Ϊ��6");
		now_key_click.ReleaseBuffer();
		break;
	case 55:
		now_key_click = TEXT("��ǰ����Ϊ��7");
		now_key_click.ReleaseBuffer();
		break;
	case 56:
		now_key_click = TEXT("��ǰ����Ϊ��8");
		now_key_click.ReleaseBuffer();
		break;
	case 57:
		now_key_click = TEXT("��ǰ����Ϊ��9");
		now_key_click.ReleaseBuffer();
		break;
	case 65:
		now_key_click = TEXT("��ǰ����Ϊ��A");
		now_key_click.ReleaseBuffer();
		break;
	case 66:
		now_key_click = TEXT("��ǰ����Ϊ��B");
		now_key_click.ReleaseBuffer();
		break;
	case 67:
		now_key_click = TEXT("��ǰ����Ϊ��C");
		now_key_click.ReleaseBuffer();
		break;
	case 68:
		now_key_click = TEXT("��ǰ����Ϊ��D");
		now_key_click.ReleaseBuffer();
		break;
	case 69:
		now_key_click = TEXT("��ǰ����Ϊ��E");
		now_key_click.ReleaseBuffer();
		break;
	case 70:
		now_key_click = TEXT("��ǰ����Ϊ��F");
		now_key_click.ReleaseBuffer();
		break;
	case 71:
		now_key_click = TEXT("��ǰ����Ϊ��G");
		now_key_click.ReleaseBuffer();
		break;
	case 72:
		now_key_click = TEXT("��ǰ����Ϊ��H");
		now_key_click.ReleaseBuffer();
		break;
	case 73:
		now_key_click = TEXT("��ǰ����Ϊ��I");
		now_key_click.ReleaseBuffer();
		break;
	case 74:
		now_key_click = TEXT("��ǰ����Ϊ��J");
		now_key_click.ReleaseBuffer();
		break;
	case 75:
		now_key_click = TEXT("��ǰ����Ϊ��K");
		now_key_click.ReleaseBuffer();
		break;
	case 76:
		now_key_click = TEXT("��ǰ����Ϊ��L");
		now_key_click.ReleaseBuffer();
		break;
	case 77:
		now_key_click = TEXT("��ǰ����Ϊ��M");
		now_key_click.ReleaseBuffer();
		break;
	case 78:
		now_key_click = TEXT("��ǰ����Ϊ��N");
		now_key_click.ReleaseBuffer();
		break;
	case 79:
		now_key_click = TEXT("��ǰ����Ϊ��O");
		now_key_click.ReleaseBuffer();
		break;
	case 80:
		now_key_click = TEXT("��ǰ����Ϊ��P");
		now_key_click.ReleaseBuffer();
		break;
	case 81:
		now_key_click = TEXT("��ǰ����Ϊ��Q");
		now_key_click.ReleaseBuffer();
		break;
	case 82:
		now_key_click = TEXT("��ǰ����Ϊ��R");
		now_key_click.ReleaseBuffer();
		break;
	case 83:
		now_key_click = TEXT("��ǰ����Ϊ��S");
		now_key_click.ReleaseBuffer();
		break;
	case 84:
		now_key_click = TEXT("��ǰ����Ϊ��T");
		now_key_click.ReleaseBuffer();
		break;
	case 85:
		now_key_click = TEXT("��ǰ����Ϊ��U");
		now_key_click.ReleaseBuffer();
		break;
	case 86:
		now_key_click = TEXT("��ǰ����Ϊ��V");
		now_key_click.ReleaseBuffer();
		break;
	case 87:
		now_key_click = TEXT("��ǰ����Ϊ��W");
		now_key_click.ReleaseBuffer();
		break;
	case 88:
		now_key_click = TEXT("��ǰ����Ϊ��X");
		now_key_click.ReleaseBuffer();
		break;
	case 89:
		now_key_click = TEXT("��ǰ����Ϊ��Y");
		now_key_click.ReleaseBuffer();
		break;
	case 90:
		now_key_click = TEXT("��ǰ����Ϊ��Z");
		now_key_click.ReleaseBuffer();
		break;
	case 91:
		now_key_click = TEXT("��ǰ����Ϊ��LWin");
		now_key_click.ReleaseBuffer();
		break;
	case 92:
		now_key_click = TEXT("��ǰ����Ϊ��RWin");
		now_key_click.ReleaseBuffer();
		break;
	case 93:
		now_key_click = TEXT("��ǰ����Ϊ��Apps");
		now_key_click.ReleaseBuffer();
		break;
	case 95:
		now_key_click = TEXT("��ǰ����Ϊ��Sleep");
		now_key_click.ReleaseBuffer();
		break;
	case 96:
		now_key_click = TEXT("��ǰ����Ϊ��0");
		now_key_click.ReleaseBuffer();
		break;
	case 97:
		now_key_click = TEXT("��ǰ����Ϊ��1");
		now_key_click.ReleaseBuffer();
		break;
	case 98:
		now_key_click = TEXT("��ǰ����Ϊ��2");
		now_key_click.ReleaseBuffer();
		break;
	case 99:
		now_key_click = TEXT("��ǰ����Ϊ��3");
		now_key_click.ReleaseBuffer();
		break;
	case 100:
		now_key_click = TEXT("��ǰ����Ϊ��4");
		now_key_click.ReleaseBuffer();
		break;
	case 101:
		now_key_click = TEXT("��ǰ����Ϊ��5");
		now_key_click.ReleaseBuffer();
		break;
	case 102:
		now_key_click = TEXT("��ǰ����Ϊ��6");
		now_key_click.ReleaseBuffer();
		break;
	case 103:
		now_key_click = TEXT("��ǰ����Ϊ��7");
		now_key_click.ReleaseBuffer();
		break;
	case 104:
		now_key_click = TEXT("��ǰ����Ϊ��8");
		now_key_click.ReleaseBuffer();
		break;
	case 105:
		now_key_click = TEXT("��ǰ����Ϊ��9");
		now_key_click.ReleaseBuffer();
		break;
	case 106:
		now_key_click = TEXT("��ǰ����Ϊ��*");
		now_key_click.ReleaseBuffer();
		break;
	case 107:
		now_key_click = TEXT("��ǰ����Ϊ��+");
		now_key_click.ReleaseBuffer();
		break;
	case 108:
		now_key_click = TEXT("��ǰ����Ϊ��Enter");
		now_key_click.ReleaseBuffer();
		break;
	case 109:
		now_key_click = TEXT("��ǰ����Ϊ��-");
		now_key_click.ReleaseBuffer();
		break;
	case 110:
		now_key_click = TEXT("��ǰ����Ϊ��.");
		now_key_click.ReleaseBuffer();
		break;
	case 111:
		now_key_click = TEXT("��ǰ����Ϊ��/");
		now_key_click.ReleaseBuffer();
		break;
	case 112:
		now_key_click = TEXT("��ǰ����Ϊ��F1");
		now_key_click.ReleaseBuffer();
		break;
	case 113:
		now_key_click = TEXT("��ǰ����Ϊ��F2");
		now_key_click.ReleaseBuffer();
		break;
	case 114:
		now_key_click = TEXT("��ǰ����Ϊ��F3");
		now_key_click.ReleaseBuffer();
		break;
	case 115:
		now_key_click = TEXT("��ǰ����Ϊ��F4");
		now_key_click.ReleaseBuffer();
		break;
	case 116:
		now_key_click = TEXT("��ǰ����Ϊ��F5");
		now_key_click.ReleaseBuffer();
		break;
	case 117:
		now_key_click = TEXT("��ǰ����Ϊ��F6");
		now_key_click.ReleaseBuffer();
		break;
	case 118:
		now_key_click = TEXT("��ǰ����Ϊ��F7");
		now_key_click.ReleaseBuffer();
		break;
	case 119:
		now_key_click = TEXT("��ǰ����Ϊ��F8");
		now_key_click.ReleaseBuffer();
		break;
	case 120:
		now_key_click = TEXT("��ǰ����Ϊ��F9");
		now_key_click.ReleaseBuffer();
		break;
	case 121:
		now_key_click = TEXT("��ǰ����Ϊ��F10");
		now_key_click.ReleaseBuffer();
		break;
	case 122:
		now_key_click = TEXT("��ǰ����Ϊ��F11");
		now_key_click.ReleaseBuffer();
		break;
	case 123:
		now_key_click = TEXT("��ǰ����Ϊ��F12");
		now_key_click.ReleaseBuffer();
		break;
	case 144:
		now_key_click = TEXT("��ǰ����Ϊ��Num Lock");
		now_key_click.ReleaseBuffer();
		break;
	case 145:
		now_key_click = TEXT("��ǰ����Ϊ��Scroll");
		now_key_click.ReleaseBuffer();
		break;
	case 160:
		now_key_click = TEXT("��ǰ����Ϊ��LShift");
		now_key_click.ReleaseBuffer();
		break;
	case 161:
		now_key_click = TEXT("��ǰ����Ϊ��RShift");
		now_key_click.ReleaseBuffer();
		break;
	case 162:
		now_key_click = TEXT("��ǰ����Ϊ��LCtrl");
		now_key_click.ReleaseBuffer();
		break;
	case 163:
		now_key_click = TEXT("��ǰ����Ϊ��RCtrl");
		now_key_click.ReleaseBuffer();
		break;
	case 164:
		now_key_click = TEXT("��ǰ����Ϊ��LAlt");
		now_key_click.ReleaseBuffer();
		break;
	case 165:
		now_key_click = TEXT("��ǰ����Ϊ��RAlt");
		now_key_click.ReleaseBuffer();
		break;
	case 173:
		now_key_click = TEXT("��ǰ����Ϊ��Volume Mute");
		now_key_click.ReleaseBuffer();
		break;
	case 174:
		now_key_click = TEXT("��ǰ����Ϊ��Volume Down");
		now_key_click.ReleaseBuffer();
		break;
	case 175:
		now_key_click = TEXT("��ǰ����Ϊ��Volume Up");
		now_key_click.ReleaseBuffer();
		break;
	case 186:
		now_key_click = TEXT("��ǰ����Ϊ��;");
		now_key_click.ReleaseBuffer();
		break;
	case 187:
		now_key_click = TEXT("��ǰ����Ϊ��=");
		now_key_click.ReleaseBuffer();
		break;
	case 188:
		now_key_click = TEXT("��ǰ����Ϊ��,");
		now_key_click.ReleaseBuffer();
		break;
	case 189:
		now_key_click = TEXT("��ǰ����Ϊ��-");
		now_key_click.ReleaseBuffer();
		break;
	case 190:
		now_key_click = TEXT("��ǰ����Ϊ��.");
		now_key_click.ReleaseBuffer();
		break;
	case 191:
		now_key_click = TEXT("��ǰ����Ϊ��/");
		now_key_click.ReleaseBuffer();
		break;
	case 192:
		now_key_click = TEXT("��ǰ����Ϊ��`");
		now_key_click.ReleaseBuffer();
		break;
	case 219:
		now_key_click = TEXT("��ǰ����Ϊ��[");
		now_key_click.ReleaseBuffer();
		break;
	case 220:
		now_key_click = TEXT("��ǰ����Ϊ��\\");
		now_key_click.ReleaseBuffer();
		break;
	case 221:
		now_key_click = TEXT("��ǰ����Ϊ��]");
		now_key_click.ReleaseBuffer();
		break;
	case 222:
		now_key_click = TEXT("��ǰ����Ϊ��\'");
		now_key_click.ReleaseBuffer();
		break;
	}
}

void SetIni()
{
	CString temp_key_click;
	GetPrivateProfileString(TEXT("TheMouseClicker"), TEXT("ClickKey"), TEXT("1"), temp_key_click.GetBuffer(4), 4, TEXT("./TheMouseClicker.ini"));
	temp_key_click.ReleaseBuffer();
	key_click = _ttoi(temp_key_click);
	SetNowKeyClick();
}

void SaveIni(int key_click)
{
	CString temp_key_click;
	temp_key_click.Format(TEXT("%d"), key_click);
	WritePrivateProfileString(TEXT("TheMouseClicker"), TEXT("ClickKey"), temp_key_click, TEXT("./TheMouseClicker.ini"));
}

void CreateData()
{
	CString str = TEXT("./data");
	if (!PathIsDirectory(str))
	{
		CreateDirectory(str, NULL);
	}
}

bool IsSameName(CString output_txt)
{
	std::ifstream input(output_txt);
	if (input.is_open())
		return true;
	else
		return false;
}

void Click(double count_time)
{
	bool Continue = true;
	int temp_key = key_click;
	double time0 = GetTickCount(), time1 = 0;
	if (temp_key == 1)
		while (true)
		{
			if (Continue == true)
			{
				time1 = GetTickCount();
				if (KEY_DOWN(4))
				{
					Continue = false;
					Sleep(500);
				}
				if (KEY_DOWN(27))
				{
					break;
				}
				if ((time1 - time0) > count_time)
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					Sleep(10);
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					time0 = GetTickCount();
				}
			}
			if (Continue == false)
			{
				if (KEY_DOWN(4))
				{
					Continue = true;
					Sleep(500);
				}
				if (KEY_DOWN(27))
				{
					break;
				}
			}
			Sleep(1);
		}
	else if (temp_key == 2)
		while (true)
		{
			if (Continue == true)
			{
				time1 = GetTickCount();
				if (KEY_DOWN(4))
				{
					Continue = false;
					Sleep(500);
				}
				if (KEY_DOWN(27))
				{
					break;
				}
				if ((time1 - time0) > count_time)
				{
					mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
					Sleep(10);
					mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
					time0 = GetTickCount();
				}
			}
			if (Continue == false)
			{
				if (KEY_DOWN(4))
				{
					Continue = true;
					Sleep(500);
				}
				if (KEY_DOWN(27))
				{
					break;
				}
			}
			Sleep(1);
		}
	else
		while (true)
		{
			if (Continue == true)
			{
				time1 = GetTickCount();
				if (KEY_DOWN(4))
				{
					Continue = false;
					Sleep(500);
				}
				if (KEY_DOWN(27))
				{
					break;
				}
				if ((time1 - time0) > count_time)
				{
					keybd_event(temp_key, 0, 0, 0);
					Sleep(10);
					keybd_event(temp_key, 0, KEYEVENTF_KEYUP, 0);
					time0 = GetTickCount();
				}
			}
			if (Continue == false)
			{
				if (KEY_DOWN(4))
				{
					Continue = true;
					Sleep(500);
				}
				if (KEY_DOWN(27))
				{
					break;
				}
			}
			Sleep(1);
		}
}

void Record()
{
	key_press_head = new Press();
	p_key_press0 = key_press_head;
	count = 0;
	click_count = 0;
	i_down = new bool[254];
	point = new POINT[total_times];
	memset(i_down, 0, sizeof(i_down));

	HWND hwnd = FindWindow(NULL, version);
	POINT* p_point = point;
	bool left_down = false, right_down = false;

	while (count < total_times)
	{
		GetCursorPos(p_point++);
		for (int i = 0; i < 254; i++)
		{
			if (i != 27)
			{
				if (KEY_DOWN(i) == true && i_down[i] == false)
				{
					p_key_press1 = new Press();
					p_key_press1->time = count;
					p_key_press1->key = i;
					p_key_press0->next = p_key_press1;
					p_key_press0 = p_key_press0->next;
					i_down[i] = true;
					click_count++;
				}
				if (i_down[i] == true && KEY_UP(i) == true)
				{
					p_key_press1 = new Press();
					p_key_press1->time = count;
					p_key_press1->key = -i;
					p_key_press0->next = p_key_press1;
					p_key_press0 = p_key_press0->next;
					i_down[i] = false;
					click_count++;
				}
			}
		}
		if (KEY_DOWN(27))
		{
			break;
		}
		count++;
		Sleep(time_interval);
	}
	CreateWindowEx(NULL, L"Record_Output", L"���뱣����ļ�����������׺��", WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WM_CTLCOLORSTATIC, 150, 150, 400, 200, hwnd, NULL, NULL, NULL);
	MSG msg_newpage;
	while (GetMessageW(&msg_newpage, NULL, 0, 0))
	{
		TranslateMessage(&msg_newpage);
		DispatchMessageW(&msg_newpage);
	}
	UpdateWindow(hwnd);
	p_key_press0 = key_press_head;
	while (p_key_press0->next != NULL)
	{
		p_key_press1 = p_key_press0->next;
		delete p_key_press0;
		p_key_press0 = p_key_press1;
	}
	delete p_key_press0;
	delete[] point;
	delete[] i_down;
}

void Display()
{
	Sleep(100);
	if (input_success == true)
	{
		bool display_continue = true;
		int i = 0;
		double time0 = 0, time1 = 0;
		while (display_continue == true)
		{
			p_key_press0 = key_press_head;
			if (p_key_press0->next != NULL)
				p_key_press0 = p_key_press0->next;
			i = 0;
			while (i <= count)
			{
				SetCursorPos(point[i].x, point[i].y);
				if (i == p_key_press0->time)
				{
					if (p_key_press0->key < 6)
					{
						if (p_key_press0->key == 1)
						{
							mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
							if (p_key_press0->next != NULL)
								p_key_press0 = p_key_press0->next;
						}
						else if (p_key_press0->key == -1)
						{
							mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							if (p_key_press0->next != NULL)
								p_key_press0 = p_key_press0->next;
						}
						else if (p_key_press0->key == 2)
						{
							mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
							if (p_key_press0->next != NULL)
								p_key_press0 = p_key_press0->next;
						}
						else if (p_key_press0->key == -2)
						{
							mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							if (p_key_press0->next != NULL)
								p_key_press0 = p_key_press0->next;
						}
						else if (p_key_press0->key == 4)
						{
							mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
							if (p_key_press0->next != NULL)
								p_key_press0 = p_key_press0->next;
						}
						else if (p_key_press0->key == -4)
						{
							mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
							if (p_key_press0->next != NULL)
								p_key_press0 = p_key_press0->next;
						}
					}
					else
					{
						if (p_key_press0->key > 0)
						{
							keybd_event(p_key_press0->key, 0, 0, 0);
							if (p_key_press0->next != NULL)
								p_key_press0 = p_key_press0->next;
						}
						if (p_key_press0->key < 0)
						{
							keybd_event(-p_key_press0->key, 0, KEYEVENTF_KEYUP, 0);
							if (p_key_press0->next != NULL)
								p_key_press0 = p_key_press0->next;
						}
					}

				}
				if (KEY_DOWN(27))
				{
					display_continue = false;
					break;
				}
				i++;
				Sleep(time_interval);
			}
			time0 = GetTickCount();
			time1 = GetTickCount();
			while (time1 - time0 < 3000)
			{
				time1 = GetTickCount();
				if (KEY_DOWN(27))
				{
					display_continue = false;
					break;
				}
				Sleep(time_interval);
			}
		}
	}
	input_success = false;
	p_key_press0 = key_press_head;
	while (p_key_press0->next != NULL)
	{
		p_key_press1 = p_key_press0->next;
		delete p_key_press0;
		p_key_press0 = p_key_press1;
	}
	delete p_key_press0;
	delete[] point;
}

LRESULT CALLBACK RecordInputWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND name_get = NULL, button_ok;
	switch (msg)
	{
	case WM_CREATE:
	{
		name_get = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 35, 360, 30, hwnd, (HMENU)Input_Name, NULL, NULL);
		button_ok = CreateWindow(L"button", L"ȷ��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 165, 100, 70, 50, hwnd, (HMENU)BUTTON_INPUT, NULL, NULL);
		SendMessage(name_get, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(button_ok, WM_SETFONT, (WPARAM)font, TRUE);
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case BUTTON_INPUT:
		{
			

			CString temp;
			CString storage_address = L"./data/";
			GetDlgItemText(hwnd, Input_Name, temp.GetBuffer(100), 100);
			temp.ReleaseBuffer();
			temp += ".txt";
			storage_address += temp;
			int a = 0, b = 0;
			std::ifstream input(storage_address);
			if (input.is_open())
			{

				input >> count >> click_count;

				point = new POINT[total_times];
				for (int i = 0; i <= count; i++)
				{
					input >> point[i].x;
				}
				for (int i = 0; i <= count; i++)
				{
					input >> point[i].y;
				}

				key_press_head = new Press();
				p_key_press0 = key_press_head;

				for (int i = 0; i < click_count; i++)
				{
					p_key_press1 = new Press();
					input >> p_key_press1->time >> p_key_press1->key;
					p_key_press0->next = p_key_press1;
					p_key_press0 = p_key_press0->next;
				}

				input_success = true;
				input.close();
				std::thread display(Display);
				SendMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
				Sleep(10);
				display.detach();
				SendMessage(hwnd, WM_CLOSE, NULL, NULL);
			}
			else
			{
				MessageBox(NULL, L"�Ҳ����ļ�", L"Warning", MB_OK);
			}
		}
		}
	}
	case WM_CLOSE:
	{
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK RecordOutputReact(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND name_get = NULL, button_ok;
	switch (msg)
	{
	case WM_CREATE:
	{
		name_get = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 35, 360, 30, hwnd, (HMENU)Output_Name, NULL, NULL);
		button_ok = CreateWindow(L"button", L"ȷ��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 165, 100, 70, 50, hwnd, (HMENU)BUTTON_OUTPUT, NULL, NULL);
		SendMessage(name_get, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(button_ok, WM_SETFONT, (WPARAM)font, TRUE);
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case BUTTON_OUTPUT:
		{
			CString temp;
			CString storage_address = L"./data/";
			GetDlgItemText(hwnd, Output_Name, temp.GetBuffer(100), 100);
			temp.ReleaseBuffer();
			temp += ".txt";
			storage_address += temp;
			if (IsSameName(storage_address))
			{
				MessageBox(NULL, L"�Ѵ���ͬ���ļ�", L"Warning", MB_OK);
			}
			else
			{
				std::ofstream output;
				CreateData();
				output.open(storage_address);
				output << count << ' ' << click_count << std::endl;
				for (int i = 0; i <= count; i++)
				{
					output << point[i].x << " ";
				}
				output << std::endl;
				for (int i = 0; i <= count; i++)
				{
					output << point[i].y << " ";
				}
				output << std::endl;
				p_key_press0 = key_press_head;
				while (p_key_press0->next != NULL)
				{
					p_key_press0 = p_key_press0->next;
					output << p_key_press0->time << ' ' << p_key_press0->key << std::endl;
				}
				output.close();
				SendMessage(hwnd, WM_CLOSE, NULL, NULL);
				MessageBox(NULL, storage_address, storage_address, MB_OK);
				break;
			}
		}
		}
	case WM_CLOSE:
	{
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK TimeWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND text1, time_get = NULL, button_okl, button_cancel, button_okr, text2, main_win;
	static HWND hwnd_now_key;
	main_win = FindWindow(NULL, version);
	double count_time = 0;
	HDC hdc;
	PAINTSTRUCT ps;
	switch (msg)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		text1 = CreateWindow(L"static", L"������ʱ�䣨��λ:�룩", WS_CHILD | WS_VISIBLE, 10, 10, 200, 30, hwnd, (HMENU)1, NULL, 0);
		TextOutW(hdc, 210, 35, now_key_click, now_key_click.GetLength());
		text2 = CreateWindow(L"static", L"��ʼ�󣬰�������ֹͣ������ESC������", WS_CHILD | WS_VISIBLE, 5, 70, 400, 30, hwnd, (HMENU)1, NULL, 0);
		time_get = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 35, 195, 30, hwnd, (HMENU)Input_Time, NULL, NULL);
		button_okl = CreateWindow(L"button", L"���㣡", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 100, 70, 50, hwnd, (HMENU)BUTTON_SURE, NULL, NULL);
		button_okr = CreateWindow(L"button", L"�޸İ���", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 100, 90, 50, hwnd, (HMENU)BUTTON_SELECT_KEY, NULL, NULL);
		button_cancel = CreateWindow(L"button", L"ȡ��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 200, 100, 70, 50, hwnd, (HMENU)BUTTON_CANCEL, NULL, NULL);
		SendMessage(text1, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(button_okl, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(button_okr, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(button_cancel, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(time_get, WM_SETFONT, (WPARAM)font, TRUE);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_CTLCOLORSTATIC:
	{
		if ((HWND)lParam == GetDlgItem(hwnd, 1))//���ָ����ǩ��������Ա�
		{
			SetTextColor((HDC)wParam, RGB(0, 0, 0));//�����ı���ɫ
			SetBkMode((HDC)wParam, TRANSPARENT);//���ñ���͸��
		}
		return (INT_PTR)GetStockObject((NULL_BRUSH));
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case BUTTON_SURE:
		{
			CString temp;
			GetDlgItemText(hwnd, Input_Time, temp.GetBuffer(11), 11);
			temp.ReleaseBuffer();
			double count_time = _wtof(temp);
			if (count_time < 0 || count_time >= 10000000000)
				MessageBox(NULL, L"���뷶Χ��0~9999999999֮��", L"FBI Warning!", MB_OK);
			else if (count_time == 9999999999)
				MessageBox(NULL, L"�����㣬������������Ҫ��10���˵�ʱ�����ʵ��һ�ε���", L"FBI Warning!", MB_OK);
			else if (count_time >= 2491344000)
				MessageBox(NULL, L"��֪������ƽ��������79����", L"FBI Warning!", MB_OK);
			else
			{
				count_time *= 1000;
				SendMessage(hwnd, WM_CLOSE, NULL, NULL);
				SendMessage(main_win, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
				std::thread click(Click, count_time);
				Sleep(1000);
				click.detach();
				Sleep(10);
				temp.ReleaseBuffer(10);
			}
			break;
		}
		case BUTTON_SELECT_KEY:
		{
			std::thread getkey(GetKey);
			CreateWindowEx(NULL, L"Tips", L"��ʾ", WS_VISIBLE | WM_CTLCOLORSTATIC, 300, 300, 250, 100, hwnd, NULL, NULL, NULL);
			MSG msg_newpage;
			while (GetMessageW(&msg_newpage, NULL, 0, 0))
			{
				TranslateMessage(&msg_newpage);
				DispatchMessageW(&msg_newpage);
			}
			getkey.detach();
			SetNowKeyClick();
			InvalidateRect(hwnd, NULL, true);
			UpdateWindow(hwnd);
			break;
		}
		case BUTTON_CANCEL:
		{
			SendMessage(hwnd, WM_CLOSE, NULL, NULL);
			break;
		}
		}
	}
	case WM_CLOSE:
	{
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK TipsProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND text;
	switch (msg)
	{
	case WM_CREATE:
	{
		text = CreateWindow(L"static", L"�뵥����ѡ��İ���", WS_CHILD | WS_VISIBLE, 20, 20, 200, 36, hwnd, (HMENU)1, NULL, 0);
		SendMessage(text, WM_SETFONT, (WPARAM)font, TRUE);
		break;
	}
	case WM_CTLCOLORSTATIC:
	{
		if ((HWND)lParam == GetDlgItem(hwnd, 1))//���ָ����ǩ��������Ա�
		{
			SetTextColor((HDC)wParam, RGB(0, 0, 0));//�����ı���ɫ
			SetBkMode((HDC)wParam, TRANSPARENT);//���ñ���͸��
		}
		return (INT_PTR)GetStockObject((NULL_BRUSH));
		break;
	}
	case WM_CLOSE:
	{
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND hwndButton1, hwndButton2, hwndButton3, hwndButton4, text;
	bool record_button = false;
	switch (msg)
	{
	case WM_PAINT:
	{
		text = CreateWindow(L"static", version, WS_CHILD | WS_VISIBLE, 90, 50, 200, 20, hwnd, (HMENU)1, NULL, 0);
		hwndButton1 = CreateWindowEx(NULL, TEXT("Button"), TEXT("1.������������ESC���˳���"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 100, 265, 50, hwnd, (HMENU)BUTTON1, NULL, NULL);
		hwndButton2 = CreateWindowEx(NULL, TEXT("Button"), TEXT("2.¼��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 175, 265, 50, hwnd, (HMENU)BUTTON2, NULL, NULL);
		hwndButton3 = CreateWindowEx(NULL, TEXT("Button"), TEXT("3.����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 250, 265, 50, hwnd, (HMENU)BUTTON3, NULL, NULL);
		hwndButton4 = CreateWindowEx(NULL, TEXT("Button"), TEXT("4.��Ŀ��ַ"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 325, 265, 50, hwnd, (HMENU)BUTTON4, NULL, NULL);
		SendMessage(text, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(hwndButton1, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(hwndButton2, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(hwndButton3, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(hwndButton4, WM_SETFONT, (WPARAM)font, TRUE);
		break;
	}
	case WM_CTLCOLORSTATIC:
	{
		if ((HWND)lParam == GetDlgItem(hwnd, 1))//���ָ����ǩ��������Ա�
		{
			SetTextColor((HDC)wParam, RGB(0, 0, 0));//�����ı���ɫ
			SetBkMode((HDC)wParam, TRANSPARENT);//���ñ���͸��
		}
		return (INT_PTR)GetStockObject((NULL_BRUSH));
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case BUTTON1:
		{
			CreateWindowEx(NULL, L"Time_Input", L"����", WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE | WM_CTLCOLORSTATIC, 150, 150, 410, 200, NULL, NULL, NULL, NULL);
			MSG msg_newpage;
			while (GetMessageW(&msg_newpage, NULL, 0, 0))
			{
				TranslateMessage(&msg_newpage);
				DispatchMessageW(&msg_newpage);
			}
			break;
		}
		case BUTTON2:
		{
			record_button = true;
			MessageBox(hwnd, L"���ȷ����ʼ¼��(����ESC������)", L"׼����ʼ", MB_OK);
			UpdateWindow(hwnd);
			break;
		}
		case BUTTON3:
		{
			CreateWindowEx(NULL, L"Record_Input", L"���뱣����ļ�����������׺��", WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE | WM_CTLCOLORSTATIC, 150, 150, 400, 200, hwnd, NULL, NULL, NULL);
			MSG msg_newpage;
			while (GetMessageW(&msg_newpage, NULL, 0, 0))
			{
				TranslateMessage(&msg_newpage);
				DispatchMessageW(&msg_newpage);
			}
			SendMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
			UpdateWindow(hwnd);
			break;
		}
		case BUTTON4:
		{
			ShellExecute(NULL, L"open", L"explorer.exe", add, NULL, SW_SHOW);
			Sleep(10);
			break;
		}
		}
	}
	case IDH_OK:
	{
		if (record_button)
		{
			std::thread record(Record);
			SendMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
			Sleep(100);
			record.detach();
			record_button = false;
			break;
		}
	}
	case WM_CLOSE:
	{
		SaveIni(key_click);
		break;
	}
	case WM_DESTROY:
	{
		DeleteObject(font);
		PostQuitMessage(0);
		return 0;
	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//init
	CreateData();
	SetIni();

	WNDCLASSEX main_window, time_input, record_input, record_output, tips;

	//main_window����
	main_window.cbSize = sizeof(main_window);
	main_window.style = CS_VREDRAW | CS_HREDRAW;
	main_window.lpfnWndProc = WinProc;
	main_window.cbClsExtra = 0;
	main_window.cbWndExtra = 0;
	main_window.hInstance = hInstance;
	main_window.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_ICON1));
	main_window.hCursor = LoadCursorW(hInstance, IDC_ARROW);
	main_window.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	main_window.lpszMenuName = NULL;
	main_window.lpszClassName = L"Main";
	main_window.hIconSm = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_ICON1));

	time_input.cbSize = sizeof(time_input);
	time_input.style = CS_VREDRAW | CS_HREDRAW;
	time_input.lpfnWndProc = TimeWinProc;
	time_input.cbClsExtra = 0;
	time_input.cbWndExtra = 0;
	time_input.hInstance = NULL;
	time_input.hIcon = NULL;
	time_input.hCursor = NULL;
	time_input.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	time_input.lpszMenuName = NULL;
	time_input.lpszClassName = L"Time_Input";
	time_input.hIconSm = NULL;

	record_input.cbSize = sizeof(record_input);
	record_input.style = CS_VREDRAW | CS_HREDRAW;
	record_input.lpfnWndProc = RecordInputWinProc;
	record_input.cbClsExtra = 0;
	record_input.cbWndExtra = 0;
	record_input.hInstance = NULL;
	record_input.hIcon = NULL;
	record_input.hCursor = NULL;
	record_input.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	record_input.lpszMenuName = NULL;
	record_input.lpszClassName = L"Record_Input";
	record_input.hIconSm = NULL;

	record_output.cbSize = sizeof(record_output);
	record_output.style = CS_VREDRAW | CS_HREDRAW;
	record_output.lpfnWndProc = RecordOutputReact;
	record_output.cbClsExtra = 0;
	record_output.cbWndExtra = 0;
	record_output.hInstance = NULL;
	record_output.hIcon = NULL;
	record_output.hCursor = NULL;
	record_output.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	record_output.lpszMenuName = NULL;
	record_output.lpszClassName = L"Record_Output";
	record_output.hIconSm = NULL;

	tips.cbSize = sizeof(tips);
	tips.style = CS_VREDRAW | CS_HREDRAW;
	tips.lpfnWndProc = TipsProc;
	tips.cbClsExtra = 0;
	tips.cbWndExtra = 0;
	tips.hInstance = NULL;
	tips.hIcon = NULL;
	tips.hCursor = NULL;
	tips.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	tips.lpszMenuName = NULL;
	tips.lpszClassName = L"Tips";
	tips.hIconSm = NULL;

	//ע�ᴰ��
	if (0 == RegisterClassExW(&main_window))
	{
		MessageBoxW(NULL, L"main wrong", L"Regist", MB_OK);
		return 0;
	}

	if (0 == RegisterClassExW(&time_input))
	{
		MessageBox(NULL, L"time input wrong", L"Regist", MB_OK);
		return 0;
	}

	if (0 == RegisterClassExW(&record_input))
	{
		MessageBox(NULL, L"record input wrong", L"Regist", MB_OK);
		return 0;
	}

	if (0 == RegisterClassExW(&record_output))
	{
		MessageBox(NULL, L"record output wrong", L"Regist", MB_OK);
		return 0;
	}

	if (0 == RegisterClassExW(&tips))
	{
		MessageBox(NULL, L"tips wrong", L"Regist", MB_OK);
		return 0;
	}

	//��������
	HWND main_win = CreateWindowEx(NULL, L"Main", version, WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE | WM_CTLCOLORSTATIC, 100, 100, 300, 450, NULL, NULL, hInstance, NULL);

	ShowWindow(main_win, SW_SHOW);
	UpdateWindow(main_win);

	//����ˢ��
	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);	
		DispatchMessageW(&msg);
	}
	delete key_press_head;
	return 0;
}