//
//  Trie.h
//  Code
//
//  Created by Zhi Xing on 8/29/14.
//  Copyright (c) 2014 Zhi Xing. All rights reserved.
//

#ifndef __Code__Trie__
#define __Code__Trie__

#define ALPHABET_SIZE 26
#define CHAR_INDEX(c) (c < 'a' ? (int)(c - 'A') : (int)(c - 'a'))

#include <string>
#include <vector>

using namespace std;

namespace Code {
    class Trie {
    public:
        Trie(): _root(nullptr) {}
        Trie(const Trie &other);
        Trie(Trie &&other);
        virtual ~Trie();
        Trie &operator=(const Trie &other);
        Trie &operator=(Trie &&other);
        virtual void insert(const string &word);
        virtual void remove(const string &word);
        virtual bool lookup(const string &word) const;
    private:
        struct Node {
            int value;
            vector<Node*> children;
            Node(int num = 0): value(num), children(ALPHABET_SIZE, nullptr) {}
        };
        
        Node *_root;
        Node *_copy(const Node *root);
        void _clean(Node *root);
        bool _remove(const string &word, int index, Node *root);
        bool _isFree(const Node *root) const;
    };
}
#endif /* defined(__Code__Trie__) */
