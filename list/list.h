//
// Created by Sabbrumm on 01.03.2023.
//

#ifndef LIST_LAB_LIST_H
#define LIST_LAB_LIST_H
#pragma once

struct Node{
    int Data;
    Node *next = nullptr;
};

class List{
private:
    int _lenght = 0;
    Node *FirstNode = nullptr;
    Node *LastNode = nullptr;
public:
    List();
    void append(int obj);
    void sort();
    int len();
    void pop(int index);
    void reverse();
    Node *getNode(int index);
    int *get(int index);
    void clear();
    int* operator [] (int index);
    void swap(int index1, int index2);
    void print();
    void insert(int index, int val);
};

#endif //LIST_LAB_LIST_H
