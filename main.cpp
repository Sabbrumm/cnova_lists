#include <iostream>
#include "list/list.h"
#include "brum_cuts/brum_cuts.h"
#include <windows.h>
#include <conio.h>


#define SCR_WIDTH 85
#define SCR_HEIGHT 25
enum Points{
    makelist,
    deletelist,
    addtoend,
    delfromend,
    addindex,
    delindex,
    insertpart,
    delpart,
    reverse,
    sorting
};
enum SelectMode{
    Buttons, Lists
};
enum LPoints{l1, l2};
SelectMode selmode = Buttons;
// Область списков - с 22 по 24 строку
// остальной экран - с 2 по 21
// плюс ограничение
int ExitVar = 0;

int point = makelist;
int lspoint = l1;



List *list1 = nullptr;
List *list2 = nullptr;
using namespace std;




void printCentral(std::string button, int chosen=0){
    if (!chosen){
        for (int i = 0; i<(SCR_WIDTH - unicode_len(button))/2; i++){
            cout<<" ";
        }
        cout<<button<<"   ";
    }
    else{
        for (int i = 0; i<(SCR_WIDTH - unicode_len(button))/2 - 3; i++){
            cout<<" ";
        }
        cout << ">> " << button << " <<";
    }

}

void coutn(string c, int n){
    for (int i = 0; i<n; i++){
        cout<<c;
    }
}

int count_spaces_list(List *subj){
    int b = 0;
    b += (subj->len()-1)*4;
    string buf = "";
    for (int i = 0; i<subj->len(); i++){
        buf = to_string(*subj->get(i));
        b+= unicode_len(buf);
    }
    b+=2;
    return (SCR_WIDTH-b)/2;
}

string list_to_string(List *subj){
    if (subj==nullptr){
        return string(SCR_WIDTH, ' ');
    }
    else if (subj->len()==0){
        return "{Пустой список}";
    }
    else {
        string buf = "{";
        for (int i = 0; i<subj->len(); i++){
            buf.append(to_string(*subj->get(i)));
            if (i!=subj->len()-1){
                buf.append(" -> ");
            }
        }
        buf.append("}");
        return buf;
    }
}


void startscreen(){
    SetCur(0, 3); printCentral("[Создать список]", point==makelist);
    SetCur(0, 4); printCentral("[Удалить список]", point==deletelist);

    SetCur(0, 6); printCentral("[Добавить элемент в конец]", point==addtoend);
    SetCur(0, 7); printCentral("[Удалить последний элемент]", point==delfromend);

    SetCur(0, 9); printCentral("[Добавить элемент по индексу]", point==addindex);
    SetCur(0, 10); printCentral("[Удалить элемент по индексу]", point==delindex);

    SetCur(0, 12); printCentral("[Дублировать часть списка]", point==insertpart);
    SetCur(0, 13); printCentral("[Удалить часть списка]", point==delpart);

    SetCur(0, 15); printCentral("[Перевернуть список]", point==reverse);
    SetCur(0, 16); printCentral("[Отсортировать список]", point==sorting);
}
void listsprinter(){
    if (selmode==Buttons){
        SetCur(0, 21); printCentral(list_to_string(list1)); cout<<"            ";
        SetCur(0, 23); printCentral(list_to_string(list2)); cout<<"            ";
    }
    else if (selmode==Lists){

        SetCur(0, 21); printCentral(list_to_string(list1), lspoint==l1); cout<<"            ";
        SetCur(0, 23); printCentral(list_to_string(list2), lspoint==l2); cout<<"            ";
    }
}
void hintprinter(){}

void Border(){
    cout << string(SCR_WIDTH, '=') <<
            string(SCR_HEIGHT-5,'\n') <<
            string(SCR_WIDTH, '=') <<
            string(4,'\n') <<
            string(SCR_WIDTH, '=');
    SetCur(0,1); cout << "Горячие клавиши:";
    SetCur(0,2); cout << "[ESC] - выход";

}
void ConsoleColorBlack() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}
void ConsoleColorWhite() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

