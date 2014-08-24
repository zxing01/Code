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

void print(int n)
{
    cout << n << " ";
}

int main(int argc, char *argv[])
{
    AVLTree<int> avl;
    
    cout << " Adding value 0 to 14...\n";
    for (int i = 8; i >= 0; --i)
        avl.insert(i);
    for (int i = 9; i < 15; ++i)
        avl.insert(i);
    cout << " Size = " << avl.size() << endl;
    
    cout << " Inorder traversal: ";
    avl.inorderTraversal(print);
    cout << endl;
    
    cout << " Preorder traversal: ";
    avl.preorderTraversal(print);
    cout << endl;
    
    cout << " Postorder traversal: ";
    avl.postorderTraversal(print);
    cout << endl;
    
    cout << " Removing value 0 to 8...\n";
    for (int i = 0; i < 4; ++i)
        avl.remove(i);
    for (int i = 8; i >= 4; --i)
        avl.remove(i);
    cout << " Size = " << avl.size() << endl;
    
    cout << " Inorder traversal: ";
    avl.inorderTraversal(print);
    cout << endl;
    
    cout << " Preorder traversal: ";
    avl.preorderTraversal(print);
    cout << endl;
    
    cout << " Postorder traversal: ";
    avl.postorderTraversal(print);
    cout << endl;
}

#endif
