#include "Link.h"

Link::Link():theKey(""),data(0),d(NULL),n(NULL){

}

Link::Link(const char *k, int d, Link* next):theKey(k),data(d),d(NULL),n(next){}

Link::Link(const char *k, string str, Link* next):theKey(k),data(0),d(str),n(next){}

Link::Link(const Link& t):theKey(t.theKey),data(t.data),n(t.n){}

ostream & operator<<(ostream& out,const Link& x){
  out << "("<< x.theKey << ", " << x.data << ")";
  return out;
}

/*  Some simple tests of the class Link */
void show(Link *t){
  while(t != NULL){
    cout << "-->" << *t;
    t = t->n;
  }
  cout<<endl;
}
