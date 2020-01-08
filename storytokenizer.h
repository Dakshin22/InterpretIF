#pragma once
#include <string>
using namespace std;
//this program tokenizes html by extracting passages from a story, Dakshin Rathan

class PassageToken
{
private:
string name;
string text;
int passnum;

public:
    string getName() const;
    string getText() const;

    PassageToken(int,string,string);
 
};

class StoryTokenizer
{
private:
    
    string name;
    string text;
    int passnum;
    int position;
    string passa;


public:

    bool hasNextPassage();
    PassageToken nextPassage();
    StoryTokenizer();
    StoryTokenizer(string);
 
};
