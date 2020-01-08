#pragma once

#include <vector>
#include "storytokenizer.h"
#include "passagetokenizer.h"
#include "parts.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
using namespace std;


class IFInterpreter
{
private:

    int PassageNum;
    string line;
    string story;
    string file;
    vector<PassageToken> passages;
    vector<LinkPart> links;
    bool gt;
    string tgt;
   // vector<Parts*> ifs;
   // unordered_map<LinkPart,PassageToken> con;
public:
    void print();
    void play();
    //void Process(BlockPart*);
    IFInterpreter(string);
    
};
