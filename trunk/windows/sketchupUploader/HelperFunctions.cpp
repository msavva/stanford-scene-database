#include "Main.h"

void ModifyKey(UINT Key, bool Up)
{
    INPUT CurInput;
    CurInput.type = INPUT_KEYBOARD;
    CurInput.ki.wVk = Key;
    CurInput.ki.wScan = 0;
    CurInput.ki.time = 0;
    CurInput.ki.dwExtraInfo = 0;
    if(Up)
    {
        CurInput.ki.dwFlags = KEYEVENTF_KEYUP;
    }
    else
    {
        CurInput.ki.dwFlags = 0;
    }
    SendInput(1, &CurInput, sizeof(INPUT));
}

void SendKey(UINT Key, bool Ctrl, bool Alt)
{
    Sleep(500);
    if(Ctrl)
    {
        ModifyKey(KEY_CTRL, false);
    }
    if(Alt)
    {
        ModifyKey(KEY_ALT, false);
    }
    ModifyKey(Key, false);
    ModifyKey(Key, true);
    if(Ctrl)
    {
        ModifyKey(KEY_CTRL, true);
    }
    if(Alt)
    {
        ModifyKey(KEY_ALT, true);
    }
    Sleep(250);
}

void BlockOnKey(UINT Key)
{
    cout << "Blocking until KEY_NUMPADADD key pressed" << endl;
    bool KeyPressed = false;
    while(!KeyPressed)
    {
        if(GetAsyncKeyState(Key) != 0)
        {
            KeyPressed = true;
        }
        Sleep(200);
    }
    
}

void RandomSleepEvent()
{
    Sleep(2000 + rand() % 1000);
    if(rand() % 100 == 0)
    {
        cout << "Small sleep..." << endl;
        Sleep(10000);
    }
    if(rand() % 1000 == 0)
    {
        cout << "Big sleep..." << endl;
        Sleep(60000);
    }
}

void CopyStringToClipboard(const string &s)
{
    OpenClipboard(NULL);
    EmptyClipboard();

    HGLOBAL GlobalHandle;
    UINT BytesToCopy = s.length() + 1;
    GlobalHandle = GlobalAlloc(GMEM_MOVEABLE, BytesToCopy);
    if(GlobalHandle != NULL)
    {
        BYTE *StringPointer = (BYTE*)GlobalLock(GlobalHandle); 
        memcpy(StringPointer, s.c_str(), BytesToCopy); 
        GlobalUnlock(GlobalHandle);
        SetClipboardData(CF_TEXT, GlobalHandle);
    }
    CloseClipboard();
}

void ClickMouse(int x, int y)
{
    SetCursorPos(x, y);
    mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
    mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP, x, y, 0, 0);
}