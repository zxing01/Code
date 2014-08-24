//
//  Utilities.cpp
//  Code
//
//  Created by Zhi Xing on 8/20/14.
//  Copyright (c) 2014 Zhi Xing. All rights reserved.
//

#include "Utilities.h"
#include <list>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
vector<int> Code::maxInSubarrays(const vector<int> &array, int subarraySize)
{
    vector<int> max;
    list<int> deque;
    
    for (int i = 0; i < array.size(); ++i)
    {
        while (!deque.empty() && array[deque.back()] < array[i])
            deque.pop_back();
        deque.push_back(i);
        if (deque.front() <= i - subarraySize)
            deque.pop_front();
        if (i >= subarraySize - 1)
            max.push_back(array[deque.front()]);
    }
    
    return max;
}

///////////////////////////////////////////////////////////////////////////////
#ifdef __TEST__Code__Utilities__
#include <iostream>
using namespace Code;

int main(int argc, const char *argv[])
{
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
}

#endif