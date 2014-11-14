//
//  Utilities.cpp
//  Code
//
//  Created by Zhi Xing on 8/20/14.
//  Copyright (c) 2014 Zhi Xing. All rights reserved.
//

#include "Utilities.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <list>
#include <sstream>
#include <stack>
#include <queue>
#include <deque>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
vector<int> Code::maxInSubarrays(const vector<int> &array, int k) {
    vector<int> max;
    list<int> deque;
    
    for (int i = 0; i < array.size(); ++i) {
        while (!deque.empty() && array[deque.back()] < array[i])
            deque.pop_back();
        deque.push_back(i);
        if (deque.front() <= i - k)
            deque.pop_front();
        if (i >= k - 1)
            max.push_back(array[deque.front()]);
    }
    
    return max;
}

///////////////////////////////////////////////////////////////////////////////
double Code::pow(double x, int n) {
    if (x == 0)
        return 0;
    if (n == 0)
        return 1;
    
    int p = n < 0 ? -n : n;
    double y = pow(x, p/2);
    y = p % 2 == 1 ? y * y * x : y * y;
    return n < 0 ? 1 / y : y;
}

///////////////////////////////////////////////////////////////////////////////
Code::ListNode *Code::reverseBetween(ListNode *head, int m, int n) {
    if (!head)
        return nullptr;
    ListNode *cur = head, *next = head->next;
    ListNode *prev = nullptr, *start = nullptr, *end = nullptr;
    int counter = 1;
    while (counter <= n) {
        if (counter == m - 1)
            prev = cur;
        else if (counter == m)
            start = end = cur;
        else if (counter > m) {
            cur->next = start;
            start = cur;
        }
        cur = next;
        if (cur)
            next = cur->next;
        ++counter;
    }
    
    if (prev)
        prev->next = start;
    else
        head = start;
    end->next = cur;
    
    return head;
}

