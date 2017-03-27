/*                                                            
Russell Laros
rkl218
cse109.154
Program 7
**/


#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include "Assembler.h"
#include "Hashtable.h"
#include "Hash.h"
#include "Link.h"

using namespace std;

bool isSasm(string str, int len){
  bool flag = false;
  if(len <= 5){
    flag = false;
  }
  else{
    if(str.substr(len - 5, 5) == ".sasm"){
      flag = true;
    }
    else{
      flag = false;
    }
  }
  return flag;
}

string toHexString(string s){
  stringstream conv;
  string cunt = "";
  string temp = "";
  int stringLen = (int)s.length();
  for(int x = 0; x <stringLen; x++){
    char changeStr = s[x];
    int changeInt = changeStr;
    conv<<std::hex<<changeInt;
    temp = conv.str();
    conv.str("");
    conv.clear();
    cunt = cunt + temp;
  }
  return cunt;
}

void processByteCode(ifstream& in, ofstream& out, Assembler& a){
  int j = 0;
  while(!in.eof()){
  string line = a.getLine();
  a.processLine(line);
    }
  in.close();
  while(j < a.numLinesFilled){
    out<<a.programArray[j];
    j++;
  }
  out<<"000000";
  j = 0;
    while(a.labelMap->table[j] != NULL){
    out<<a.labelMap->table[j]->value;
    out<<toHexString(a.labelMap->table[j]->key);
    out<<"ff";
    j++;
  }
  out<<"aa";
  j = 0;
  while(a.argMap->table[j] != NULL){
    out<<a.argMap->table[j]->value;
    out<<toHexString(a.argMap->table[j]->key);
    out<<"ff";
    j++;
  }
  out<<"aa";
  out.close();
}

int main(int argc, char ** argv){
 int tempProgArrSize = 0;
 int tempLArrSize = 0;
 int tempArgumentArrSize = 0;
 string tempProgArray[255];
 string tempLArray[255];
 string tempArgumentArray[255];
 ofstream out;
 int i = 1;
 ifstream in;
 
 for(int m = 0; m < 255; m++){
   tempProgArray[m] = "";
   tempLArray[m] = "";
   tempArgumentArray[m] = "";
 }
 Assembler assembler(in);
 while(i < argc){
   string arg = argv[i];
   int argLen = (int) arg.length();
   if (arg == "-i") {
     cout << "operation   " << "   byte code \n";
     for(int k = 0; k < 23; k++){
       cout<<assembler.help->table[k]->key << "               "<<assembler.help->table[k]->value<<endl;
     }
     cout<<endl;
     i++;  
   }
   else if (arg == "-h") {
   cout<<"To assemble 1 or more files: ./assemble file1.sasm file2.sasm..." <<endl;
   cout<<"Passing in file names as command line args saves them as *.s files to pass into the Linker."<<endl;
   cout<<"Command line arguments:"<<endl;
   cout<<"    -h displays this usage information"<<endl;
   cout<<"    -i prints all the .sasm instructions as well as their bytecode representation."<<endl;
   cout<<"    -l prints the label map. The decimal value of the 1 byte hex string on the left and the respective label on the right."<<endl;
   cout<<"    -a prints the instruction arguments. The decimal value of the 1 byte hex string on the left and the respective argument on the right."<<endl;
   cout<<"    -p prints the bytecode of the .sasm program. It prints every instruction on its own line, mirroring the .sasm that was input."<<endl;
   cout<<endl;
   i++;
   }
   else if(arg == "-l"){
     string theString = "";
     int len = 0;
     bool flagF = false;
     for(int ni = i; ni > 1; ni--){
       theString = argv[ni-1];
       len = (int) theString.length();
       if(isSasm(argv[ni-1], len) == true ){
	   flagF = true;
       }
     }
     if(flagF == false){
       cout<<"Error, need a file to convert"<<endl;
       exit(1);
     }
     else{
       int l = 0;
       while(l < tempLArrSize){
         cout<<tempLArray[l]<<endl;
         l++;
       }
       cout<<endl;
       i++;
     }
   }
     else if(arg =="-a"){
       string theString = "";
       int len = 0;
       bool flagF = false;
       for(int ni = i; ni > 1; ni--){
	 theString = argv[ni-1];
	 len = (int) theString.length();
	 if(isSasm(argv[ni-1], len) == true ){
           flagF = true;
	 }
       }
       if(flagF == false){
	 cout<<"Error, need a file to convert"<<endl;
	 exit(1);
       }
       else{
	 int l = 0;
	 while(l < tempArgumentArrSize){
	   cout<<tempArgumentArray[l]<<endl;
      	   l++;
	 }
	 cout<<endl;
	 i++;
       }
     }
   else if(arg == "-p"){
     string theString = "";
     int len = 0;
     bool flagF = false;
     for(int ni = i; ni > 1; ni--){
       theString = argv[ni-1];
       len = (int) theString.length();
       if(isSasm(argv[ni-1], len) == true ){
	 flagF = true;
       }
     }
     if(flagF == false){
       cout<<"Error, need a file to convert"<<endl;
       exit(1);
     }
     else{
       int l = 0;
       while(l < tempProgArrSize){
	 cout<<tempProgArray[l]<<endl;
	 l++;
       }
       cout<<endl;
       i++;
     }
   }
   else if(argLen >= 6 && arg.substr(argLen - 5, 5) ==".sasm"){
     string name = arg.substr(0, argLen - 5);
     name = name + ".s";
     const char * nameCStr = name.c_str();
     out.open(nameCStr);
     in.open(argv[i]);
     Assembler ass(in);
     processByteCode(in, out, ass);
     in.close();
     for(int q = 0; q <ass.numLinesFilled; q++){
       tempProgArray[q] = ass.programArray[q];
       tempProgArrSize++;
     }
     tempProgArray[tempProgArrSize++] = "000000";
     for(int g = 0; g< ass.numLabelsUsed; g++){
       tempLArray[g] = ass.labelMap->table[g]->value + toHexString(ass.labelMap->table[g]->key) + "ff";
       tempLArrSize++;
     }
     tempLArray[tempLArrSize++] = "aa";
     for(int r = 0; r< ass.numArgsUsed;r++){
       tempArgumentArray[r] = ass.argMap->table[r]->value + toHexString(ass.argMap->table[r]->key) + "ff";
       tempArgumentArrSize++;
     }
     tempArgumentArray[tempArgumentArrSize++] = "aa";
     i++;
   }
   else{ 
     cout<<"error "<<arg<<" is not a valid command, type -h for commands"<<endl;
     exit(1);
   }
 }
 return 0;
}
