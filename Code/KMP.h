//
//  KMP.h
//  Code
//
//  Created by Zhi Xing on 8/20/14.
//  Copyright (c) 2014 Zhi Xing. All rights reserved.
//

#ifndef __Code__KMP__
#define __Code__KMP__

#include <string>
#include <vector>

using namespace std;

namespace Code {
    class KMP {
    public:
        KMP(const string &pattern);
        void changePattern(const string &pattern);
        vector<int> search(const string &text) const;
    private:
        string _patt;
        vector<int> _dfa; // Deterministic Finite Automaton
        void _buildDFA();
    };
}

#endif /* defined(__Code__KMP__) */
