#pragma once
#include <assert.h>


template <typename T>
class stack {
private:

    class Node {
    public:
        Node* next;
        T data;

        Node() {
            this->next = nullptr;
            this->data = T();
        }

        Node(T data = T()) {
            next = nullptr;
            this->data = data;
        }

        ~Node() {

        }
    };

    Node* head;
    int size;


public:

    stack() {
        this->head = nullptr;
        size = 0;
    }

    ~stack() {
        clear();
    }

    void push(T data) {
        Node* tmp = new Node(data);

        if (head == nullptr) {
            tmp->next = nullptr;
            head = tmp;
        }
        else {
            tmp->next = head;
            head = tmp;
        }
        size++;
    }

    void pop() {
        assert(size > 0 && "size = 0");
        Node* tmp = head;
        if (size == 1) {
            delete tmp;
            head =  nullptr;
        }
        else {
            head = head->next;
            delete tmp;
        }
        size--;
    }

    T get() {
        if(size)
            return head->data;
    }

    int getSize() {
        return size;
    }

    T& operator[](const int index) {
        assert(size > index && "out of range");

        Node* current = this->head;
        int counter = 0;
        while (current != nullptr) {
            if (counter == index) {
                return current->data;
            }
            current = current->next;
            counter++;
        }
    }

    bool isEmpty() {
        return !size;
    }

    void clear() {
        while (size) {
            pop();
        }
    }

};