//
//  Trie.cpp
//  Code
//
//  Created by Zhi Xing on 8/29/14.
//  Copyright (c) 2014 Zhi Xing. All rights reserved.
//

#include "Trie.h"

using namespace std;
using namespace Code;

///////////////////////////////////////////////////////////////////////////////
Trie::Trie(const Trie &other): _root(_copy(other._root)) {}

///////////////////////////////////////////////////////////////////////////////
Trie::Trie(Trie &&other): _root(other._root) {
    other._root = nullptr;
}

///////////////////////////////////////////////////////////////////////////////
Trie::~Trie() {
    _clean(_root);
    _root = nullptr;
}

///////////////////////////////////////////////////////////////////////////////
Trie &Trie::operator=(const Trie &other) {
    _clean(_root);
    _root = _copy(other._root);
    return *this;
}

///////////////////////////////////////////////////////////////////////////////
Trie &Trie::operator=(Trie &&other) {
    _clean(_root);
    _root = other._root;
    other._root = nullptr;
    return *this;
}

///////////////////////////////////////////////////////////////////////////////
void Trie::insert(const string &word) {
    if (!_root)
        _root = new Node();
    Node *cur = _root;
    for (int i = 0; i < word.length(); ++i) {
        int index = CHAR_INDEX(word[i]);
        if (index < 0 || index >= ALPHABET_SIZE)
            return;
        if (!cur->children[index])
            cur->children[index] = new Node();
        cur = cur->children[index];
    }
    cur->value = 1;
}

///////////////////////////////////////////////////////////////////////////////
void Trie::remove(const string &word) {
    if (!_root)
        return;
    _remove(word, 0, _root);
}

///////////////////////////////////////////////////////////////////////////////
bool Trie::lookup(const string &word) {
    if (!_root)
        return false;
    Node *cur = _root;
    for (int i = 0; i < word.length(); ++i) {
        int index = CHAR_INDEX(word[i]);
        if (index < 0 || index >= ALPHABET_SIZE)
            return false;
        if (!cur->children[index])
            return false;
        cur = cur->children[index];
    }
    return cur->value == 1;
}

///////////////////////////////////////////////////////////////////////////////
Trie::Node *Trie::_copy(Node *root) {
    if (!root)
        return nullptr;
    Node *newRoot = new Node(root->value);
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        if (root->children[i])
            newRoot->children[i] = _copy(root->children[i]);
    return newRoot;
}

///////////////////////////////////////////////////////////////////////////////
void Trie::_clean(Node *root) {
    if (!root)
        return;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        if (root->children[i])
            _clean(root->children[i]);
    delete root;
}

///////////////////////////////////////////////////////////////////////////////
bool Trie::_remove(const string &word, int index, Node *root) {
    if (!root)
        return false;
    
    if (index == word.length()) {
        root->value = 0;
        return _isFree(root);
    }
    else {
        int cindex = CHAR_INDEX(word[index]);
        if (cindex >= 0 && cindex < ALPHABET_SIZE && root->children[cindex]) {
            if (_remove(word, index + 1, root->children[cindex])) {
                delete root->children[cindex];
                root->children[cindex] = nullptr;
                return _isFree(root);
            }
        }
    }
    
    return false;
}

///////////////////////////////////////////////////////////////////////////////
bool Trie::_isFree(Node *root) {
    if (!root)
        return false;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        if (root->children[i] != nullptr)
            return false;
    return true;
}

///////////////////////////////////////////////////////////////////////////////
#ifdef __TEST__Code__Trie__

#include <iostream>

int main(int argc, char *argv[]) {
    Trie t;
    
    cout << " Inserting words: ";
    vector<string> words {"This", "is", "a", "test"};
    for (auto w : words) {
        t.insert(w);
        cout << "'" << w << "' ";
    }
    cout << endl;
    cout << "   Find 'this'? " << (t.lookup("this") ? "Yes" : "No") << endl;
    cout << "   Find 'This'? " << (t.lookup("This") ? "Yes" : "No") << endl;
    cout << "   Find ''? " << (t.lookup("") ? "Yes" : "No") << endl;
    cout << "   Find 'tes'? " << (t.lookup("tes") ? "Yes" : "No") << endl;
    cout << "   Find 'tests'? " << (t.lookup("tests") ? "Yes" : "No") << endl;

    cout << " Testing copy constructor:\n";
    Trie copy(t);
    cout << "   Find 'test' in copy? " << (copy.lookup("test") ? "Yes" : "No") << endl;
    cout << "   Find 'test' in origin? " << (t.lookup("test") ? "Yes" : "No") << endl;
    
    cout << " Removing words: ";
    words = vector<string> {"a", "test", "case", "for", "Trie"};
    for (auto w : words) {
        t.remove(w);
        cout << "'" << w << "' ";
    }
    cout << endl;
    
    cout << " Testing copy assignment:\n";
    copy = t;
    cout << "   Find 'test' in copy? " << (copy.lookup("test") ? "Yes" : "No") << endl;
    cout << "   Find 'test' in origin? " << (t.lookup("test") ? "Yes" : "No") << endl;
    
    cout << " Testing move constructor:\n";
    Trie temp(move(copy));
    cout << "   Find 'this' in temp? " << (temp.lookup("this") ? "Yes" : "No") << endl;
    cout << "   Find 'this' in copy? " << (copy.lookup("this") ? "Yes" : "No") << endl;
    
    cout << " Testing move assignment:\n";
    copy = move(temp);
    cout << "   Find 'this' in temp? " << (temp.lookup("this") ? "Yes" : "No") << endl;
    cout << "   Find 'this' in copy? " << (copy.lookup("this") ? "Yes" : "No") << endl;
}

#endif