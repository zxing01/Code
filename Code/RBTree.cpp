//
//  RBTree.cpp
//  Code
//
//  Created by Zhi Xing on 8/24/14.
//  Copyright (c) 2014 Zhi Xing. All rights reserved.
//

#include "RBTree.h"

///////////////////////////////////////////////////////////////////////////////
#ifdef __TEST__Code__RBTree__

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
    RBTree<int> rb;
    
    cout << " Adding value 0 to 14...\n";
    for (int i = 8; i >= 0; --i)
        rb.insert(i);
    for (int i = 5; i < 15; ++i)
        rb.insert(i);
    cout << " Size = " << rb.size() << endl;
    
    cout << " Inorder traversal: ";
    rb.inorderTraversal(print);
    cout << endl;
    
    cout << " Preorder traversal: ";
    rb.preorderTraversal(print);
    cout << endl;
    
    cout << " Postorder traversal: ";
    rb.postorderTraversal(print);
    cout << endl;
    
    cout << " Removing value 0 to 8...\n";
    for (int i = 0; i < 4; ++i)
        rb.remove(i);
    for (int i = 8; i >= 0; --i)
        rb.remove(i);
    cout << " Size = " << rb.size() << endl;
    
    cout << " Inorder traversal: ";
    rb.inorderTraversal(print);
    cout << endl;
    
    cout << " Preorder traversal: ";
    rb.preorderTraversal(print);
    cout << endl;
    
    cout << " Postorder traversal: ";
    rb.postorderTraversal(print);
    cout << endl;
    
    cout << " Minusing one from all the elements...\n";
    rb.inorderTraversal(minusOne);
    cout << " Size = " << rb.size() << endl;
    
    cout << " Inorder traversal: ";
    rb.inorderTraversal(print);
    cout << endl;
    
    cout << " Preorder traversal: ";
    rb.preorderTraversal(print);
    cout << endl;
    
    cout << " Postorder traversal: ";
    rb.postorderTraversal(print);
    cout << endl;
}

#endif