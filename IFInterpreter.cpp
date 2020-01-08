#include <vector>
#include "storytokenizer.h"
#include "passagetokenizer.h"
#include "IFInterpreter.h"
#include "parts.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <unordered_map>

using namespace std;

//replace hasnolinks with links.size
//make stati data member to let if/else if/else ocmmunicate wiht eachother
//amke it so if without else works.

IFInterpreter::IFInterpreter(string file)
{
  ifstream in(file);
  if (!in.is_open())
  {
    cout << "Couldn't open " << file << " for reading!\n";
    return;
  }

  getline(in, line);
  while (in && line != "</html>")
  {
    story += line + '\n';
    getline(in, line);
  }
  PassageNum = 0;
  StoryTokenizer stc(story);
  while (stc.hasNextPassage())
  {
    //Use the PassageToken to construct a PassageTokenizer
    PassageToken ptok = stc.nextPassage();
    passages.push_back(ptok); //populates passageToken vector
  }
  links = {};
  //  ifs = {};
  gt = false;
  tgt = "";
}

void IFInterpreter::play()
{
  //variable to determine if a block is being processed
  gt = false;
  int input, linkCount = 0;

  //Construct the StoryTokenizer object
  StoryTokenizer st(story);

  PassageToken p = passages[0];
  //Iterate through all of the passages in the story
  do
  {
    //Use the PassageToken to construct a PassageTokenizer
    links.clear();

    bool bl = false;
    gt = false;

    if (!bl)
    {
      cout << "\n\nPassage"
           << " " << p.getName() << ":  " << endl;
    }
    bl = false;
    PassageTokenizer pt(p.getText());

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
        //cout << "  Link:  ";

        l.extract(stok);
        links.push_back(l);
        break;
      case SET:
        //cout << "  Set:  ";

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

        bp.extractb(stok, links, gt, tgt);

        break;
      case TEXT:

        t.extract(stok);
        break;
      default:
        cout << "  Unknown token:  ";
      }
    }

    if (gt == true)
    {

      for (int i = 0; i < passages.size(); i++)
      {
        if (tgt == passages[i].getName())
        {

          p = passages[i];
        }
      }
    }

    else
    {
      if (links.size() > 0)
      {
        for (int i = 0; i < links.size(); i++)
        {
          cout << '\n'
               << i + 1 << ". " << links[i].getDisplay() << endl;
        }

        if (cin >> input)
        {
          
          for (int i = 0; i < passages.size(); i++)
          {
            
            if (links[input - 1].getTarget() == passages[i].getName())
            {

              
              p = passages[i];
            }
          }
        }
      }
    }
    
  } while (links.size() > 0 || gt);
}

