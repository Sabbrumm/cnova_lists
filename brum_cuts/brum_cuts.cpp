//
// Created by Sabbrumm on 01.03.2023.
//

#include "brum_cuts.h"
#include <iostream>
#include <windows.h>
#include <algorithm>
using namespace std;

void arrow(int boo){
    if (boo){
        std::cout<<" <--"<<std::endl;
    } else std::cout<<std::endl;
}

void SetCur(int X, int Y){
    COORD cursor;
    cursor.X = X;
    cursor.Y = Y;
    SC(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
}
void localize() {
    SetConsoleOutputCP(CP_UTF8);
}

void window_fullscreen(){
    SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
}

void window_fontsize(short fs){
    CONSOLE_FONT_INFOEX finf;
    GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 1, &finf);
    finf.dwFontSize.X = fs;
    finf.dwFontSize.Y = fs*2;
    finf.cbSize = sizeof(finf);
    lstrcpyW(finf.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 1, &finf);
}

void window_hidecursor(){
    CONSOLE_CURSOR_INFO cinf;
    cinf.dwSize = 100;
    cinf.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cinf);
}

void window_settitle(const wchar_t* myTitle){
    SetConsoleTitleW(myTitle);
}

void window_dec(){
    localize();
    window_fullscreen();
    window_hidecursor();
    window_fontsize(17);
}

void interface_border(int width, int height){
    cout << string(width, '=') << string(height-2,'\n') << string(width, '=') << endl;
}

int unicode_len(std::string s){
    return (s.length() - count_if(s.begin(), s.end(), [](char c)->bool { return (c & 0xC0) == 0x80; }));
}