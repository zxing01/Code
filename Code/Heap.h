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
        Heap(bool (*compare)(const T&, const T&));
        Heap(vector<T> elems, bool (*compare)(const T&, const T&));
        int size();
        T top();
        T pop();
        void add(const T &elem);
        void add(const vector<T> &elems);
    private:
        vector<T> _heap;
        bool (*_comparator)(const T&, const T&);
        void _heapify();
        void _shiftDown(int idx);
        void _shiftUp(int idx);
    };
}

#endif /* defined(__Code__Heap__) */
