//
//  AVLTree.cpp
//  Code
//
//  Created by Zhi Xing on 8/21/14.
//  Copyright (c) 2014 Zhi Xing. All rights reserved.
//

#include "AVLTree.h"

///////////////////////////////////////////////////////////////////////////////
#ifdef __TEST__Code__AVLTree__

#include <iostream>

using namespace std;
using namespace Code;

void print(int &n) {
    cout << n << " ";
}

void minusOne(int &n) {
    --n;
}

int main(int argc, char *argv[]) {
    AVLTree<int> avl;
    
    cout << " Adding value 0 to 14...\n";
    for (int i = 8; i >= 0; --i)
        avl.insert(i);
    for (int i = 5; i < 15; ++i)
        avl.insert(i);
    cout << "   Size = " << avl.size() << endl;
    cout << "   Inorder traversal: ";
    avl.inorderTraversal(print);
    cout << endl;
    cout << "   Preorder traversal: ";
    avl.preorderTraversal(print);
    cout << endl;
    cout << "   Postorder traversal: ";
    avl.postorderTraversal(print);
    cout << endl;
    
    cout << " Removing value 0 to 8...\n";
    for (int i = 0; i < 4; ++i)
        avl.remove(i);
    for (int i = 8; i >= 0; --i)
        avl.remove(i);
    cout << "   Size = " << avl.size() << endl;
    cout << "   Inorder traversal: ";
    avl.inorderTraversal(print);
    cout << endl;
    cout << "   Preorder traversal: ";
    avl.preorderTraversal(print);
    cout << endl;
    cout << "   Postorder traversal: ";
    avl.postorderTraversal(print);
    cout << endl;
    
    cout << " Testing copy constructor...\n";
    AVLTree<int> copy(avl);
    cout << "   Size of copy = " << copy.size() << endl;
    cout << "   Size of origin = " << avl.size() << endl;
    cout << "   Inorder traversal of copy: ";
    copy.inorderTraversal(print);
    cout << endl;
    cout << "   Inorder traversal of origin: ";
    avl.inorderTraversal(print);
    cout << endl;
    
    cout << " Minusing one from all the elements...\n";
    avl.inorderTraversal(minusOne);
    cout << "   Size = " << avl.size() << endl;
    cout << "   Inorder traversal: ";
    avl.inorderTraversal(print);
    cout << endl;
    
    cout << " Testing copy assignment...\n";
    copy = avl;
    cout << "   Size of copy = " << copy.size() << endl;
    cout << "   Size of origin = " << avl.size() << endl;
    cout << "   Inorder traversal of copy: ";
    copy.inorderTraversal(print);
    cout << endl;
    cout << "   Inorder traversal of origin: ";
    avl.inorderTraversal(print);
    cout << endl;
    
    cout << " Testing move constructor...\n";
    AVLTree<int> temp(move(copy));
    cout << "   Size of temp = " << temp.size() << endl;
    cout << "   Size of copy = " << copy.size() << endl;
    cout << "   Inorder traversal of temp: ";
    temp.inorderTraversal(print);
    cout << endl;
    cout << "   Inorder traversal of copy: ";
    copy.inorderTraversal(print);
    cout << endl;
    
    cout << " Testing move assignment...\n";
    copy = move(temp);
    cout << "   Size of temp = " << temp.size() << endl;
    cout << "   Size of copy = " << copy.size() << endl;
    cout << "   Inorder traversal of temp: ";
    temp.inorderTraversal(print);
    cout << endl;
    cout << "   Inorder traversal of copy: ";
    copy.inorderTraversal(print);
    cout << endl;
    
    cout << " Destroying original tree...\n";
    avl.~AVLTree();
    cout << "   Size = " << avl.size() << endl;
    cout << "   Inorder traversal: ";
    avl.inorderTraversal(print);
    cout << endl;
}

#endif
