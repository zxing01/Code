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
KMP::KMP(const string &pattern) : _patt(pattern)
{
    _buildNFA();
}

///////////////////////////////////////////////////////////////////////////////
vector<int> KMP::search(const string &text)
{
    vector<int> indices;
    int plen = static_cast<int>(_patt.length());
    int tlen = static_cast<int>(text.length());
    int i = 0, j = 0;
    
    while (i < tlen && j < plen) {
        if (text[i] == _patt[j]) {
            ++i, ++j;
            if (j == plen) {
                indices.push_back(i - plen);
                j = _nfa[j-1];
            }
        }
        else if (j > 0)
            j = _nfa[j];
        else
            ++i;
    }
    return indices;
}

///////////////////////////////////////////////////////////////////////////////
void KMP::changePattern(const string &pattern)
{
    _patt = pattern;
    _buildNFA();
}

///////////////////////////////////////////////////////////////////////////////
void KMP::_buildNFA()
{
    int len = static_cast<int>(_patt.length());
    _nfa = vector<int>(len);
    int match = 0, pos = 0;
    
    while (pos < len) {
        if (pos < 2)
            _nfa[pos++] = 0;
        else if (_patt[pos-1] == _patt[match])
            _nfa[pos++] = ++match;
        else if (match > 0)
            match = _nfa[match];
        else
            _nfa[pos++] = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
#ifdef __TEST__Code__KMP__
#include <iostream>

int main(int argc, const char *argv[])
{
    string text = "AAAAABCAAAAABCAAAAA";
    cout << " text = '" << text << "'\n";
    
    string pattern = "AAABCAAA";
    cout << " pattern = '" << pattern << "'\n";
    KMP kmp(pattern);
    auto ret = kmp.search(text);
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
    
    pattern = "A";
    cout << " pattern = '" << pattern << "'\n";
    kmp.changePattern(pattern);
    ret = kmp.search(text);
    cout << "   result = [ ";
    for (auto v : ret)
        cout << v << " ";
    cout << "]\n";
    
    pattern = "AB";
    cout << " pattern = '" << pattern << "'\n";
    kmp.changePattern(pattern);
    ret = kmp.search(text);
    cout << "   result = [ ";
    for (auto v : ret)
        cout << v << " ";
    cout << "]\n";
}

#endif