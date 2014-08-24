//
//  Heap.cpp
//  Code
//
//  Created by Zhi Xing on 8/20/14.
//  Copyright (c) 2014 Zhi Xing. All rights reserved.
//

#include "Heap.h"

///////////////////////////////////////////////////////////////////////////////
#ifdef __TEST__Code__Heap__
#include <iostream>
#include <list>
#include <set>

using namespace std;
using namespace Code;

bool larger(const int &n1, const int &n2)
{
    return n1 > n2;
}

bool smaller(const int &n1, const int &n2)
{
    return n1 < n2;
}

int main(int argc, const char *argv[])
{
    list<int> nums {9, 1, 5, 3, 7};
    set<int> ext {6, 4, 8, 0, 2};
    cout << " original heap elements = [ ";
    for (auto n : nums)
        cout << n << " ";
    cout << "]\n";
    
    cout << " additional heap elements = [ ";
    for (auto n : ext)
        cout << n << " ";
    cout << "]\n";
    
    Heap<int> maxHeap(nums.begin(), nums.end(), larger);
    maxHeap.add(ext.begin(), ext.end());
    cout << " poping elements from max heap: ";
    while (maxHeap.size())
        cout << maxHeap.pop() << " ";
    cout << endl;
    
    Heap<int> minHeap(nums.begin(), nums.end(), smaller);
    minHeap.add(ext.begin(), ext.end());
    cout << " poping elements from min heap: ";
    while (minHeap.size())
        cout << minHeap.pop() << " ";
    cout << endl;
}

#endif