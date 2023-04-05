//
// Created by Sabbrumm on 01.03.2023.
//
#include <string>
#ifndef LIST_LAB_BRUM_CUTS_H
#define LIST_LAB_BRUM_CUTS_H

#define SC SetConsoleCursorPosition
#define KEY_ESC 27
#define KEY_CONTROL 224
#define KEY_BACKSPACE 8
#define KEY_ENTER 13
#define KEY_CONTROL_DOWN 80
#define KEY_CONTROL_UP 72

#define KEY_CONTROL_RIGHT 77
#define KEY_CONTROL_LEFT 75
#define KEY_0 48
#define KEY_9 57

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100

void arrow(int boo);
void SetCur(int X, int Y);

void localize();
void window_fullscreen();
void window_fontsize(short fs);
void window_hidecursor();
void window_settitle(const wchar_t* myTitle);
void window_dec();
void interface_border(int width, int height);
int unicode_len(std::string s);

#endif //LIST_LAB_BRUM_CUTS_H
