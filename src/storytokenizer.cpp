#include "storytokenizer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include <sstream>
using namespace std;
//this program tokenizes html by extracting passages from a story, Dakshin Rathan
string PassageToken::getName() const
{
  return name;
}

string PassageToken::getText() const
{
  return text;
}


PassageToken StoryTokenizer::nextPassage()
{
  if (text.find("<tw-passagedata", position) != string::npos)
  {
    position = text.find("<tw-passagedata", position);

    string name = text.substr((text.find("name", position)) + 6, text.find("\" ", (text.find("name", position + 6))) - text.find("name", position) - 6);
    position += 16;

    string passa = text.substr((text.find(">", position)) + 1, (text.find("</tw-passagedata", (text.find(">", position))) - (text.find(">", position)) - 1));

    passnum += 1;
    PassageToken pt(passnum, name, passa);
    return pt;
  }

  PassageToken empty(0, "", "");
  return empty;
}

bool StoryTokenizer::hasNextPassage()
{

  if (text.find("<tw-passagedata", position) != string::npos)
  {
    return true;
  }
  return false;
}
PassageToken::PassageToken(int passagenum, string title, string body)
{
  passnum = passagenum;
  name = title;
  text = body;
}
StoryTokenizer::StoryTokenizer(string fullS)
{
  text = fullS;
  passnum = 0;
  position = 0;
  passa = "empty";
}
