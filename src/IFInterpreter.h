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
    vector<PassageToken> passages; //Populates with all passages in the form of PassageToken objects upon instantiation
    vector<LinkPart> links; //Populates with all links in a passage in the form of LinkPart objects upon instatiation
    bool gt;
    string tgt;

public:
    void play(); //function to start the interaction with user
    IFInterpreter(string); 
    
};
