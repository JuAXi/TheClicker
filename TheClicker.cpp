#include <Windows.h>
#include "resource.h"
#include <atlstr.h>
#include <thread>
#include <fstream>
#include <ShlObj.h>

#ifdef x86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#ifdef x64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

CString version = L"TheClicker1.3.1";
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
CString now_key_click = TEXT("当前按键为：");

const HFONT font = CreateFont(18, 9, 0, 0, 600, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"宋体");

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
		now_key_click = TEXT("当前按键为：LButton");
		now_key_click.ReleaseBuffer();
		break;
	case 2:
		now_key_click = TEXT("当前按键为：RButton");
		now_key_click.ReleaseBuffer();
		break;
	case 8:
		now_key_click = TEXT("当前按键为：Back");
		now_key_click.ReleaseBuffer();
		break;
	case 9:
		now_key_click = TEXT("当前按键为：Tab");
		now_key_click.ReleaseBuffer();
		break;
	case 12:
		now_key_click = TEXT("当前按键为：Clear");
		now_key_click.ReleaseBuffer();
		break;
	case 13:
		now_key_click = TEXT("当前按键为：Enter");
		now_key_click.ReleaseBuffer();
		break;
	case 19:
		now_key_click = TEXT("当前按键为：Pause");
		now_key_click.ReleaseBuffer();
		break;
	case 20:
		now_key_click = TEXT("当前按键为：Caps Lock");
		now_key_click.ReleaseBuffer();
		break;
	case 32:
		now_key_click = TEXT("当前按键为：Space");
		now_key_click.ReleaseBuffer();
		break;
	case 33:
		now_key_click = TEXT("当前按键为：Page Up");
		now_key_click.ReleaseBuffer();
		break;
	case 34:
		now_key_click = TEXT("当前按键为：Page Down");
		now_key_click.ReleaseBuffer();
		break;
	case 35:
		now_key_click = TEXT("当前按键为：End");
		now_key_click.ReleaseBuffer();
		break;
	case 36:
		now_key_click = TEXT("当前按键为：Home");
		now_key_click.ReleaseBuffer();
		break;
	case 37:
		now_key_click = TEXT("当前按键为：Left Arrow");
		now_key_click.ReleaseBuffer();
		break;
	case 38:
		now_key_click = TEXT("当前按键为：Up Arrow");
		now_key_click.ReleaseBuffer();
		break;
	case 39:
		now_key_click = TEXT("当前按键为：Right Arrow");
		now_key_click.ReleaseBuffer();
		break;
	case 40:
		now_key_click = TEXT("当前按键为：Down Arrow");
		now_key_click.ReleaseBuffer();
		break;
	case 41:
		now_key_click = TEXT("当前按键为：Select");
		now_key_click.ReleaseBuffer();
		break;
	case 42:
		now_key_click = TEXT("当前按键为：Print");
		now_key_click.ReleaseBuffer();
		break;
	case 43:
		now_key_click = TEXT("当前按键为：Excute");
		now_key_click.ReleaseBuffer();
		break;
	case 44:
		now_key_click = TEXT("当前按键为：Snapshot");
		now_key_click.ReleaseBuffer();
		break;
	case 45:
		now_key_click = TEXT("当前按键为：Insert");
		now_key_click.ReleaseBuffer();
		break;
	case 46:
		now_key_click = TEXT("当前按键为：Delete");
		now_key_click.ReleaseBuffer();
		break;
	case 47:
		now_key_click = TEXT("当前按键为：Help");
		now_key_click.ReleaseBuffer();
		break;
	case 48:
		now_key_click = TEXT("当前按键为：0");
		now_key_click.ReleaseBuffer();
		break;
	case 49:
		now_key_click = TEXT("当前按键为：1");
		now_key_click.ReleaseBuffer();
		break;
	case 50:
		now_key_click = TEXT("当前按键为：2");
		now_key_click.ReleaseBuffer();
		break;
	case 51:
		now_key_click = TEXT("当前按键为：3");
		now_key_click.ReleaseBuffer();
		break;
	case 52:
		now_key_click = TEXT("当前按键为：4");
		now_key_click.ReleaseBuffer();
		break;
	case 53:
		now_key_click = TEXT("当前按键为：5");
		now_key_click.ReleaseBuffer();
		break;
	case 54:
		now_key_click = TEXT("当前按键为：6");
		now_key_click.ReleaseBuffer();
		break;
	case 55:
		now_key_click = TEXT("当前按键为：7");
		now_key_click.ReleaseBuffer();
		break;
	case 56:
		now_key_click = TEXT("当前按键为：8");
		now_key_click.ReleaseBuffer();
		break;
	case 57:
		now_key_click = TEXT("当前按键为：9");
		now_key_click.ReleaseBuffer();
		break;
	case 65:
		now_key_click = TEXT("当前按键为：A");
		now_key_click.ReleaseBuffer();
		break;
	case 66:
		now_key_click = TEXT("当前按键为：B");
		now_key_click.ReleaseBuffer();
		break;
	case 67:
		now_key_click = TEXT("当前按键为：C");
		now_key_click.ReleaseBuffer();
		break;
	case 68:
		now_key_click = TEXT("当前按键为：D");
		now_key_click.ReleaseBuffer();
		break;
	case 69:
		now_key_click = TEXT("当前按键为：E");
		now_key_click.ReleaseBuffer();
		break;
	case 70:
		now_key_click = TEXT("当前按键为：F");
		now_key_click.ReleaseBuffer();
		break;
	case 71:
		now_key_click = TEXT("当前按键为：G");
		now_key_click.ReleaseBuffer();
		break;
	case 72:
		now_key_click = TEXT("当前按键为：H");
		now_key_click.ReleaseBuffer();
		break;
	case 73:
		now_key_click = TEXT("当前按键为：I");
		now_key_click.ReleaseBuffer();
		break;
	case 74:
		now_key_click = TEXT("当前按键为：J");
		now_key_click.ReleaseBuffer();
		break;
	case 75:
		now_key_click = TEXT("当前按键为：K");
		now_key_click.ReleaseBuffer();
		break;
	case 76:
		now_key_click = TEXT("当前按键为：L");
		now_key_click.ReleaseBuffer();
		break;
	case 77:
		now_key_click = TEXT("当前按键为：M");
		now_key_click.ReleaseBuffer();
		break;
	case 78:
		now_key_click = TEXT("当前按键为：N");
		now_key_click.ReleaseBuffer();
		break;
	case 79:
		now_key_click = TEXT("当前按键为：O");
		now_key_click.ReleaseBuffer();
		break;
	case 80:
		now_key_click = TEXT("当前按键为：P");
		now_key_click.ReleaseBuffer();
		break;
	case 81:
		now_key_click = TEXT("当前按键为：Q");
		now_key_click.ReleaseBuffer();
		break;
	case 82:
		now_key_click = TEXT("当前按键为：R");
		now_key_click.ReleaseBuffer();
		break;
	case 83:
		now_key_click = TEXT("当前按键为：S");
		now_key_click.ReleaseBuffer();
		break;
	case 84:
		now_key_click = TEXT("当前按键为：T");
		now_key_click.ReleaseBuffer();
		break;
	case 85:
		now_key_click = TEXT("当前按键为：U");
		now_key_click.ReleaseBuffer();
		break;
	case 86:
		now_key_click = TEXT("当前按键为：V");
		now_key_click.ReleaseBuffer();
		break;
	case 87:
		now_key_click = TEXT("当前按键为：W");
		now_key_click.ReleaseBuffer();
		break;
	case 88:
		now_key_click = TEXT("当前按键为：X");
		now_key_click.ReleaseBuffer();
		break;
	case 89:
		now_key_click = TEXT("当前按键为：Y");
		now_key_click.ReleaseBuffer();
		break;
	case 90:
		now_key_click = TEXT("当前按键为：Z");
		now_key_click.ReleaseBuffer();
		break;
	case 91:
		now_key_click = TEXT("当前按键为：LWin");
		now_key_click.ReleaseBuffer();
		break;
	case 92:
		now_key_click = TEXT("当前按键为：RWin");
		now_key_click.ReleaseBuffer();
		break;
	case 93:
		now_key_click = TEXT("当前按键为：Apps");
		now_key_click.ReleaseBuffer();
		break;
	case 95:
		now_key_click = TEXT("当前按键为：Sleep");
		now_key_click.ReleaseBuffer();
		break;
	case 96:
		now_key_click = TEXT("当前按键为：0");
		now_key_click.ReleaseBuffer();
		break;
	case 97:
		now_key_click = TEXT("当前按键为：1");
		now_key_click.ReleaseBuffer();
		break;
	case 98:
		now_key_click = TEXT("当前按键为：2");
		now_key_click.ReleaseBuffer();
		break;
	case 99:
		now_key_click = TEXT("当前按键为：3");
		now_key_click.ReleaseBuffer();
		break;
	case 100:
		now_key_click = TEXT("当前按键为：4");
		now_key_click.ReleaseBuffer();
		break;
	case 101:
		now_key_click = TEXT("当前按键为：5");
		now_key_click.ReleaseBuffer();
		break;
	case 102:
		now_key_click = TEXT("当前按键为：6");
		now_key_click.ReleaseBuffer();
		break;
	case 103:
		now_key_click = TEXT("当前按键为：7");
		now_key_click.ReleaseBuffer();
		break;
	case 104:
		now_key_click = TEXT("当前按键为：8");
		now_key_click.ReleaseBuffer();
		break;
	case 105:
		now_key_click = TEXT("当前按键为：9");
		now_key_click.ReleaseBuffer();
		break;
	case 106:
		now_key_click = TEXT("当前按键为：*");
		now_key_click.ReleaseBuffer();
		break;
	case 107:
		now_key_click = TEXT("当前按键为：+");
		now_key_click.ReleaseBuffer();
		break;
	case 108:
		now_key_click = TEXT("当前按键为：Enter");
		now_key_click.ReleaseBuffer();
		break;
	case 109:
		now_key_click = TEXT("当前按键为：-");
		now_key_click.ReleaseBuffer();
		break;
	case 110:
		now_key_click = TEXT("当前按键为：.");
		now_key_click.ReleaseBuffer();
		break;
	case 111:
		now_key_click = TEXT("当前按键为：/");
		now_key_click.ReleaseBuffer();
		break;
	case 112:
		now_key_click = TEXT("当前按键为：F1");
		now_key_click.ReleaseBuffer();
		break;
	case 113:
		now_key_click = TEXT("当前按键为：F2");
		now_key_click.ReleaseBuffer();
		break;
	case 114:
		now_key_click = TEXT("当前按键为：F3");
		now_key_click.ReleaseBuffer();
		break;
	case 115:
		now_key_click = TEXT("当前按键为：F4");
		now_key_click.ReleaseBuffer();
		break;
	case 116:
		now_key_click = TEXT("当前按键为：F5");
		now_key_click.ReleaseBuffer();
		break;
	case 117:
		now_key_click = TEXT("当前按键为：F6");
		now_key_click.ReleaseBuffer();
		break;
	case 118:
		now_key_click = TEXT("当前按键为：F7");
		now_key_click.ReleaseBuffer();
		break;
	case 119:
		now_key_click = TEXT("当前按键为：F8");
		now_key_click.ReleaseBuffer();
		break;
	case 120:
		now_key_click = TEXT("当前按键为：F9");
		now_key_click.ReleaseBuffer();
		break;
	case 121:
		now_key_click = TEXT("当前按键为：F10");
		now_key_click.ReleaseBuffer();
		break;
	case 122:
		now_key_click = TEXT("当前按键为：F11");
		now_key_click.ReleaseBuffer();
		break;
	case 123:
		now_key_click = TEXT("当前按键为：F12");
		now_key_click.ReleaseBuffer();
		break;
	case 144:
		now_key_click = TEXT("当前按键为：Num Lock");
		now_key_click.ReleaseBuffer();
		break;
	case 145:
		now_key_click = TEXT("当前按键为：Scroll");
		now_key_click.ReleaseBuffer();
		break;
	case 160:
		now_key_click = TEXT("当前按键为：LShift");
		now_key_click.ReleaseBuffer();
		break;
	case 161:
		now_key_click = TEXT("当前按键为：RShift");
		now_key_click.ReleaseBuffer();
		break;
	case 162:
		now_key_click = TEXT("当前按键为：LCtrl");
		now_key_click.ReleaseBuffer();
		break;
	case 163:
		now_key_click = TEXT("当前按键为：RCtrl");
		now_key_click.ReleaseBuffer();
		break;
	case 164:
		now_key_click = TEXT("当前按键为：LAlt");
		now_key_click.ReleaseBuffer();
		break;
	case 165:
		now_key_click = TEXT("当前按键为：RAlt");
		now_key_click.ReleaseBuffer();
		break;
	case 173:
		now_key_click = TEXT("当前按键为：Volume Mute");
		now_key_click.ReleaseBuffer();
		break;
	case 174:
		now_key_click = TEXT("当前按键为：Volume Down");
		now_key_click.ReleaseBuffer();
		break;
	case 175:
		now_key_click = TEXT("当前按键为：Volume Up");
		now_key_click.ReleaseBuffer();
		break;
	case 186:
		now_key_click = TEXT("当前按键为：;");
		now_key_click.ReleaseBuffer();
		break;
	case 187:
		now_key_click = TEXT("当前按键为：=");
		now_key_click.ReleaseBuffer();
		break;
	case 188:
		now_key_click = TEXT("当前按键为：,");
		now_key_click.ReleaseBuffer();
		break;
	case 189:
		now_key_click = TEXT("当前按键为：-");
		now_key_click.ReleaseBuffer();
		break;
	case 190:
		now_key_click = TEXT("当前按键为：.");
		now_key_click.ReleaseBuffer();
		break;
	case 191:
		now_key_click = TEXT("当前按键为：/");
		now_key_click.ReleaseBuffer();
		break;
	case 192:
		now_key_click = TEXT("当前按键为：`");
		now_key_click.ReleaseBuffer();
		break;
	case 219:
		now_key_click = TEXT("当前按键为：[");
		now_key_click.ReleaseBuffer();
		break;
	case 220:
		now_key_click = TEXT("当前按键为：\\");
		now_key_click.ReleaseBuffer();
		break;
	case 221:
		now_key_click = TEXT("当前按键为：]");
		now_key_click.ReleaseBuffer();
		break;
	case 222:
		now_key_click = TEXT("当前按键为：\'");
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
			if (i != 27 && i != 17)
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

	p_key_press0 = key_press_head;
	if (p_key_press0->next != NULL)
		p_key_press0 = p_key_press0->next;
	while ((p_key_press0->next != NULL) && (p_key_press0->time == 0))
	{
		click_count--;
		p_key_press0 = p_key_press0->next;
	}
	if (p_key_press0->time == 0)
		click_count--;

	HRESULT hresult = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hresult))
	{
		IFileDialog* ifiledialog = NULL;
		hresult = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&ifiledialog));
		if (SUCCEEDED(hresult))
		{
			hresult = ifiledialog->SetDefaultExtension(L"txt");
			COMDLG_FILTERSPEC file_type[] =
			{
				{L"Text files", L"*.txt"},
			};
			hresult = ifiledialog->SetFileTypes(ARRAYSIZE(file_type), file_type);
			hresult = ifiledialog->SetFileTypeIndex(1);
			hresult = ifiledialog->Show(NULL);
			if (SUCCEEDED(hresult))
			{
				IShellItem* ishellitem;
				hresult = ifiledialog->GetResult(&ishellitem);
				if (SUCCEEDED(hresult))
				{
					LPWSTR file_path = NULL;
						hresult = ishellitem->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &file_path);

						CString storage_address = file_path;
						std::ofstream output;
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
						if (p_key_press0->time != 0)
							output << p_key_press0->time << ' ' << p_key_press0->key << std::endl;
					}
					output.close();

					ishellitem->Release();
				}
			}
			ifiledialog->Release();
		}
		CoUninitialize();
	}

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
					if (p_key_press0->key < 6 && p_key_press0->key > -6)
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

