/*                                                                                                                                                       
Russell Laros
rkl218
cse109.154
Program 7                                                                                                                                             
**/

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "Hash.h"
#include <iostream>

using namespace std;

class HashTable{
 public:
	Hash ** table;
	HashTable();
	HashTable(int s);
	~HashTable();

	int size; 
	bool inTable(string k);
	void add(string k, string val);
	string getValue(string k);
};

#endif
