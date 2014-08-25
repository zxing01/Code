//
//  AVLTree.h
//  Code
//
//  Created by Zhi Xing on 8/21/14.
//  Copyright (c) 2014 Zhi Xing. All rights reserved.
//

#ifndef __Code__AVLTree__
#define __Code__AVLTree__

#include <stack>

namespace Code {
    // type T needs to have copy constructor, operator< and operator== implemented
    template <typename T>
    class AVLTree {
    public:
        AVLTree(): _size(0), _root(nullptr) {}
        int size() const;
        void insert(const T &value);
        void remove(const T &value);
        void inorderTraversal(void (*)(T&));
        void preorderTraversal(void (*)(T&));
        void postorderTraversal(void (*)(T&));
    private:
        struct Node {
            T elem;
            int height;
            Node *left;
            Node *right;
            Node(const T &value): elem(value), height(1), left(nullptr), right(nullptr) {}
        };
        int _size;
        Node *_root;
        Node *_insert(Node *root, const T &value);
        Node *_remove(Node *root, const T &value);
        Node *_rotateLeft(Node *root);
        Node *_rotateRight(Node *root);
        Node *_balance(Node *root);
        int _height(Node *root) const;
        int _heightDiff(Node *root) const;
    };
}

using namespace std;
using namespace Code;

///////////////////////////////////////////////////////////////////////////////
template <typename T>
int AVLTree<T>::size() const {
    return _size;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void AVLTree<T>::insert(const T &value) {
    _root = _insert(_root, value);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void AVLTree<T>::remove(const T &value) {
    _root = _remove(_root, value);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void AVLTree<T>::inorderTraversal(void (*operation)(T&)) {
    stack<Node*> stk;
    Node* cur = _root;
    while (cur || !stk.empty()) {
        if (cur) {
            stk.push(cur);
            cur = cur->left;
        }
        else {
            cur = stk.top();
            stk.pop();
            operation(cur->elem);
            cur = cur->right;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void AVLTree<T>::preorderTraversal(void (*operation)(T&)) {
    stack<Node*> stk;
    Node* cur = _root;
    while (cur || !stk.empty()) {
        if (cur) {
            operation(cur->elem);
            stk.push(cur);
            cur = cur->left;
        }
        else {
            cur = stk.top()->right;
            stk.pop();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void AVLTree<T>::postorderTraversal(void (*operation)(T&)) {
    stack<Node*> stk_tmp;
    stack<Node*> stk_out;
    Node* cur = _root;
    while (cur || !stk_tmp.empty()) {
        if (cur) {
            stk_out.push(cur);
            stk_tmp.push(cur);
            cur = cur->right;
        }
        else {
            cur = stk_tmp.top()->left;
            stk_tmp.pop();
        }
    }
    
    while (!stk_out.empty()) {
        operation(stk_out.top()->elem);
        stk_out.pop();
    }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::_insert(Node *root, const T &value) {
    if (!root) {
        root = new Node(value);
        ++_size;
    }
    else if (value == root->elem)
        return root;
    else if (value < root->elem)
        root->left = _insert(root->left, value);
    else // value > root->elem
        root->right = _insert(root->right, value);
    
    return _balance(root);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::_remove(Node *root, const T &value) {
    if (!root)
        return nullptr;
    else if (value < root->elem)
        root->left = _remove(root->left, value);
    else if (value > root->elem)
        root->right = _remove(root->right, value);
    else if (!root->left) { // value == root->elem
        delete root;
        --_size;
        root = root->right;
    }
    else { // value == root->elem
        Node *cur = root->left;
        while (cur->right)
            cur = cur->right;
        root->elem = cur->elem;
        root->left = _remove(root->left, root->elem);
    }
    
    return _balance(root);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::_balance(Node *root) {
    if (!root)
        return nullptr;
    
    root->height = _height(root);
    
    int diff = _heightDiff(root);
    if (diff > 1) {
        if (_heightDiff(root->left) < 0)
            root->left = _rotateLeft(root->left);
        root = _rotateRight(root);
    }
    else if (diff < -1) {
        if (_heightDiff(root->right) > 0)
            root->right = _rotateRight(root->right);
        root = _rotateLeft(root);
    }
    
    return root;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::_rotateLeft(Node *root) {
    if (!root || !root->right)
        return root;
    
    Node* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    
    root->height = _height(root);
    newRoot->height = _height(newRoot);
    
    return newRoot;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::_rotateRight(Node *root) {
    if (!root || !root->left)
        return root;
    
    Node* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    
    root->height = _height(root);
    newRoot->height = _height(newRoot);
    
    return newRoot;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
int AVLTree<T>::_height(Node *root) const {
    if (!root)
        return 0;
    int leftHeight = root->left ? root->left->height : 0;
    int rightHeight = root->right ? root->right->height : 0;
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
int AVLTree<T>::_heightDiff(Node *root) const {
    if (!root)
        return 0;
    int leftHeight = root->left ? root->left->height : 0;
    int rightHeight = root->right ? root->right->height : 0;
    return leftHeight - rightHeight;
}

#endif /* defined(__Code__AVLTree__) */
