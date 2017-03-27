/*                                                                                                                                                       
Russell Laros
rkl218
cse109.154
Progam 7                                                                                                                                              
**/

#ifndef HASH_H
#define HASH_H
#include <stdlib.h>
#include <string>

using namespace std;

class Hash{
 public:
  string key;
  string value;

  Hash();
  Hash(string k, string val);
  ~Hash();

};
#endif
