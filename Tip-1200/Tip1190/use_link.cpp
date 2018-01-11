#include <iostream.h>
#include <string.h>
#include <stdlib.h>

class dblinkob {
 public:
   char info;
   dblinkob *next;
   dblinkob *previous;
   dblinkob() {
      info = 0;
      next = NULL;
      previous = NULL;
    }
   dblinkob *getnext() {return next;}
   dblinkob *getprevious() {return previous;}
   void getinfo(char &c) { c = info;}
   void change(char c) {info = c;}
   friend ostream &operator<<(ostream &stream, dblinkob o)
    {
      stream << o.info << endl;
      return stream;
    }
   friend ostream &operator<<(ostream &stream, dblinkob *o)
    {
      stream << o->info << endl;
      return stream;
    }
   friend istream &operator>>(istream &stream, dblinkob &o)
    {
      cout << "Enter information: " << endl;
      stream >> o.info;
      return stream;
    }
 };

class dllist : public dblinkob {
   dblinkob *start, *end;
 public:
   dllist() {start = end = NULL;}
   void store(char c);
   void remove(dblinkob *ob);
   void frwdlist();
   void bkwdlist();
   dblinkob *find(char c);
   dblinkob *getstart() {return start;}
   dblinkob *getend() {return end;}
 };

void dllist::store(char c)
 {
   dblinkob *p;

   p = new dblinkob;
   if(!p) {
      cout << "Allocation error." << endl;
      exit(1);
    }
   p->info = c;
   if(start==NULL)
    {
      end = start = p;
    }
   else
    {
      p->previous = end;
      end->next = p;
      end = p;
    }
 }

void dllist::remove(dblinkob *ob)
 {
   if(ob->previous)
    {
      ob->previous->next = ob->next;
      if(ob->next)
         ob->next->previous = ob->previous;
      else
         end = ob->previous;
    }
   else
    {
      if(ob->next)
       {
         ob->next->previous = NULL;
         start = ob->next;
       }
      else
         start = end = NULL;
    }
 }

void dllist::frwdlist()
 {
   dblinkob *temp;

   temp = start;
   do {
      cout << temp->info << " ";
      temp = temp->getnext();
    } while(temp);
   cout << endl;
 }

void dllist::bkwdlist()
 {
   dblinkob *temp;

   temp = end;
   do {
      cout << temp->info << " ";
      temp = temp->getprevious();
   } while(temp);
   cout << endl;
 }

dblinkob *dllist::find(char c)
 {
   dblinkob *temp;

   temp = start;
   while(temp) {
      if(c==temp->info) return temp;
      temp = temp ->getnext();
    }
   return NULL;
 }

int main()
 {
   dllist list;
   char c;
   dblinkob *p;

   list.store('1');
   list.store('2');
   list.store('3');

   cout << "here is list backwards, then forwards." << endl;
   list.bkwdlist();
   list.frwdlist();
   cout << endl;
   cout << "'Manually' walk through the list." << endl;
   p = list.getstart();
   while(p) {
      p->getinfo(c);
      cout << c << " ";
      p = p->getnext();
    }
   cout << endl << endl;
   cout << "Looking for item 2." << endl;
   p = list.find('2');
   if(p)
    {
      p->getinfo(c);
      cout << "Found: " << c << endl;
    }
   cout << endl;
   p->getinfo(c);
   cout << "Removing item: " << c << endl;
   list.remove(p);
   cout << "Here is new list forwards." << endl;
   list.frwdlist();
   cout << endl;
   cout << "Adding an item." << endl;
   list.store('4');
   cout << "Here is list forwards." << endl;
   list.frwdlist();
   cout << endl;
   p = list.find('1');
   if(!p)
    {
      cout << "Error, item not found." << endl;
      return 1;
    }
   p->getinfo(c);
   cout << "Changing " << c << " to 5." << endl;
   p->change('5');
   cout << "Here is list forwards, then backwards." << endl;
   list.frwdlist();
   list.bkwdlist();
   cout << endl;
   cin >> *p;
   cout << p;
   cout << "Here is list forwards again." << endl;
   list.frwdlist();
   cout << endl;
   cout << "Here is list after removing head of list." << endl;
   p = list.getstart();
   list.remove(p);
   list.frwdlist();
   cout << endl;
   cout << "Here is list after removing end of list." << endl;
   p = list.getend();
   list.remove(p);
   list.frwdlist();
   return 0;
 }
 







