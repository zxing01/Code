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
        KMP(string pattern);
        void changePattern(string pattern);
        vector<int> search(string text);
    private:
        string _patt;
        vector<int> _nfa; // Nondeterministic Finite Automaton
        void _buildNFA();
    };
}

#endif /* defined(__Code__KMP__) */
