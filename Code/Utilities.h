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
}

#endif /* defined(__Code__Utilities__) */
