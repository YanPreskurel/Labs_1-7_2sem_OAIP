#ifndef TREE_H
#define TREE_H

#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <QString>
#include "mainwindow.h"

template <typename T>
class AVLTree {
public:
    class Node {
    public:
        int key;
        T data;
        Node* left;
        Node* right;
        int height;

        Node() = default;
        ~Node() {

        }
    };


    int k=0;
    QString G;
    QVector<std::pair<int,QString>> V;

    Node* newNode(int key, T data = T())
    {
        Node* node = new Node();
        node->key = key;
        node->data = data;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1; // new node is initially
                          // added at leaf
        return(node);
    }

    Node* root = nullptr;

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int height(Node* node)
    {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    Node* rightRotate(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left),
            height(y->right)) + 1;
        x->height = max(height(x->left),
            height(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left),
            height(x->right)) + 1;
        y->height = max(height(y->left),
            height(y->right)) + 1;

        return y;
    }

    int getBalance(Node* node)
    {
        if (node == nullptr) {
            return 0;
        }
        int heightL = height(node->left);
        int heightR = height(node->right);
        return heightL - heightR;
    }

    Node* insert(Node* node, int key, T data = T())
    {
        /* 1. Perform the normal BST insertion */
        if (node == nullptr) {
            return (newNode(key, data));
        }

        if (key < node->key)
            node->left = insert(node->left, key, data);
        else if (key > node->key)
            node->right = insert(node->right, key, data);
        else // Equal keys are not allowed in BST
            return node;

        /* 2. Update height of this ancestor node */
        node->height = 1 + max(height(node->left), height(node->right));

        /* 3. Get the balance factor of this ancestor
            node to check whether this node became
            unbalanced */
        int balance = getBalance(node);

        // If this node becomes unbalanced, then
        // there are 4 cases

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }

    // Recursive function to delete a node
    // with given key from subtree with
    // given root. It returns root of the
    // modified subtree.
    Node* deleteNode(Node* root, int key)
    {

        if (!root) return root;

        if (key > root->key)
            root->right = deleteNode(root->right, key);
        else if (key < root->key)
            root->left = deleteNode(root->left, key);
        else
        {
            if (!root->left && !root->right)
            {
                delete root;
                root = nullptr;
            }
            else if (!root->left)
            {
                Node* temp = root;
                root = root->right;
                delete temp;
                temp = nullptr;
            }
            else if (!root->right)
            {
                Node* temp = root;
                root = root->left;
                delete temp;
                temp = nullptr;
            }
            else
            {
                Node* temp = root->right;
                while (temp->left)
                {
                    temp = temp->left;
                }
                root->key = temp->key;
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->key);
            }
        }


        // If the tree had only one node
        // then return
        if (root == nullptr)
            return root;

        // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
        root->height = 1 + max(height(root->left), height(root->right));

        // STEP 3: GET THE BALANCE FACTOR OF
        // THIS NODE (to check whether this
        // node became unbalanced)
        int balance = getBalance(root);

        // If this node becomes unbalanced,
        // then there are 4 cases

        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 &&getBalance(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // A utility function to print preorder
    // traversal of the tree.
    // The function also prints height
    // of every node

    void preOrder(Node* root)
    {
        if (root != nullptr)
        {
            std::pair<int,QString> tmp(root->key,root->data);
            V.push_back(tmp);
            preOrder(root->left);
            preOrder(root->right);
        }
    }


    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        if((!node->right && node->left) || (!node->left && node->right))
        {
            k++;
        }
        else if(!node->right && !node->left)
        {
            k+=2;
        }
        std::pair<int,QString> tmp(node->key,node->data);
        V.push_back(tmp);
        //std::cout << node->key << " ";
        inOrder(node->right);
    }


    void postOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        inOrder(node->right);
        std::pair<int,QString> tmp(node->key,node->data);
        V.push_back(tmp);
    }

    void wideOrder(Node* root) {
        std::queue<Node*> children;
        children.push(root);

        while (!children.empty()) {
            Node* node = children.front();
            children.pop();

            std::pair<int,QString> tmp(node->key,node->data);
            V.push_back(tmp);

            if (node->left)
                children.push(node->left);
            if (node->right)
                children.push(node->right);

        }
    }

    Node* findElement(Node* root, int key) {

        if (root == nullptr) {
            return nullptr;
        }

        if (root->key > key)
        {
            root->left = findElement(root->left, key);
        }
        else if (root->key < key)
        {
            root->right = findElement(root->right, key);
        }
        else
        {
            return root;
        }
    }


    void recursive_show(Node* cur, unsigned level = 1) {

        if (cur) {

            recursive_show(cur->right, level + 1);

            for (int i = 0; i < level; ++i)
                std::cout << '\t';

            std::cout << cur->key << '\n' << '\n';

            recursive_show(cur->left, level + 1);
        }
    }

    void printTree(Node* root, int space = 0) {
        if (root == nullptr){
            return;
        }
        const int COUNT = 3;
        space += COUNT;
        printTree(root->right, space);
        for (int i = COUNT; i < space; i++) {
            G += "  ";
        }
        QString tmp;
        G+=tmp.setNum(root->key);
        G+="\n";
        printTree(root->left, space);
    }

public:
    AVLTree() = default;
    ~AVLTree() {

    }

    void push(int key, T data = T()) {
        root = insert(root, key, data);
    }

    void pop(int key) {
        root = deleteNode(root, key);
    }

    void print() {
        printTree(root);
    }

    void output() {
        preOrder(root);
        std::cout << "\n\n";
        inOrder(root);
        std::cout << "\n\n";
        postOrder(root);
        std::cout << "\n\n";
        wideOrder(root);
        std::cout << "\n\n";
    }

    void find(int key) {
        Node* element = findElement(root, key);
        if (element != nullptr)
        {
            std::cout << element->key << "\n";
        }
        else
        {
            std::cout << "nullptr\n";
        }
        //std::cout << element != nullptr ? element->key : "nullptr";
    }
};

/*
template <typename T>
class Tree {
private:
    template<typename T>
    class Node {
    public:
        int key;
        T data;
        Node<T>* left;
        Node<T>* right;

        Node() = default;
        ~Node() {

        }
    };

    Node<T>* newNode(int key, T value = T()) {
        Node<T>* newNode = new Node<T>();
        newNode->key = key;
        newNode->data = value;
        newNode->left = nullptr;
        newNode->right = nullptr;

        return newNode;
    }

    Node<T>* root = nullptr;

    Node<T>* insert(Node<T>* node, int key, T value = T()) {
        if (node == nullptr) {
            return (newNode(key, value));
        }

        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else
            return node;

        return node;
    }

    void recursive_show(Node<T>* cur, unsigned level = 1) {

        if (cur) {

            recursive_show(cur->right, level + 1);

            for (int i = 0; i < level; ++i)
                std::cout << '\t';

            std::cout << cur->key << '\n' << '\n';

            recursive_show(cur->left, level + 1);
        }

    }

    void inOrder(Node<T>* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        //std::cout << node->key << " ";
        inOrder(node->right);
    }

public:
    Tree() = default;
    ~Tree() {

    }

    void push(int key, T data = T()) {
        root = insert(root, key, data);
    }

    void print() {
        recursive_show(root);
    }


};
*/


#endif // TREE_H
