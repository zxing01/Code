//
//  Heap.h
//  Code
//
//  Created by Zhi Xing on 8/20/14.
//  Copyright (c) 2014 Zhi Xing. All rights reserved.
//

#ifndef __Code__Heap__
#define __Code__Heap__

#include <vector>

using namespace std;

namespace Code {
    template <typename T>
    class Heap {
    public:
        Heap(bool (*)(const T&, const T&));
        template <typename Iterator>
        Heap(const Iterator begin, const Iterator end, bool (*)(const T&, const T&));
        int size() const;
        T top() const;
        T pop();
        void add(const T &elem);
        template <typename Iterator>
        void add(const Iterator begin, const Iterator end);
    private:
        vector<T> _heap;
        bool (*_comparator)(const T&, const T&);
        void _heapify();
        void _shiftDown(int idx);
        void _shiftUp(int idx);
    };
}

using namespace Code;

///////////////////////////////////////////////////////////////////////////////
template <typename T>
Heap<T>::Heap(bool (*compare)(const T&, const T&)) : _comparator(compare) {}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
template <typename Iterator>
Heap<T>::Heap(const Iterator begin, const Iterator end, bool (*compare)(const T&, const T&)) : _heap(begin, end), _comparator(compare) {
    _heapify();
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
int Heap<T>::size() const {
    return static_cast<int>(_heap.size());
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
T Heap<T>::top() const {
    return _heap[0];
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
T Heap<T>::pop() {
    T ret = _heap[0];
    _heap[0] = _heap.back();
    _heap.pop_back();
    _shiftDown(0);
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void Heap<T>::add(const T &elem) {
    _heap.push_back(elem);
    _shiftUp(static_cast<int>(_heap.size()) - 1);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
template <typename Iterator>
void Heap<T>::add(const Iterator begin, const Iterator end) {
    _heap.reserve(_heap.size() + distance(begin, end));
    for (auto it = begin; it != end; ++it)
        add(*it);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void Heap<T>::_heapify() {
    for (int i = 0; i < _heap.size(); ++i)
        _shiftUp(i);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void Heap<T>::_shiftDown(int idx) {
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
void Heap<T>::_shiftUp(int idx) {
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

#endif /* defined(__Code__Heap__) */