void ExclamationWindow(const std::string header, const std::string footer){
    const int WIN_WIDTH = 33;
    const int WIN_HEIGHT = 7;

    // Задание окна

    SetCur(
            (SCR_WIDTH-WIN_WIDTH)/2,
            (SCR_HEIGHT-WIN_HEIGHT)/2
            );
    cout<<"┏"; coutn("━", WIN_WIDTH-2); cout<<"┓";
    for (int i=1; i<6; i++){
        SetCur(
                (SCR_WIDTH-WIN_WIDTH)/2,
                (SCR_HEIGHT-WIN_HEIGHT)/2+i
        );
        cout<<"┃";coutn(" ", WIN_WIDTH-2); cout<<"┃";
    }
    SetCur(
            (SCR_WIDTH-WIN_WIDTH)/2,
            (SCR_HEIGHT-WIN_HEIGHT)/2+6
    );
    cout<<"┗"; coutn("━", WIN_WIDTH-2); cout<<"┛";

    int HEADERCOORD = (WIN_WIDTH-2 - unicode_len(header))/2 + (SCR_WIDTH-WIN_WIDTH)/2+1;
    SetCur(
            HEADERCOORD,
            (SCR_HEIGHT-WIN_HEIGHT)/2+1
    );
    std::cout<<header;
    int FOOTERCOORD = (WIN_WIDTH-2 - unicode_len(footer))/2 + (SCR_WIDTH-WIN_WIDTH)/2+1;
    SetCur(
            FOOTERCOORD,
            (SCR_HEIGHT-WIN_HEIGHT)/2+3
    );
    std::cout<<footer;
    getch();
    SetCur(
            (SCR_WIDTH-WIN_WIDTH)/2,
            (SCR_HEIGHT-WIN_HEIGHT)/2
    );
    for (int i=0; i<WIN_HEIGHT; i++) {
        SetCur(
                (SCR_WIDTH - WIN_WIDTH) / 2,
                (SCR_HEIGHT - WIN_HEIGHT) / 2 + i
        );
        coutn(" ", WIN_WIDTH);
    }
}

int IntInputWindow(const std::string header){
    int buffer_value=0;
    int escape = 0;
    const int WIN_WIDTH = 33;
    const int WIN_HEIGHT = 8;

    // Задание окна

    //Печать рамки
    SetCur(
            (SCR_WIDTH-WIN_WIDTH)/2,
            (SCR_HEIGHT-WIN_HEIGHT)/2
    );
    cout<<"┏"; coutn("━", WIN_WIDTH-2); cout<<"┓";
    for (int i=1; i<WIN_HEIGHT; i++){

        SetCur(
                (SCR_WIDTH-WIN_WIDTH)/2,
                (SCR_HEIGHT-WIN_HEIGHT)/2+i
        );
        cout<<"┃";

        ConsoleColorBlack();
        if (i==3){
            ConsoleColorWhite();
        }
        coutn(" ", WIN_WIDTH-2);
        ConsoleColorBlack();
        cout<<"┃";

    }
    SetCur(
            (SCR_WIDTH-WIN_WIDTH)/2,
            (SCR_HEIGHT-WIN_HEIGHT)/2+WIN_HEIGHT-1
    );
    cout<<"┗"; coutn("━", WIN_WIDTH-2); cout<<"┛";
    //

    //Печать заголовка
    int HEADERCOORD = (WIN_WIDTH-2 - unicode_len(header))/2 + (SCR_WIDTH-WIN_WIDTH)/2+1;
    SetCur(
            HEADERCOORD,
            (SCR_HEIGHT-WIN_HEIGHT)/2+1
    );
    std::cout<<header;
    //

    //Печать поля ввода;
    ConsoleColorWhite();
    int ENTERFIELD = (WIN_WIDTH-2 - unicode_len(to_string(buffer_value)))/2 + (SCR_WIDTH-WIN_WIDTH)/2+1;
    SetCur(
            ENTERFIELD,
            (SCR_HEIGHT-WIN_HEIGHT)/2+3
    );
    std::cout<<buffer_value;
    ConsoleColorBlack();
    //

    //Печать подсказки
    int HINTFIELD = (WIN_WIDTH-2 - unicode_len(" [ESC]                 [Enter] "))/2 + (SCR_WIDTH-WIN_WIDTH)/2+1;
    SetCur(
            HINTFIELD,
            (SCR_HEIGHT-WIN_HEIGHT)/2+5
    );
    std::cout<<"  Отмена                Ввод   ";
    SetCur(
            HINTFIELD,
            (SCR_HEIGHT-WIN_HEIGHT)/2+6
    );
    std::cout<<"   [ESC]               [Enter] ";

    // Перехват ввода
    int ENTERFIELD2 = (WIN_WIDTH-3)/2 + (SCR_WIDTH-WIN_WIDTH)/2+1;
    while (true){

        ConsoleColorWhite();


        SetCur(
                ENTERFIELD2,
                (SCR_HEIGHT-WIN_HEIGHT)/2+3
        );
        cout<<"  ";
        SetCur(
                ENTERFIELD2,
                (SCR_HEIGHT-WIN_HEIGHT)/2+3
        );
        std::cout<<buffer_value;
        ConsoleColorBlack();
        int key = getch();
        if (key>=KEY_0 and key<=KEY_9){
            int num = key-KEY_0;
            if (buffer_value*10+num<100){
                buffer_value = buffer_value*10+num;
            }
        }
        else if (key==KEY_BACKSPACE){
            buffer_value=buffer_value/10;
        }
        else if (key==KEY_ESC){
            escape = 1;
            break;
        }
        else if (key==KEY_ENTER){
            break;
        }
    }



    // Завершение работы окна
    SetCur(
            (SCR_WIDTH-WIN_WIDTH)/2,
            (SCR_HEIGHT-WIN_HEIGHT)/2
    );
    for (int i=0; i<WIN_HEIGHT; i++) {
        SetCur(
                (SCR_WIDTH - WIN_WIDTH) / 2,
                (SCR_HEIGHT - WIN_HEIGHT) / 2 + i
        );
        coutn(" ", WIN_WIDTH);
    }
    if (escape){
        return -1;
    }
    else{
        return buffer_value;
    }
}


