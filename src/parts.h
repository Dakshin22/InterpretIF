#pragma once


#include <vector>
#include "storytokenizer.h"
#include "passagetokenizer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <unordered_map>
using namespace std;

class Parts
{
protected:
    static unordered_map<string, bool> vars;
    static bool match, alreadyMatched;
    bool temp;
    string temp1;
    

public:
    virtual void extract(PartToken)  = 0;
    virtual bool getValue() {return temp;}
    virtual string getVariable() {return temp1;}
    Parts(PartToken);
    Parts();
    //returns vars--the unordered map for the variables in the story
    unordered_map<string, bool> getVars() {return vars;}
   
    
};

class IfPart : public Parts
{
private:
    string variable;
    bool value;

public:
    IfPart(PartToken);
    virtual string getVariable() override {return variable;}
    virtual bool getValue() override {return value;}
    virtual void extract(PartToken) override;
};

class ElsePart : public Parts
{
private:
    string elseText;

public:
    ElsePart(PartToken);
    virtual void extract(PartToken) override;
};

class ElseIfPart : public Parts
{
private:
    string variable;
    bool value;

public:
    ElseIfPart(PartToken);
    virtual string getVariable() override {return variable;}
    virtual bool getValue() override {return value;}
    virtual void extract(PartToken) override;
};



class GoToPart : public Parts
{
private:
    string target;

public:
    GoToPart(PartToken);
    string getTarget() const;
    virtual void extract(PartToken)  override;
};

class SetPart : public Parts
{
private:
    string variable;
    bool value;

public:
    SetPart(PartToken);
    virtual void extract(PartToken)  override;
};

class TextPart : public Parts
{
private:
    string body;

public:
    TextPart(PartToken);
    
    virtual void extract(PartToken) override;
};

class LinkPart : public Parts
{
private:
    string display;
    string target;
    

public:
    LinkPart(PartToken);
    string getDisplay() const;
    string getTarget() const;
    
    
    virtual void extract(PartToken) override;
};

class BlockPart : public Parts
{
private:
    string BlockText;
    
  

public:
    BlockPart(PartToken);
    //empty virtual function
    void extract(PartToken){}
    //block version of extract
    void extractb(PartToken,vector<LinkPart>&,bool&,string&);
   
};
