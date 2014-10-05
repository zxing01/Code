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
Code::TreeNode *sortedListToBST(Code::ListNode *&head, int left, int right) {
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
Code::TreeNode *Code::sortedListToBST(ListNode *head) {
    ListNode *cur = head;
    int count = 0;
    while (cur) {
        ++count;
        cur = cur->next;
    }
    return ::sortedListToBST(head, 1, count);
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
    stringstream ss(str);
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
void nth34(int n) {
    int digit = 1;
    int count = 2;
    while (count < n) {
        ++digit;
        count += (1 << digit);
    }
    
    count -= (1 << digit);
    n -= count + 1;
    string res;
    for (int i = digit - 1; i >= 0; --i) {
        if (n & (int)1 << i)
            res += '4';
        else
            res += '3';
    }
    
    cout << res << endl;
}

///////////////////////////////////////////////////////////////////////////////
#ifdef __TEST__Code__Utilities__
using namespace Code;

int main(int argc, const char *argv[]) {
    // tests for maxInSubarrays
    vector<int> array {1, 2, 3, 4, 5, 4, 3, 2, 1};
    cout << " array = [ ";
    for (auto n : array)
        cout << n << " ";
    cout << "]\n";
    
    auto ret = maxInSubarrays(array, 1);
    cout << "  max of subarrays of size 1 = [ ";
    for (auto n : ret)
        cout << n << " ";
    cout << "]\n";
    
    ret = maxInSubarrays(array, 2);
    cout << "  max of subarrays of size 2 = [ ";
    for (auto n : ret)
        cout << n << " ";
    cout << "]\n";
    
    ret = maxInSubarrays(array, 3);
    cout << "  max of subarrays of size 3 = [ ";
    for (auto n : ret)
        cout << n << " ";
    cout << "]\n";
    
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
    cout << "  Split to [ ";
    for (auto s : vec)
        cout << "'" << s << "' ";
    cout << "]\n";
    
    // tests for isPalindrome
    bool result = isPalindrome(100021);
    cout << " isPalindrome(100021) = " << (result ? "true" : "false") << endl;
    
    for (int i = 0; i < 30; ++i)
        nth34(i+1);
}

#endif