/*连点器功能窗口*/
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
		text1 = CreateWindow(L"static", L"请输入时间（单位:毫秒）", WS_CHILD | WS_VISIBLE, 10, 10, 220, 30, hwnd, (HMENU)1, NULL, 0);
		TextOutW(hdc, 230, 35, now_key_click, now_key_click.GetLength());
		text2 = CreateWindow(L"static", L"开始后，按鼠标滚轮停止，按‘ESC’结束", WS_CHILD | WS_VISIBLE, 5, 70, 400, 30, hwnd, (HMENU)1, NULL, 0);
		time_get = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 10, 35, 195, 30, hwnd, (HMENU)Input_Time, NULL, NULL);
		button_okl = CreateWindow(L"button", L"开点！", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 100, 70, 50, hwnd, (HMENU)BUTTON_SURE, NULL, NULL);
		button_okr = CreateWindow(L"button", L"修改按键", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 100, 90, 50, hwnd, (HMENU)BUTTON_SELECT_KEY, NULL, NULL);
		button_cancel = CreateWindow(L"button", L"取消", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 200, 100, 70, 50, hwnd, (HMENU)BUTTON_CANCEL, NULL, NULL);
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
		if ((HWND)lParam == GetDlgItem(hwnd, 1))
		{
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
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
			GetDlgItemText(hwnd, Input_Time, temp.GetBuffer(7), 7);
			temp.ReleaseBuffer();
			double count_time = _wtof(temp);
			if (count_time < 0 || count_time >= 100000)
				MessageBox(NULL, L"输入范围在0~100000之间", L"FBI Warning!", MB_OK);
			else
			{
				SendMessage(hwnd, WM_CLOSE, NULL, NULL);
				SendMessage(main_win, WM_SYSCOMMAND, SC_MINIMIZE, NULL);
				std::thread click(Click, count_time);
				Sleep(1000);
				click.detach();
				Sleep(10);
				temp.ReleaseBuffer(7);
			}
			break;
		}
		case BUTTON_SELECT_KEY:
		{
			std::thread getkey(GetKey);
			CreateWindowEx(NULL, L"Tips", L"提示", WS_VISIBLE | WM_CTLCOLORSTATIC, 300, 300, 250, 100, hwnd, NULL, NULL, NULL);
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

/*更改按键提示窗口*/
LRESULT CALLBACK TipsProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND text;
	switch (msg)
	{
	case WM_CREATE:
	{
		text = CreateWindow(L"static", L"请单击想选择的按键", WS_CHILD | WS_VISIBLE, 20, 20, 200, 36, hwnd, (HMENU)1, NULL, 0);
		SendMessage(text, WM_SETFONT, (WPARAM)font, TRUE);
		break;
	}
	case WM_CTLCOLORSTATIC:
	{
		if ((HWND)lParam == GetDlgItem(hwnd, 1))
		{
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
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

/*主窗口*/
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND hwndButton1, hwndButton2, hwndButton3, hwndButton4, text;
	bool record_button = false;
	switch (msg)
	{
	case WM_PAINT:
	{
		text = CreateWindow(L"static", version, WS_CHILD | WS_VISIBLE, 90, 50, 200, 20, hwnd, (HMENU)1, NULL, 0);
		hwndButton1 = CreateWindowEx(NULL, TEXT("Button"), TEXT("1.连点器（按“ESC”退出）"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 100, 265, 50, hwnd, (HMENU)BUTTON1, NULL, NULL);
		hwndButton2 = CreateWindowEx(NULL, TEXT("Button"), TEXT("2.录制"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 175, 265, 50, hwnd, (HMENU)BUTTON2, NULL, NULL);
		hwndButton3 = CreateWindowEx(NULL, TEXT("Button"), TEXT("3.播放"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 250, 265, 50, hwnd, (HMENU)BUTTON3, NULL, NULL);
		hwndButton4 = CreateWindowEx(NULL, TEXT("Button"), TEXT("4.项目地址"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 325, 265, 50, hwnd, (HMENU)BUTTON4, NULL, NULL);
		SendMessage(text, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(hwndButton1, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(hwndButton2, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(hwndButton3, WM_SETFONT, (WPARAM)font, TRUE);
		SendMessage(hwndButton4, WM_SETFONT, (WPARAM)font, TRUE);
		break;
	}
	case WM_CTLCOLORSTATIC:
	{
		if ((HWND)lParam == GetDlgItem(hwnd, 1))
		{
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
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
			CreateWindowEx(NULL, L"Time_Input", L"输入", WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE | WM_CTLCOLORSTATIC, 150, 150, 410, 200, NULL, NULL, NULL, NULL);
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
			MessageBox(hwnd, L"点击确定开始录制(按‘ESC’结束)", L"准备开始", MB_OK);
			UpdateWindow(hwnd);
			break;
		}
		case BUTTON3:
		{

			IFileDialog* ifiledialog = NULL;
			HRESULT hresult = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&ifiledialog));
			if (SUCCEEDED(hresult))
			{
				DWORD dwFlags;
				hresult = ifiledialog->GetOptions(&dwFlags);
				hresult = ifiledialog->SetOptions(dwFlags);
				COMDLG_FILTERSPEC file_type[] =
				{
					{L"Text files", L"*.txt"},
				};
				hresult = ifiledialog->SetFileTypes(ARRAYSIZE(file_type), file_type);
				hresult = ifiledialog->SetFileTypeIndex(1);
				hresult = ifiledialog->Show(NULL);
				if (SUCCEEDED(hresult))
				{
					IShellItem* ishellitem;
					hresult = ifiledialog->GetResult(&ishellitem);
					LPWSTR file_path = NULL;
					hresult = ishellitem->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &file_path);
					if (SUCCEEDED(hresult))
					{
						CString storage_address = file_path;
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
							Sleep(10);
							display.detach();
						}
					}
					CoTaskMemFree(file_path);
					ishellitem->Release();
				}
				ifiledialog->Release();
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
	SetIni();

	WNDCLASSEX main_window, time_input, record_input, record_output, tips;

	//main_window属性
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

	//注册窗口
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

	if (0 == RegisterClassExW(&tips))
	{
		MessageBox(NULL, L"tips wrong", L"Regist", MB_OK);
		return 0;
	}

	//创建窗口
	HWND main_win = CreateWindowEx(NULL, L"Main", version, WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE | WM_CTLCOLORSTATIC, 100, 100, 300, 450, NULL, NULL, hInstance, NULL);

	ShowWindow(main_win, SW_SHOW);
	UpdateWindow(main_win);

	//数据刷新
	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}