///////////////////////////////////////////////////////////////////////////////
int Code::largestRectangleArea(const vector<int> &height) {
    vector<int> stk;
    int ret = 0;
    
    for (int i = 0; i < height.size(); ++i) {
        while (!stk.empty() && height[stk.back()] > height[i]) {
            int h = height[stk.back()];
            stk.pop_back();
            int w = stk.empty() ? i : i - stk.back() - 1;
            ret = max(ret, h * w);
        }
        stk.push_back(i);
    }
    
    while (!stk.empty()) {
        int h = height[stk.back()];
        stk.pop_back();
        int w = stk.empty() ? (int)height.size() : (int)height.size() - stk.back() - 1;
        ret = max(ret, h * w);
    }
    
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
int Code::maxSum(int A[], int n) {
    int ret = A[0], sum = 0;
    for (int i = 0; i < n; ++i) {
        sum = max(sum + A[i], A[i]);
        ret= max(ret, sum);
    }
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
int Code::maxProduct(int A[], int n) {
    int ret = A[0], pmax = 1, nmax = 1;
    for (int i = 0; i < n; ++i) {
        if (A[i] < 0)
            swap(pmax, nmax);
        pmax = max(pmax * A[i], A[i]);
        nmax = min(nmax * A[i], A[i]);
        ret = max(ret, pmax);
    }
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
Code::TreeNode *Code::sortedListToBST(ListNode *head) {
    ListNode *cur = head;
    int count = 0;
    while (cur) {
        ++count;
        cur = cur->next;
    }
    return Helper::sortedListToBST(head, 1, count);
}

///////////////////////////////////////////////////////////////////////////////
Code::TreeNode *Code::Helper::sortedListToBST(Code::ListNode *&head, int left, int right) {
    using namespace Code;
    if (left > right)
        return nullptr;
    
    int mid = left + (right - left) / 2;
    TreeNode *leftChild = sortedListToBST(head, left, mid-1);
    TreeNode *root = new TreeNode(head->val);
    head = head->next;
    TreeNode *rightChild = sortedListToBST(head, mid+1, right);
    root->left =leftChild;
    root->right = rightChild;
    return root;
}

///////////////////////////////////////////////////////////////////////////////
string Code::simplifyPath(const string &path) {
    vector<string> dir;
    
    int i = 0;
    while (i < path.length()) {
        while (i < path.length() && path[i] == '/')
            ++i;
        if (i < path.length()) {
            int j = i + 1;
            while (j < path.length() && path[j] != '/')
                ++j;
            string tmp = path.substr(i, j-i);
            if (tmp != "." && tmp != "..")
                dir.push_back(tmp);
            else if (tmp == ".." && dir.size() > 0)
                dir.pop_back();
            i = j + 1;
        }
    }
    
    string ret;
    for (auto it = dir.begin(); it != dir.end(); ++it)
        ret += "/" + *it;
    return ret.length() ? ret : "/";
}

///////////////////////////////////////////////////////////////////////////////
vector<string> Code::split(const string &str, char delimit) {
    vector<string> ret;
    istringstream ss(str);
    string temp;
    while (getline(ss, temp, delimit))
        ret.push_back(temp);
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
bool Code::isPalindrome(int x) {
    if (x < 0)
        return false;
    int power = 1;
    while (x / power >= 10)
        power *= 10;
    while (power > 1) {
        if (x / power != x % 10)
            return false;
        x = x % power / 10;
        power /= 100;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////
int Code::nQueen(int n) {
    int count = 0;
    long goal = (1 << n) - 1;
    long row = 0, ldia = 0, rdia = 0;
    Helper::fit(count, goal, row, ldia, rdia);
    return count;
}

///////////////////////////////////////////////////////////////////////////////
void Code::Helper::fit(int &count, long &goal, long row, long ldia, long rdia) {
    if (row == goal)
        ++count;
    else {
        long avail = ~(row | ldia | rdia) & goal;
        while (avail) {
            long pick = avail & -avail; // -avail flips all bits of avail and plus 1
            avail -= pick;
            fit(count, goal, row + pick, (ldia + pick) >> 1, (rdia + pick) << 1);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
int Code::multiply(int a, int b) {
    bool neg = (a > 0) ^ (b > 0);
    a = abs(a), b = abs(b);
    int prod = 0;
    for (int i = 31; i >= 0; --i) {
        prod <<= 1;
        if ((b >> i) & 1)
            prod += a;
    }
    return neg ? -prod : prod;
}

///////////////////////////////////////////////////////////////////////////////
Code::TreeNode *Code::buildBST(const vector<int> &preorder) {
    TreeNode *root = nullptr;
    stack<TreeNode*> stk;
    for (int i = 0; i < preorder.size(); ++i) {
        TreeNode *node = new TreeNode(preorder[i]);
        if (!stk.empty() && preorder[i] < stk.top()->val) {
            stk.top()->left = node;
            stk.push(node);
        }
        else {
            TreeNode *cur = nullptr;
            while (!stk.empty() && preorder[i] >= stk.top()->val) {
                cur = stk.top();
                stk.pop();
            }
            if (cur)
                cur->right = node;
            else
                root = node;
            stk.push(node);
        }
    }
    return root;
}

///////////////////////////////////////////////////////////////////////////////
Code::TreeNode *Code::buildBinaryTree(const vector<int> &inorder, const vector<int> &preorder) {
    if (inorder.size() == 0 || inorder.size() != preorder.size())
        return nullptr;
    
    int pre_begin = 0;
    return Helper::buildBinaryTree(inorder, preorder, 0, (int)inorder.size() - 1, &pre_begin);
}

///////////////////////////////////////////////////////////////////////////////
Code::TreeNode *Code::Helper::buildBinaryTree(const vector<int> &inorder, const vector<int> &preorder,
                                              int in_begin, int in_end, int *pre_begin) {
    TreeNode *root = new TreeNode(preorder[*pre_begin]);
    int mid;
    for (mid = in_begin; mid <= in_end; ++mid)
        if (inorder[mid] == preorder[*pre_begin])
            break;
    ++*pre_begin;
    if (mid > in_begin)
        root->left = buildBinaryTree(inorder, preorder, in_begin, mid-1, pre_begin);
    if (mid < in_end)
        root->right = buildBinaryTree(inorder, preorder, mid+1, in_end, pre_begin);
    return root;
}

///////////////////////////////////////////////////////////////////////////////
vector<int> Code::preorder(TreeNode *root) {
    stack<TreeNode*> stk;
    vector<int> ret;
    TreeNode *cur = root;
    while (cur || !stk.empty()) {
        if (cur) {
            ret.push_back(cur->val);
            stk.push(cur);
            cur = cur->left;
        }
        else {
            cur = stk.top();
            stk.pop();
            cur = cur->right;
        }
    }
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
vector<int> Code::inorder(TreeNode *root) {
    stack<TreeNode*> stk;
    vector<int> ret;
    TreeNode *cur = root;
    while (cur || !stk.empty()) {
        if (cur) {
            stk.push(cur);
            cur = cur->left;
        }
        else {
            cur = stk.top();
            stk.pop();
            ret.push_back(cur->val);
            cur = cur->right;
        }
    }
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
vector<int> Code::postorder(TreeNode *root) {
    stack<TreeNode*> stk;
    deque<int> ret;
    TreeNode *cur = root;
    while (cur || !stk.empty()) {
        if (cur) {
            ret.push_front(cur->val);
            stk.push(cur);
            cur = cur->right;
        }
        else {
            cur = stk.top();
            stk.pop();
            cur = cur->left;
        }
    }
    return vector<int>(ret.begin(), ret.end());
}

///////////////////////////////////////////////////////////////////////////////
vector<int> Code::valuesBetweenLevels(TreeNode *root, int lower, int upper) {
    vector<int> ret;
    TreeNode *marker = new TreeNode(0);
    queue<TreeNode*> q;
    q.push(root);
    q.push(marker);
    int level = 0;
    while (!q.empty() && level <= upper) {
        TreeNode *cur = q.front();
        q.pop();
        if (cur == marker) {
            ++level;
            q.push(cur);
        }
        else {
            if (lower <= level)
                ret.push_back(cur->val);
            if (cur->left)
                q.push(cur->left);
            if (cur->right)
                q.push(cur->right);
        }
    }
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
#ifdef __TEST__Code__Utilities__
using namespace Code;

template <typename Container>
void print(Container c) {
    cout << "[ ";
    for (auto it = c.begin(); it != c.end(); ++it)
        cout << *it << " ";
    cout << "]";
}

int main(int argc, const char *argv[]) {
    // tests for maxInSubarrays
    vector<int> array {1, 2, 3, 4, 5, 4, 3, 2, 1};
    cout << " array: ";
    print(array);
    cout << endl;
    
    auto ret = maxInSubarrays(array, 1);
    cout << "  max of subarrays of size 1: ";
    print(ret);
    cout << endl;
    
    ret = maxInSubarrays(array, 2);
    cout << "  max of subarrays of size 2: ";
    print(ret);
    cout << endl;
    
    ret = maxInSubarrays(array, 3);
    cout << "  max of subarrays of size 3: ";
    print(ret);
    cout << endl;
    
    // tests for pow
    cout << " pow(0, 10) = " << pow(0, 10) << endl;
    cout << " pow(10, 1) = " << pow(10, 1) << endl;
    cout << " pow(2, 10) = " << pow(2, 5) << endl;
    cout << " pow(2, 10) = " << pow(10, -1) << endl;
    cout << " pow(2, 10) = " << pow(10, -4) << endl;
    
    // tests for split
    string path = "/Users/zxing/Movies/Modern Family//S05";
    cout << " Path = " << path << endl;
    auto vec = split(path, '/');
    cout << "  Split to: ";
    print(vec);
    cout << endl;
    
    // tests for isPalindrome
    bool result = isPalindrome(100021);
    cout << " isPalindrome(100021) = " << (result ? "true" : "false") << endl;
    
    // tests for multiply
    cout << " multiply(9, -15) = " << multiply(9, -15) << endl;
    cout << " multiply(-9, 20) = " << multiply(-9, 20) << endl;
    
    // tests for buildBinaryTree, preorder, inorder and postorder
    vector<int> in {1, 2, 3, 4, 5, 6, 7};
    vector<int> pre {4, 2, 1, 3, 6, 5, 7};
    cout << " Given inorder traversal: ";
    print(in);
    cout << " preorder traversal: ";
    print(pre);
    cout << endl;
    TreeNode *tree = buildBinaryTree(in, pre);
    auto traversal = inorder(tree);
    cout << "   Inorder traversal of constructed binary tree: ";
    print(traversal);
    cout << endl;
    traversal = preorder(tree);
    cout << "   Preorder traversal of constructed binary tree: ";
    print(traversal);
    cout << endl;
    traversal = postorder(tree);
    cout << "   Postorder traversal of constructed binary tree: ";
    print(traversal);
    cout << endl;
    
    // tests for buildBST
    cout << " Given preorder traversal: ";
    print(pre);
    cout << endl;
    tree = buildBST(pre);
    traversal = inorder(tree);
    cout << "   Inorder traversal of constructed BST: ";
    print(traversal);
    cout << endl;
    
    cout << " Given tree with preorder traversal: ";
    print(pre);
    cout << endl;
    vector<int> values = valuesBetweenLevels(tree, 1, 3);
    cout << "   Values between layers 1 and 3: ";
    print(values);
    cout << endl;
}

#endif