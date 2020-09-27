#include <vector>
#include "storytokenizer.h"
#include "passagetokenizer.h"
#include "parts.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <unordered_map>
using namespace std;

class PartToken;

//static variables
unordered_map<string, bool> Parts::vars;
bool Parts::match = false;
bool Parts::alreadyMatched = false;

//constructors
Parts::Parts()
{
    vars["first"] = true;
    temp = true;
    temp1 = "";
}

LinkPart::LinkPart(PartToken l)
{
    display = "";
    target = "";
}
IfPart::IfPart(PartToken p)
{
    variable = "";
    value = false;
}

ElsePart::ElsePart(PartToken e)
{
    elseText = "";
}

ElseIfPart::ElseIfPart(PartToken ei)
{
    variable = "";
    value = false;
}

BlockPart::BlockPart(PartToken b)
{
    BlockText = "";
}

GoToPart::GoToPart(PartToken got)
{
    target = "";
}

SetPart::SetPart(PartToken se)
{
    variable = "";
    value = false;
}

TextPart::TextPart(PartToken tx)
{
    body = "";
}

void LinkPart::extract(PartToken link)
{
    string contents = link.getText();
    if (contents.find("-&gt;", 0) != string::npos)
    {
        target = contents.substr(contents.find("-&gt;", 0) + 5, contents.length() - (contents.find("-&gt;", 0) + 5) - 2);
        display = contents.substr(2, (contents.find("-&gt;", 2)) - 2);
    }
    else
    {
        target = contents.substr(2, (contents.find("]]", 0) - 2));
        display = target;
    }

    //print out
    cout << "[[" << display << "]]";
}

string LinkPart::getDisplay() const
{
    return display;
}

string LinkPart::getTarget() const
{
    return target;
}

string GoToPart::getTarget() const
{
    return target;
}

void GoToPart::extract(PartToken g)
{
    string contents = g.getText();
    unsigned pos = contents.find(" &quot;", 0);
    unsigned newpos = pos + 7;
    target = contents.substr(newpos, contents.find("&quot;", newpos) - newpos);
}
void SetPart::extract(PartToken set)
{
    string contents = set.getText();
    unsigned pos = contents.find("$", 0);
    variable = contents.substr(pos, (contents.find(" to", 0) - contents.find("$", 0)));
    unsigned spos = contents.find(" to ", pos) + 4;
    string val = contents.substr(spos, contents.find(")", spos) - spos);

    if (val == "true")
    {
        vars[variable] = true;
        value = true;
    }
    else if (val == "false")
    {
        vars[variable] = false;
        value = false;
    }
    else
    {

        cout << "\nsomething wrong with string value in 'set': " << val << endl;
    }

}

void TextPart::extract(PartToken text)
{
    body = text.getText();

    cout << body;
}

void IfPart::extract(PartToken i)
{
    alreadyMatched = false;
    string contents = i.getText();
    unsigned pos = contents.find("$", 0);
    variable = contents.substr(pos, (contents.find(" is ", 0) - contents.find("$", 0)));
    unsigned spos = contents.find(" is ", pos) + 4;
    string val = contents.substr(spos, contents.find(")", spos) - spos);

    if (val == "true")
    {
        value = true;
    }
    else if (val == "false")
    {
        value = false;
    }
    else
    {
        cout << "\nsomething wrong with string value in 'if'" << endl;
    }

    //set match variable appropriately--has the variable met the condition in the 'if' token?
    if (vars[variable] == value)
    {
        match = true;
    }
    else if (vars[variable] != value)
    {
        match = false;
    }
}

void ElsePart::extract(PartToken el)
{

    elseText = el.getText();
    //if nothing has been matched, set match to true to accept else's block
    if (!match && !alreadyMatched)
    {

        match = true;
    }
}

void ElseIfPart::extract(PartToken elseif)
{
    string contents = elseif.getText();
    unsigned pos = contents.find("$", 0);
    variable = contents.substr(pos, (contents.find(" is ", 0) - contents.find("$", 0)));
    unsigned spos = contents.find(" is ", pos) + 4;
    string val = contents.substr(spos, contents.find(")", spos) - spos);

    if (val == "true")
    {
        value = true;
    }
    else if (val == "false")
    {
        value = false;
    }
    else
    {
        cout << "\nsomething wrong with string value in 'else-if'" << endl;
    }

    if (vars[variable] == value)
    {
        match = true;
    }
    else if (vars[variable] != value)
    {
        match = false;
    }
}
//reference to the links vector is passed in extractb() to be able to push links from the block onto the existing link vector.
//reference to gt and tgt are incuded to be able to change these variables in play()
void BlockPart::extractb(PartToken block, vector<LinkPart> &BLinks, bool &gt, string &tgt)
{

    if (match)
    {

        string str = block.getText();
        string b = str.substr(1, str.length() - 2);

        PassageTokenizer pt(b);

        while (pt.hasNextPart())
        {
            PartToken stok = pt.nextPart();

            LinkPart l(stok);
            SetPart s(stok);
            GoToPart gto(stok);
            IfPart iff(stok);
            ElseIfPart eli(stok);
            ElsePart els(stok);
            BlockPart bp(stok);
            TextPart t(stok);

            switch (stok.getType())
            {
            case LINK:

                l.extract(stok);
                BLinks.push_back(l);
                break;
            case SET:

                s.extract(stok);
                break;
            case GOTO:
                gt = true;
                gto.extract(stok);
                tgt = gto.getTarget();

                break;

            case IF:

                iff.extract(stok);

                break;
            case ELSEIF:

                eli.extract(stok);

                break;
            case ELSE:

                els.extract(stok);

                break;
            case BLOCK:

                bp.extractb(stok, BLinks, gt, tgt);

                break;
            case TEXT:

                t.extract(stok);
                break;
            default:
                cout << "  Unknown token:  ";
            }
        }

        alreadyMatched = true;
        match = false;
    }
}
