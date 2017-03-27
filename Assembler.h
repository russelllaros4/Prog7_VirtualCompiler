/*                                                                                                                                                       
Russell Laros
rkl218
cse109.154                                                                                                                                                                                                                                                                                           
Program 7: takes svm code and converts it to assembly hexidecimal code                                                                                                                                              
**/

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "Hashtable.h"
#include "Hash.h"
#include "Link.h"
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>



using namespace std;

class Assembler{
 public:
   HashTable* help;
   HashTable* labelMap;
   HashTable* argMap;
   HashTable* tempList;
   istream& is;
   int lineNum;
   int numLinesFilled;
   int numLabelsUsed;
   int numArgsUsed;
   int tempLinkCount;
   string programArray[255];
   
   Assembler(istream& in);
   ~Assembler();
   string toHex(int binary);
   string getLine();
   int countNumTokens(string line);
   void processLine(string line);
};

#endif
