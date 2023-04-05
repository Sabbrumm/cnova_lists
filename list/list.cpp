//
// Created by Sabbrumm on 01.03.2023.
//
#include <iostream>
#include "list.h"

List::List() = default;

void List::append(int obj) {
    Node *newnode = new Node();
    newnode->Data=obj;

    //Если первый узел в списке пуст, то теперь первый узел - новый
    if (this->FirstNode == nullptr){
        this->FirstNode = newnode;
    }

    // Если последний узел не пуст, то теперь последний ссылается на новый.
    if (this->LastNode!= nullptr){
        this->LastNode->next= newnode;
    }
    this->LastNode = newnode;
    this->_lenght++;
}

void List::sort() {
    int i = 0;
    while (i< this->len()-1){
        int j = 0;
        while (j<this->len()-1-i){
            if (*this->get(j) < *this->get(j+1)){
                this->swap(j, j+1);
            }
            j++;
        }
        i++;
    }
}

int List::len() {
    return this->_lenght;
}

void List::pop(int index) {
    Node *tempnode = this->getNode(index);
    if (tempnode != nullptr){ //если индекс валидный
        if (tempnode->next != nullptr){ // если посередине или первый узел

            if (tempnode == this->FirstNode) { //если это первый узел
                this->FirstNode = tempnode->next;
                delete tempnode;
            }

            else { //если это где-то в середине
                Node *tempprevnode = this->getNode(index-1);
                tempprevnode->next = tempnode->next;
                delete tempnode;
            }

        }
        else { //если последний или единственный
            if (this->_lenght==1){ //если единственный
                this->LastNode = nullptr;
                this->FirstNode = nullptr;
                delete tempnode;
            }
            else {
                Node *tempprevnode = this->getNode(index-1);
                tempprevnode->next = nullptr;
                this->LastNode = tempprevnode;
                delete tempnode;
            }

        }
        this->_lenght--;
    }
}

void List::reverse() {
    List temprev;
    for (int i = this->_lenght; i>0; i--){
        temprev.append(*this->get(i-1));
    }

    this->clear();

    for (int i = 0; i<temprev._lenght; i++){
        this->append(*temprev.get(i));
    }
}

Node *List::getNode(int index) {
    if (index>=0 and index<_lenght){
        Node* tempnode = this->FirstNode; //узел с индексом ноль
        for (int i=0; i<index; i++){
            tempnode = tempnode->next;
        }
        return tempnode;
    }
    return nullptr;
}

int *List::get(int index) {
    Node *tn = this->getNode(index);
    if (tn!= nullptr){
        return &(tn->Data);
    }
    return nullptr;
}

void List::clear() {
    while (this->_lenght!=0){
        this->pop(0);
    }
}

int *List::operator[](int index) {
    return this->get(index);
}

void List::swap(int index1, int index2) {
    if (index1>=0 and index1<this->len() and
        index2>=0 and index2<this->len() and
        index1!=index2){
        Node *node1 = this->getNode(index1),
                *node2 = this->getNode(index2);
        List temprev;
        for (int i=0; i<this->len(); i++){
            if (i!=index1 and i!=index2){
                temprev.append(*this->get(i));
            }
            else if (i==index1){
                temprev.append(node2->Data);
            }
            else if (i==index2){
                temprev.append(node1->Data);
            }
        }

        this->clear();

        for (int i = 0; i<temprev._lenght; i++){
            this->append(*temprev.get(i));
        }
    }
}

void List::print() {
    for (int i=0; i<this->len(); i++){
        std::cout << *this->get(i);
        if (i!= this->len()-1){
            std::cout << " -> ";
        }
    }
    std::cout<<"\n";
}

void List::insert(int index, int val) {
    if (index>=0 and index<this->len()){
        List templist;

        for (int i=0; i<this->len(); i++){
            if (i==index)
                templist.append(val);
            templist.append(*this->get(i));
        }

        this->clear();

        for (int i = 0; i<templist._lenght; i++){
            this->append(*templist.get(i));
        }

    }


}
