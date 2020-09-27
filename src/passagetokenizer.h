#pragma once
#include "storytokenizer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
using namespace std;
//this program tokenizes html by extracting componenets from passages of a story, Dakshin Rathan
enum TYPE
{
    LINK,
    GOTO,
    SET,
    IF,
    ELSEIF,
    ELSE,
    BLOCK,
    TEXT
};


class PartToken
{
private:
    TYPE type;
    string partText;

public:
    string getText();
    TYPE getType();
    PartToken();
    PartToken(TYPE, string);
};

class PassageTokenizer
{
private:
    TYPE type;
    string text;
    int passNum;
    int position;
    string partText;
    string check;
    bool isBlock;

public:
    PartToken nextPart();
    bool hasNextPart();
    PassageTokenizer();
    PassageTokenizer(string);
    bool setBlockTrue();
    void getIsBlock();

};
