/*                                                                                                                                                       
Russell Laros
rkl218
cse109.154        
Program #7                                                                                                                                              
**/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include "Assembler.h"
#include "Hashtable.h"
#include "Hash.h"
#include "Link.h"

using namespace std;

Assembler::Assembler(istream& in): is(in), lineNum(0), numLinesFilled(1), numLabelsUsed(0), numArgsUsed(0), tempLinkCount(0){
  help = new HashTable(); 
  labelMap = new HashTable(255);
  argMap = new HashTable(255);
  tempList = new HashTable(255);
  programArray[0] = "CAFEBE";

}

Assembler::~Assembler(){}

string Assembler::toHex(int bi){
  string returnHexString = "";
  stringstream convert;
  convert << std::hex << bi;
  string hexString(convert.str());
  int hexLen = (int) hexString.length();
  if(hexLen < 2){
    returnHexString = "0" + hexString;
  }
  else{
    returnHexString = hexString;
  }
  return returnHexString;
}

string Assembler::getLine(){
  string line = "";  
  char ch = is.get();
  while(ch != '\n'){
    if(ch == '#'){
      while(ch !='\n'){
      ch = is.get();
      }
    }
    else if(is.eof()){
    ch ='\n';
    }
    else{
      string chString(1,ch);
      line = line + chString;
      ch = is.get();
    }
  }
  lineNum++;
  return line;
}

int Assembler::countNumTokens(string line){
    int numTokens = 0;
  int lineLen = (int) line.length();
  for(int i = 0; i < lineLen; i++){
    string lineSubstr = line.substr(i,1);
    if(lineSubstr == " "){
      numTokens++;
    }
  }
  numTokens++;
  return numTokens;
}

void Assembler::processLine(string line){
  int numTokens = countNumTokens(line);
  string tokenArray [numTokens];
  int lineLen = (int) line.length();
  string temp = "";
  int tokenCount = 0;
  while(tokenCount < numTokens){
    for(int i = 0; i < lineLen; i++){
      string lineSubstr = line.substr(i,1);
      if(lineSubstr != " "){
        temp = temp + lineSubstr;
      }
      else{
        tokenArray[tokenCount]= temp;
        tokenCount++;
	temp = "";
      }
      if((i == (lineLen - 1)) && (lineSubstr != " ")){
	tokenArray[tokenCount]= temp;
        tokenCount++;
        temp = "";
      }
    }
  }
  bool jumpFlag = false;
  bool printStringFlag = false;
  string lineString = "";
  string labelString = "00";
  string opString = "00";
  string argString = "00";

  for(int i = 0; i < numTokens; i++){
    int tokLen = (int) tokenArray[i].length();
    if(tokenArray[i].substr(tokLen - 1, 1) == ":"){
	if(labelMap->inTable(tokenArray[i])){
	  labelString = labelMap->getValue(tokenArray[i]);
	}
    
	else{
	  string compTokenString = tokenArray[i].substr(0, tokLen - 1);
	  string labNum = toHex(lineNum);
	  numLabelsUsed++;
	  labelMap->add(tokenArray[i], labNum);
	  labelString = labNum;
	  if(tempLinkCount > 0){
	       for(int p = 0; p < tempLinkCount; p++){
		   if(compTokenString == tempList->table[p]->key){
		     stringstream convert;
		     convert << (p+1);
		     string pString = convert.str();
		     string qString = "q" + pString;
		     for(int b = 0; b < numLinesFilled; b++){
		       if(programArray[b].substr(4,2) == qString){
			 string temp = (programArray[b].substr(0,4));
			 programArray[b] = temp + labelString; 
		       } 
		     }
		   }
	       }
	  }
	}
	   
    }
       else if(help->inTable(tokenArray[i])){
	if(tokenArray[i] == "LOADL" || tokenArray[i] == "LOADV" || tokenArray[i] == "STOREV" || tokenArray[i] == "JUMPF" || tokenArray[i] == "JUMP" || tokenArray[i] =="PRINTS"){
	  if((i + 1) < numTokens){
	    opString = help->getValue(tokenArray[i]);
	    if(tokenArray[i] == "JUMPF" || tokenArray[i] == "JUMP"){
	      jumpFlag = true;
	    }
	    if(tokenArray[i] =="PRINTS"){
	      printStringFlag = true;
	    }
	  }
	  else{
	    exit(1);
	  }
	}
	else if(tokenArray[i] == "DUP" || tokenArray[i] == "PRINT" || tokenArray[i] == "PRINTLN" || tokenArray[i] == "ADD" || tokenArray[i] == "SUB" || tokenArray[i] == "MULT" || tokenArray[i] == "DIV" || tokenArray[i] == "REM" || tokenArray[i] == "AND" || tokenArray[i] == "OR" || tokenArray[i] == "NOT" || tokenArray[i] == "ISEQ" || tokenArray[i] == "ISNE" || tokenArray[i] == "ISGT" || tokenArray[i] == "ISLT" || tokenArray[i] == "ISLE"){ 
	  opString = help->getValue(tokenArray[i]);
	}
      }
      else{
	if(argMap->inTable(tokenArray[i])){
	  argString = argMap->getValue(tokenArray[i]);
	}
	 else if(jumpFlag == true){
	   string checkString = tokenArray[i] + ":";
	   if(labelMap->inTable(checkString)){
	     argString = labelMap->getValue(checkString);
		jumpFlag = false;
	      }
	      else{
		stringstream s;
		tempLinkCount++;
		s <<tempLinkCount;
		string tempLinkCountString(s.str());
		argString = "q" + tempLinkCountString;
		tempList->add(tokenArray[i],toHex(lineNum));
		jumpFlag = false;
	      }
	 }
	 else if(printStringFlag == true){
	   string argNum = toHex(lineNum);
	   string keyString = tokenArray[i].substr(1, tokLen - 2);
      	   argMap->add(keyString, argNum);
	   argString = argNum;
	   numArgsUsed++;
	 }
	  else{
	    string argNum = toHex(lineNum);
	    argMap->add(tokenArray[i], argNum);
	    argString = argNum;
	    numArgsUsed++;
	  }	      
      }
  }

  lineString = labelString + opString + argString;
  programArray[numLinesFilled] = lineString;
  numLinesFilled++;
 }  
	      	      	     
	      
