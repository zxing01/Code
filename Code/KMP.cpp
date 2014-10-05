//
//  KMP.cpp
//  Code
//
//  Created by Zhi Xing on 8/20/14.
//  Copyright (c) 2014 Zhi Xing. All rights reserved.
//

#include "KMP.h"

using namespace std;
using namespace Code;

///////////////////////////////////////////////////////////////////////////////
KMP::KMP(const string &pattern) : _patt(pattern) {
    _buildDFA();
}

///////////////////////////////////////////////////////////////////////////////
vector<int> KMP::search(const string &text) const {
    vector<int> indices;
    int plen = (int)_patt.length();
    int tlen = (int)text.length();
    int i = 0, j = 0;
    
    while (i < tlen && j < plen) {
        if (text[i] == _patt[j]) {
            if (j == plen - 1) {
                indices.push_back(i - j);
                j = _dfa[j];
            }
            else
                ++i, ++j;
        }
        else if (j > 0)
            j = _dfa[j];
        else
            ++i;
    }
    return indices;
}

///////////////////////////////////////////////////////////////////////////////
void KMP::changePattern(const string &pattern) {
    _patt = pattern;
    _buildDFA();
}

///////////////////////////////////////////////////////////////////////////////
void KMP::_buildDFA() {
    int len = (int)_patt.length();
    _dfa = vector<int>(len);
    int match = 0, pos = 0;
    
    while (pos < len) {
        if (pos < 2)
            _dfa[pos++] = 0;
        else if (_patt[pos-1] == _patt[match])
            _dfa[pos++] = ++match;
        else if (match > 0)
            match = _dfa[match];
        else
            _dfa[pos++] = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
#ifdef __TEST__Code__KMP__
#include <iostream>

int main(int argc, const char *argv[]) {
    string text = "ABCABCABC";
    cout << " text = '" << text << "'\n";
    
    string pattern = "ABCABC";
    cout << " pattern = '" << pattern << "'\n";
    KMP kmp(pattern);
    auto ret = kmp.search(text);
    cout << "   result = [ ";
    for (auto v : ret)
        cout << v << " ";
    cout << "]\n";
    
    pattern = "ABC";
    cout << " pattern = '" << pattern << "'\n";
    kmp.changePattern(pattern);
    ret = kmp.search(text);
    cout << "   result = [ ";
    for (auto v : ret)
        cout << v << " ";
    cout << "]\n";
    
    pattern = "";
    cout << " pattern = '" << pattern << "'\n";
    kmp.changePattern(pattern);
    ret = kmp.search(text);
    cout << "   result = [ ";
    for (auto v : ret)
        cout << v << " ";
    cout << "]\n";
}

#endif