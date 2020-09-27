#include <string>
#include <iostream>
#include "ifinterpreter.h"
using namespace std;

const string FILENAME = "input.txt"; //CHANGE THIS TO THE TXT/HTML FILE YOU NEED TO TOKENIZE

int main()
{
  IFInterpreter* interpreter = new IFInterpreter(FILENAME);
  interpreter->play();

  delete interpreter;
  return 0;
}
