//
//  Heap.cpp
//  Code
//
//  Created by Zhi Xing on 8/20/14.
//  Copyright (c) 2014 Zhi Xing. All rights reserved.
//

#include "Heap.h"

using namespace std;
using namespace Code;

///////////////////////////////////////////////////////////////////////////////
template <typename T>
Heap<T>::Heap(bool (*compare)(const T&, const T&)) : _comparator(compare) {}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
Heap<T>::Heap(vector<T> elems, bool (*compare)(const T&, const T&)) : _heap(elems), _comparator(compare)
{
    _heapify();
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
int Heap<T>::size()
{
    return static_cast<int>(_heap.size());
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
T Heap<T>::top()
{
    return _heap[0];
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
T Heap<T>::pop()
{
    T ret = _heap[0];
    _heap[0] = _heap.back();
    _heap.pop_back();
    _shiftDown(0);
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void Heap<T>::add(const T &elem)
{
    _heap.push_back(elem);
    _shiftUp(static_cast<int>(_heap.size()) - 1);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void Heap<T>::add(const vector<T> &elems)
{
    _heap.reserve(_heap.size() + elems.size());
    for (auto e : elems)
        add(e);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void Heap<T>::_heapify()
{
    for (int i = 0; i < _heap.size(); ++i)
        _shiftUp(i);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void Heap<T>::_shiftDown(int idx)
{
    int sz = static_cast<int>(_heap.size());
    if (idx < 0 || idx >= sz)
        return;
    
    while (true) {
        int left = 2 * idx + 1, right = 2 * idx + 2, higher;
        if (left >= sz)
            break;
        else if (right >= sz)
            higher = left;
        else
            higher = _comparator(_heap[left], _heap[right]) ? left : right;
        
        if (_comparator(_heap[higher], _heap[idx])) {
            T temp = _heap[idx];
            _heap[idx] = _heap[higher];
            _heap[higher] = temp;
            idx = higher;
        }
        else
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void Heap<T>::_shiftUp(int idx)
{
    if (idx < 0 || idx >= _heap.size())
        return;
    
    while (true) {
        int parent = (idx - 1) / 2;
        if (parent < 0)
            break;
        
        if (_comparator(_heap[idx], _heap[parent])) {
            T temp = _heap[idx];
            _heap[idx] = _heap[parent];
            _heap[parent] = temp;
            idx = parent;
        }
        else
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
#ifdef __TEST__Code__Heap__
#include <iostream>

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
    vector<int> nums {9, 1, 5, 3, 7};
    vector<int> ext {6, 4, 8, 0, 2};
    cout << " original heap elements = [ ";
    for (auto n : nums)
        cout << n << " ";
    cout << "]\n";
    
    cout << " additional heap elements = [ ";
    for (auto n : ext)
        cout << n << " ";
    cout << "]\n";
    
    Heap<int> maxHeap(nums, larger);
    maxHeap.add(ext);
    cout << " poping elements from max heap: ";
    while (maxHeap.size())
        cout << maxHeap.pop() << " ";
    cout << endl;
    
    Heap<int> minHeap(nums, smaller);
    minHeap.add(ext);
    cout << " poping elements from min heap: ";
    while (minHeap.size())
        cout << minHeap.pop() << " ";
    cout << endl;
}

#endif