#include <iostream.h>
#include <string.h>
#include <stdlib.h>

template <class DataT> class dblinkob {
 public:
   DataT info;
   dblinkob<DataT> *next;
   dblinkob<DataT> *previous;
   dblinkob() {
      info = 0;
      next = NULL;
      previous = NULL;
    }
   dblinkob(DataT c) {
      info = c;
      next = NULL;
      previous = NULL;
    }
   dblinkob<DataT> *getnext() {return next;}
   dblinkob<DataT> *getprevious() {return previous;}
   void getinfo(DataT &c) { c = info;}
   void change(DataT c) {info = c;}
   friend ostream &operator<<(ostream &stream, dblinkob<DataT> o)
    {
      stream << o.info << endl;
      return stream;
    }
   friend ostream &operator<<(ostream &stream, dblinkob<DataT> *o)
    {
      stream << o->info << endl;
      return stream;
    }
   friend istream &operator>>(istream &stream, dblinkob<DataT> &o)
    {
      cout << "Enter information: " << endl;
      stream >> o.info;
      return stream;
    }
 };

template <class DataT> class dllist : public dblinkob<DataT> {
   dblinkob<DataT> *start, *end;
 public:
   dllist() {start = end = NULL;}
   void store(DataT c);
   void remove(dblinkob<DataT> *ob);
   void frwdlist();
   void bkwdlist();
   dblinkob<DataT> *find(DataT c);
   dblinkob<DataT> *getstart() {return start;}
   dblinkob<DataT> *getend() {return end;}
 };

template <class DataT> void dllist<DataT>::store(DataT c)
 {
   dblinkob<DataT> *p;

   p = new dblinkob<DataT>;
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

template <class DataT> void dllist<DataT>::remove(dblinkob<DataT> *ob)
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

template <class DataT> void dllist<DataT>::frwdlist()
 {
   dblinkob<DataT> *temp;

   temp = start;
   do {
      cout << temp->info << " ";
      temp = temp->getnext();
    } while(temp);
   cout << endl;
 }

template <class DataT> void dllist<DataT>::bkwdlist()
 {
   dblinkob<DataT> *temp;

   temp = end;
   do {
      cout << temp->info << " ";
      temp = temp->getprevious();
   } while(temp);
   cout << endl;
 }

template <class DataT> dblinkob<DataT> *dllist<DataT>::find(DataT c)
 {
   dblinkob<DataT> *temp;

   temp = start;
   while(temp) {
      if(c==temp->info) return temp;
      temp = temp ->getnext();
    }
   return NULL;
 }

int main()
 {
   dllist<double> list;
   double c;
   dblinkob<double> *p;

   list.store(1.1);
   list.store(2.2);
   list.store(3.3);

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
   cout << "Looking for item 2.2." << endl;
   p = list.find(2.2);
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
   list.store(4.4);
   cout << "Here is list forwards." << endl;
   list.frwdlist();
   cout << endl;
   p = list.find(1.1);
   if(!p)
    {
      cout << "Error, item not found." << endl;
      return 1;
    }
   p->getinfo(c);
   cout << "Changing " << c << " to 5." << endl;
   p->change(5.5);
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
 







