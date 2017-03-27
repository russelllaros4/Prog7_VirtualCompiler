/*
Russell Laros
rkl218
cse109.154
Program 7
*/
#ifndef LINK_H
#define LINK_H
#include <iostream>
#include <fstream>

using namespace std;

class Link{
public:
	const char *theKey;  
	int data;  
	string d;
	Link *n;

	Link(const char *k, double d = 0, Link *next = NULL);

	Link(const Link &t);

	friend ostream& operator <<(ostream& out, const Link &t);
};
#endif