int selectlist(){
    if (list1== nullptr){
        lspoint = l2;
    }
    else if (list2== nullptr){
        lspoint = l1;
    }
    else {
        lspoint = l1;
    }
    while(true){
        listsprinter();
        switch (getch()){
            case KEY_ESC:
                return 0;
            case KEY_CONTROL:
                switch (getch()){
                    case KEY_CONTROL_DOWN:
                        if (list1!= nullptr and list2 != nullptr){
                            lspoint++;
                            if (lspoint>l2){
                                lspoint = l1;
                            }
                        }
                        break;
                    case KEY_CONTROL_UP:
                        if (list1!= nullptr and list2 != nullptr){
                            lspoint--;
                            if (lspoint<l1){
                                lspoint = l2;
                            }
                        }
                        break;
                }
                break;
            case KEY_ENTER:
                if (lspoint==l1){
                    return 1;
                }
                else{
                    return 2;
                }
        }
    }

};

void Controls(){
    switch (getch()){
        case KEY_ESC:
            ExitVar = 1;
            break;
        case KEY_CONTROL:
            switch (getch()){
                case KEY_CONTROL_DOWN:

                    point++;
                    if (point>sorting){
                        point = makelist;
                    }
                    break;

                case KEY_CONTROL_UP:

                    point--;
                    if (point<makelist){
                        point = sorting;
                    }
                    break;


            }
            break;
        case KEY_ENTER:
            switch (point){
                case makelist:
                    if (list1==nullptr and list2==nullptr){
                        list1 = new List();
                    }
                    else if(list1==nullptr){
                        list1 = new List();
                    }
                    else if (list2==nullptr){
                        list2 = new List();
                    }
                    else {
                        ExclamationWindow("Ошибка", "2 списка - максимум");
                    }

                    break;
                case deletelist:
                    if (list1== nullptr and list2 == nullptr){
                        ExclamationWindow("Ошибка", "Нет ни одного списка");
                    }
                    else {
                        selmode = Lists;
                        switch (selectlist()){
                            case 0:
                                break;
                            case 1:
                                list1->clear();
                                delete list1;
                                list1 = nullptr;
                                break;
                            case 2:
                                list2->clear();
                                delete list2;
                                list2 = nullptr;
                                break;
                        }
                        selmode = Buttons;
                    }
                    break;
                case addtoend:
                    if (list1== nullptr and list2 == nullptr){
                        ExclamationWindow("Ошибка", "Нет ни одного списка");
                    }
                    else{
                        int val = IntInputWindow("Введите значение от 0 до 99");
                        if (val==-1)
                            break;
                        else{
                            startscreen();
                            selmode = Lists;
                            switch (selectlist()){
                                case 0:
                                    break;
                                case 1:
                                    if (list1->len()<10){
                                        list1->append(val);
                                    }
                                    else {
                                        ExclamationWindow("Ошибка", "Ограничение на длину - 10");
                                    }
                                    break;


                                case 2:
                                    if (list2->len()<10){
                                        list2->append(val);
                                    }

                                    else
                                        ExclamationWindow("Ошибка", "Ограничение на длину - 10");
                                    break;

                            }
                            selmode = Buttons;
                        }
                    }
                    listsprinter();
                    startscreen();
                    break;
                case delfromend:
                    if (list1== nullptr and list2 == nullptr){
                        ExclamationWindow("Ошибка", "Нет ни одного списка");
                    }
                    else{
                        selmode = Lists;
                        switch (selectlist()){
                            case 0:
                                break;
                            case 1:
                                if (list1->len()>0){
                                    list1->pop(list1->len()-1);
                                }
                                else {
                                    ExclamationWindow("Ошибка", "Невыполнимо в пустом списке");
                                }
                                break;


                            case 2:
                                if (list2->len()>0){
                                    list2->pop(list2->len()-1);
                                }

                                else
                                    ExclamationWindow("Ошибка", "Невыполнимо в пустом списке");
                                break;

                        }
                        selmode = Buttons;
                    }

                    listsprinter();
                    break;
                case addindex:
                    if (list1== nullptr and list2 == nullptr){
                        ExclamationWindow("Ошибка", "Нет ни одного списка");
                    }
                    else{
                        int val = IntInputWindow("Введите значение от 0 до 99");

                        if (val==-1)
                            break;

                        int index = IntInputWindow("Введите индекс элемента");
                        if (index==-1)
                            break;
                        startscreen();
                        selmode = Lists;
                        switch (selectlist()){
                            case 0:
                                break;
                            case 1:
                                if (list1->len()>10){
                                    ExclamationWindow("Ошибка", "Ограничение на длину - 10");
                                    break;
                                }
                                else if (index>=list1->len() and list1->len()!=0){
                                    ExclamationWindow("Ошибка", "Недопустимый индекс");
                                    break;
                                }
                                else{
                                    if (list1->len()==0){
                                        list1->append(val);
                                        break;
                                    }
                                    else{
                                        list1->insert(index, val);
                                        break;
                                    }

                                }



                            case 2:
                                if (list2->len()>10){
                                    ExclamationWindow("Ошибка", "Ограничение на длину - 10");
                                    break;
                                }
                                else if (index>list2->len() and list2->len()!=0){
                                    ExclamationWindow("Ошибка", "Недопустимый индекс");
                                    break;
                                }
                                else{
                                    if (list2->len()==0){
                                        list2->append(val);
                                        break;
                                    }
                                    else{
                                        list2->insert(index, val);
                                        break;
                                    }
                                }

                        }
                        selmode = Buttons;

                        startscreen();
                        listsprinter();
                    }
                    break;
                case delindex:
                    if (list1== nullptr and list2 == nullptr){
                        ExclamationWindow("Ошибка", "Нет ни одного списка");
                    }
                    else{
                        int index = IntInputWindow("Введите индекс элемента");
                        if (index==-1)
                            break;
                        startscreen();
                        selmode = Lists;
                        switch (selectlist()){
                            case 0:
                                break;
                            case 1:
                                if (list1->len()<=0){
                                    ExclamationWindow("Ошибка", "Невыполнимо в пустом списке");
                                    break;
                                }
                                else if (index>=list1->len()){
                                    ExclamationWindow("Ошибка", "Недопустимый индекс");
                                    break;
                                }
                                else{
                                    list1->pop(index);
                                    break;
                                }



                            case 2:
                                if (list2->len()<=0){
                                    ExclamationWindow("Ошибка", "Невыполнимо в пустом списке");
                                    break;
                                }
                                else if (index>list2->len()){
                                    ExclamationWindow("Ошибка", "Недопустимый индекс");
                                    break;
                                }
                                else{
                                    list2->pop(index);
                                    break;
                                }

                        }
                        selmode = Buttons;

                        startscreen();
                        listsprinter();
                    }
                    break;
                case insertpart:
                    if (list1== nullptr and list2 == nullptr){
                        ExclamationWindow("Ошибка", "Нет ни одного списка");
                    }
                    else{
                        int index1 = IntInputWindow("Введите первый индекс");
                        if (index1==-1){
                            break;
                        }
                        int index2 = IntInputWindow("Введите второй индекс");
                        if (index2==-1){
                            break;
                        }
                        if (index2<index1){
                            ExclamationWindow("Ошибка", "Неверный диапазон");
                            break;
                        }
                        startscreen();
                        selmode = Lists;
                        switch (selectlist()){
                            case 0:
                                break;
                            case 1:
                                if (index1>list1->len() or index2>list1->len()){
                                    ExclamationWindow("Ошибка", "Неверный диапазон");
                                    break;
                                }
                                if (index2-index1+1+list1->len()>10){
                                    ExclamationWindow("Ошибка", "Ограничение на длину - 10");
                                    break;
                                }
                                for (int i = index1; i<index2+1; i++){
                                    list1->append(*list1->get(i));
                                }
                                break;



                            case 2:
                                if (index1>list2->len() or index2>list2->len()){
                                    ExclamationWindow("Ошибка", "Неверный диапазон");
                                    break;
                                }
                                if (index2-index1+1+list2->len()>10){
                                    ExclamationWindow("Ошибка", "Ограничение на длину - 10");
                                    break;
                                }
                                for (int i = index1; i<index2+1; i++){
                                    list2->append(*list2->get(i));
                                }
                                break;

                        }
                        selmode = Buttons;
                    }
                    break;
                case delpart:
                    if (list1== nullptr and list2 == nullptr){
                        ExclamationWindow("Ошибка", "Нет ни одного списка");
                    }
                    else{
                        int index1 = IntInputWindow("Введите первый индекс");
                        if (index1==-1){
                            break;
                        }
                        int index2 = IntInputWindow("Введите второй индекс");
                        if (index2==-1){
                            break;
                        }
                        if (index2<index1){
                            ExclamationWindow("Ошибка", "Неверный диапазон");
                            break;
                        }
                        startscreen();
                        selmode = Lists;
                        switch (selectlist()){
                            case 0:
                                break;
                            case 1:
                                if (list1->len()==0){
                                    ExclamationWindow("Ошибка", "Невыполнимо в пустом списке");
                                    break;
                                }
                                if (index1>list1->len() or index2>list1->len()){
                                    ExclamationWindow("Ошибка", "Неверный диапазон");
                                    break;
                                }
                                for (int i = index1; i<index2+1; i++){
                                    list1->pop(i);
                                }
                                break;



                            case 2:
                                if (list2->len()==0){
                                    ExclamationWindow("Ошибка", "Невыполнимо в пустом списке");
                                    break;
                                }
                                if (index1>list2->len() or index2>list2->len()){
                                    ExclamationWindow("Ошибка", "Неверный диапазон");
                                    break;
                                }
                                for (int i = index1; i<index2+1; i++){
                                    list2->pop(i);
                                }
                                break;

                        }
                        selmode = Buttons;
                    }
                    break;
                case reverse:
                    if (list1== nullptr and list2 == nullptr){
                        ExclamationWindow("Ошибка", "Нет ни одного списка");
                    }
                    else{
                        selmode = Lists;
                        switch (selectlist()){
                            case 0:
                                break;
                            case 1:
                                list1->reverse();
                                break;
                            case 2:
                                list2->reverse();
                                break;
                        }
                        selmode = Buttons;
                    }
                    break;
                case sorting:
                    if (list1== nullptr and list2 == nullptr){
                        ExclamationWindow("Ошибка", "Нет ни одного списка");
                    }
                    else{
                        selmode = Lists;
                        switch (selectlist()){
                            case 0:
                                break;
                            case 1:
                                list1->sort();
                                break;
                            case 2:
                                list2->sort();
                                break;
                        }
                        selmode = Buttons;
                    }
                    break;


            }

            break;
    }
}

int main(){
    window_settitle(L"Односвязный список");
    window_dec();
    Border();
    while (!ExitVar){
        startscreen();
        listsprinter();
        Controls();
    }

    return 0;
}