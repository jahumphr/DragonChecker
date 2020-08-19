#include <iostream>
#include <windows.h>

#define VK_KEY_1	0x31

void moveMouse(int x, int y);
void mouseClick();
void escape();
bool checkPixel();
void attemptTar();

int main() {

    Sleep(10000);

    //loops until dragon has spawned
    while (1){

        moveMouse(740, 790);
        Sleep(1023);
        mouseClick();
        Sleep(15000);
        attemptTar();
        Sleep(1000);
        if (checkPixel()) {
            Beep(500, 20000);
            break;
        }

        escape();
        Sleep(2300);
        moveMouse(750, 493);
        Sleep(1400);
        mouseClick();
        Sleep(43421);

         }

    return 0;
}

//Moves cursor to input coordinates
void moveMouse(int x, int y){

    //get screen size/resolution information
    double screenResWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
    double screenResHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;

    double dx = x*(65535.0f/screenResWidth);
    double dy = y*(65535.0f/screenResHeight);

    //setup input and assign values
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
    input.mi.dx = LONG(dx);
    input.mi.dy = LONG(dy);

    ::SendInput(1, &input, sizeof(INPUT));
}

void mouseClick(){
    INPUT input = {0};

    //click down
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    ::SendInput(1, &input, sizeof(INPUT));

    //click release
    ::SecureZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    ::SendInput(1, &input, sizeof(INPUT));
}

void escape(){
    INPUT input = {0};

    //setup ESCAPE as input key
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VkKeyScanA(VK_ESCAPE);
    SendInput(1, &input, sizeof(INPUT));
    SecureZeroMemory(&input, sizeof(INPUT));

    //key release
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

//in-game Lua script to attempt to target dragon by pressing 1
void attemptTar(){
    INPUT input = {0};

    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VkKeyScanA(VK_KEY_1);
    SendInput(1, &input, sizeof(INPUT));
    SecureZeroMemory(&input, sizeof(INPUT));

    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

//check if dragon has spawned
bool checkPixel(){
    POINT p;
    COLORREF color;
    HDC hdc;
    BOOL b;

    hdc = GetDC(NULL);
    if (hdc == NULL)
        return false;

    moveMouse(410, 42);
    if (!GetCursorPos(&p))
        return false;

    color = GetPixel(hdc, p.x, p.y);

    ReleaseDC(NULL, hdc);

    //if pixel at cursor location is correct RGB, dragon has been targeted
    if (GetRValue(color) == 255 && GetGValue(color) == 209 && GetBValue(color) == 0){
        return true;
    }
    return false;


}