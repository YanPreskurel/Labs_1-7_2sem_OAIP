#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include "stack/stack/stack.h"
#include <vector>
#include <iostream>
#include <QString>

template <typename T>
class HashTable {
public:

    class Item {
    public:
        int key;
        T data;

        Item() {
            this->key = int();
            this->data = T();
        }

        Item(int key, T data = T()) {
            this->key = key;
            this->data = data;
        }
    };

    std::vector<stack<Item>> vector;
    int size;
    size_t m_size = 0;
    QString s = "";

public:
    HashTable() {
        this->vector.resize(97);
        this->size = this->vector.size();
    }

    int hash(int key) {
        return key % this->size;
    }

    void insert(int key, T data = T()) {
        int index = hash(key);
        Item tmp(key, data);
        m_size++;

        vector[index].push(tmp);
    }

    void search(int key) {
        s = "";
        QString q;
        int index = hash(key);
        for (int i = 0; i < vector[index].getSize(); i++) {
            if (vector[index][i].key == key) {
                QString w;
                q += "key : ";
                q+=w.setNum(vector[index][i].key);
                q+=" data : ";
                q+=vector[index][i].data;
                q+="\n";
            }
        }
        s += q;
    }

    bool contains(int key)
    {
        int index = hash(key);
        for (int i = 0; i < vector[index].getSize(); i++) {
            if (vector[index][i].key == key) {
                return true;
            }
        }
        return false;
    }

    bool empty() {
        return !m_size;
    }

    void deleteByKey(int key) {
        int index = hash(key);

        if (!vector[index].isEmpty()) {
            stack<Item> newStack;
            while (vector[index].getSize()) {
                if (vector[index].get().key == key) {
                    vector[index].pop();
                    m_size--;
                    break;
                }
                newStack.push(vector[index].get());
                vector[index].pop();
            }
            while (newStack.getSize()) {
                vector[index].push(newStack.get());
                newStack.pop();
            }
            std::cout << vector[index].getSize();
        }
    }
};


#endif // HASHTABLE_H
