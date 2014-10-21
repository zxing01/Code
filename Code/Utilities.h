//
//  Utilities.h
//  Code
//
//  Created by Zhi Xing on 8/20/14.
//  Copyright (c) 2014 Zhi Xing. All rights reserved.
//

#ifndef __Code__Utilities__
#define __Code__Utilities__

#include <vector>
#include <string>

using namespace std;

namespace Code {
    // linked list node
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x): val(x), next(nullptr) {}
    };
    // binary tree node
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    };
    
    // max ints in subarrys of size k in given array
    vector<int> maxInSubarrays(const vector<int> &array, int k);
    
    // calculate x^n
    double pow(double x, int n);
    
    // reverse linked list from position m to n
    ListNode *reverseBetween(ListNode *head, int m, int n);
    
    // largest rectangle in histogram
    int largestRectangleArea(const vector<int> &height);
    
    // max sum of subarrays (A[] has at least 1 element)
    int maxSum(int A[], int n);
    
    // max product of subarrays (A[] has at least 1 element)
    int maxProduct(int A[], int n);
    
    // turn sorted linked list to balanced BST
    TreeNode *sortedListToBST(ListNode *head);
    
    // simplify a Unix-style path
    string simplifyPath(const string &path);
    
    // split string using delimiter
    vector<string> split(const string &str, char delimit);
    
    // check if a number is palindrome (negative numbers are considered not)
    bool isPalindrome(int x);
    
    // count the number of solutions for n-queen problem
    int nQueen(int n);
    
    // multiply two integers without using * and with minimal number of additions
    int multiply(int a, int b);
    
    // build binary tree from inorder and preorder traversal
    TreeNode *buildBinaryTree(const vector<int> &inorder, const vector<int> &preorder);
    
    // iterative preorder binary tree traversal
    vector<int> preorder(TreeNode *root);
    
    // iterative inorder binary tree traversal
    vector<int> inorder(TreeNode *root);
    
    // iterateive postorder binary tree traversal
    vector<int> postorder(TreeNode *root);
    
    // helper functions
    namespace Helper {
        TreeNode *sortedListToBST(Code::ListNode *&head, int left, int right);
        void fit(int &count, long &goal, long row, long ldia, long rdia);
        TreeNode *buildBinaryTree(const vector<int> &inorder, const vector<int> &preorder, int in_begin, int in_end, int *pre_begin);
    }
}

#endif /* defined(__Code__Utilities__) */
