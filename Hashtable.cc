/*                                                                                                                                                       
Russell Laros
rkl218
cse109.15
Program 7                                                                                                                                              
**/

#include "Hashtable.h"
#include "Hash.h"
#include <iostream>

HashTable::HashTable(): size(23){
  table = new Hash*[23];
  table[0] = new Hash("ADD","a0");
  table[1] = new Hash("SUB","a1");
  table[2] = new Hash("MULT","a2");
  table[3] = new Hash("DIV","a3");
  table[4] = new Hash("REM","a4");
  table[5] = new Hash("DUP","a5");
  table[6] = new Hash("AND","b0");
  table[7] = new Hash("OR","b1");
  table[8] = new Hash("NOT","b2");
  table[9] = new Hash("ISEQ","b3");
  table[10] = new Hash("ISNE","b4");
  table[11] = new Hash("ISGT","b5");
  table[12] = new Hash("ISGE","b6");
  table[13] = new Hash("ISLT","b7");
  table[14] = new Hash("ISLE","b8");
  table[15] = new Hash("LOADL","c0");
  table[16] = new Hash("LOADV","c1");
  table[17] = new Hash("STOREV","c2");
  table[18] = new Hash("JUMP","d0");
  table[19] = new Hash("JUMPF","d1");
  table[20] = new Hash("PRINT","e0");
  table[21] = new Hash("PRINTLN","e1");
  table[22] = new Hash("PRINTS", "e2");
}

HashTable::HashTable(int siz): size(siz){
  table = new Hash*[siz];
  for(int i = 0; i < size; i++){
    table[i] = NULL;
  }
}

bool HashTable::inTable(string k){
  bool check = false;
  for(int i = 0; i < size; i++){
    if(table[i] != NULL){
      if(table[i]->key == k){
      check = true;
      }
    }
  }
  return check;
}

HashTable::~HashTable(){}

void HashTable::add(string k, string val){
  bool check = false;
  int i = 0;
  while(i < size && check == false){
    if(inTable(k) == true){
      check = true;
    }
    else{
      if(table[i] == NULL){
	table[i] = new Hash(k, val);
	check = true;
      }
    }
    i++;
  }
  if(i >= size){
    cout <<"Error: exceeded table size limitations i is "<< i << endl;
  }
}

string HashTable::getValue(string k){
  int i = 0;
  bool check = false;
  if(inTable(k) == false){
    exit(1);
  }
  else{
    while(i < size || check == false){
      if(table[i] != NULL){
	if(table[i]->key == k){
	  check = true;
	  break;
	}
      }
      i++;
    }
    return table[i]->value;
  }
}
