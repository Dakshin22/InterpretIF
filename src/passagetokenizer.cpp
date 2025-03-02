#include "storytokenizer.h"
#include "passagetokenizer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
using namespace std;
//this program tokenizes html by extracting componenets from passages of a story, Dakshin Rathan
PartToken PassageTokenizer::nextPart()
{


    //BLOCK
    if (isBlock)
    {

        position = text.find(")", position) + 1;
        int i = position;
        int count = 1;
        while (count != 0)
        {
            i++;
            if (text[i] == '[') 
            {
                count++;
            }
            if ((text[i] == ']'))
            {
                count--;
            }
        }
        partText = text.substr(position, 1 + i - position);
        type = BLOCK;
        position = i + 1;

        PartToken paTB(type, partText);
        isBlock = false;
        return paTB;
    }

    //GOTO
    if (text.find("(go-to: ", position) == position)
    {
        position = text.find("(go-to: ", position);
        partText = text.substr(position, (text.find(")", position) - position) + 1);
        type = GOTO;
        position = text.find(")", position) + 1;

        PartToken paTG(type, partText);
        return paTG;
    }

    //LINK
    else if (text.find("[[", position) == position)
    {

        position = text.find("[[", position);
        partText = text.substr(position, (text.find("]]", position) - position) + 2);
        type = LINK;
        position = text.find("]]", position) + 2;
        PartToken paTL(type, partText);
        return paTL;
    }

    //SET
    else if (text.find("(set: ", position) == position)
    {
        position = text.find("(set: ", position);
        partText = text.substr(position, (text.find(")", position) - position) + 1);
        type = SET;
        position = text.find(")", position) + 1;
        PartToken paTS(type, partText);

        return paTS;
    }

    //IF
    else if (text.find("(if: ", position) == position)
    {

        position = text.find("(if: ", position);
        partText = text.substr(position, (text.find(")", position) - position) + 1);
        type = IF;
        position = text.find(")", position);
        PartToken paTI(type, partText);
        isBlock = true;
        return paTI;
    }

    //ELSE IF
    else if (text.find("(else-if: ", position) == position)
    {
        position = text.find("(else-if: ", position);
        //  cout << "character after end of else-if: " << text[text.find(")", position) + 1] << '\n';

        partText = text.substr(position, (text.find(")", position) - position) + 1);
        type = ELSEIF;
        position = text.find(")", position);
        PartToken paTEI(type, partText);
        isBlock = true;
        return paTEI;
    }

    //ELSE
    else if (text.find("(else:)[", position) == position)
    {
        position = text.find("(else:", position);
        partText = text.substr(position, (text.find(")", position) - position) + 1);
        type = ELSE;
        position = text.find(")", position);
        PartToken paTE(type, partText);
        isBlock = true;
        return paTE;
    }

    //BLOCK
    else if (text.find(")[", position) == position)
    {

        //block
        position = text.find(")", position) + 1;
        int i = position;
        int count = 1;
        while (count != 0)
        {
            i++;
            if (text[i] == '[') 
            {
                count++;
            }
            if ((text[i] == ']'))
            {
                count--;
            }
        }
        partText = text.substr(position, 1 + i - position);
        type = BLOCK;
        position = i + 1;

        PartToken paTB(type, partText);
        return paTB;
    }
    //TEXT
    else
    {

        unsigned positionl = position;
        unsigned positiong = position;
        unsigned positioni = position;
        unsigned positionei = position;
        unsigned positione = position;
        unsigned positions = position;

        positionl = text.find("[[", position);
        positiong = text.find("(go-to: ", position);
        positioni = text.find("(if: ", position);
        positionei = text.find("(else-if: ", positione);
        positions = text.find("(set: ", position);
        positione = text.find("(else:)", position);

        int mini;


        mini = positionl;
        if (positiong < mini && positiong != -1)
        {
            mini = positiong;
        }
        if (positioni < mini && positioni != -1)
        {
            mini = positioni;
        }
        if (positionei < mini && positionei != -1)
        {
            mini = positionei;
        }
        if (positione < mini && positione != -1)
        {
            mini = positione;
        }
        if (positions < mini && positions != -1)
        {
            mini = positions;
        }

        partText = text.substr(position, mini - position);
        position = mini;
        type = TEXT;
        PartToken paTT(type, partText);
        return paTT;
    }

    return PartToken(TEXT, "");
}

bool PassageTokenizer::hasNextPart()
{
    if (text.length() > position)
    {
        return true;
    }


    return false;
}

TYPE PartToken::getType()
{
    return type;
}

string PartToken::getText()
{
    return partText;
}

PassageTokenizer::PassageTokenizer(string txt)
{
    text = txt;
    position = 0;
    type = TEXT;
    partText = "";
    isBlock = false;
}

PartToken::PartToken(TYPE typ, string pText)
{
    type = typ;
    partText = pText;
}
