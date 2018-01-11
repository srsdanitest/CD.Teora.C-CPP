#include <iostream.h>
#include <string.h>
#include <stdlib.h>

class Book {
  public:
    Book(char *title, char *author, char *publisher, float price); // Constructor
    Book() {};
    void show_title(void);
    float get_price(void);
    void show(void);
    void assign_publisher(char *name);
    bool operator==(Book op2);
  private:
    char title[256];
    char author[64];
    float price;
    char publisher[256];
    void show_publisher(void);
};

Book::Book(char *title, char *author, char *publisher, float price)
 {
   strcpy(Book::title, title);
   strcpy(Book::author, author);
   strcpy(Book::publisher, publisher);
   Book::price = price;
 }

void Book::show_title(void)
  { cout << "Title: " << title << endl; };

float Book::get_price(void)
  { return(price); };

void Book::show(void)
  { show_title(); show_publisher(); };

void Book::assign_publisher(char *name)
  { strcpy(publisher, name); };

void Book::show_publisher(void)
  { cout << "Publisher: " << publisher << endl; };

bool Book::operator==(Book op2)
 {
   if(title!=op2.title)
      return false;
   if(author!=op2.author)
      return false;
   if(publisher!=op2.publisher)
      return false;
   if(price!=op2.price)
      return false;
   return true;
 }

template <class DataT> class list_object {
 public:
   DataT info;
   list_object<DataT> *next;
   list_object<DataT> *previous;
   list_object() {
      next = NULL;
      previous = NULL;
    }
   list_object(DataT c) {
      info = c;
      next = NULL;
      previous = NULL;
    }
   list_object<DataT> *getnext() {return next;}
   list_object<DataT> *getprevious() {return previous;}
   void getinfo(DataT &c) { c = info;}
   void change(DataT c) {info = c;}
   friend ostream &operator<<(ostream &stream, list_object<DataT> o)
    {
      stream << o.info << endl;
      return stream;
    }
   friend ostream &operator<<(ostream &stream, list_object<DataT> *o)
    {
      stream << o->info << endl;
      return stream;
    }
/*   friend istream &operator>>(istream &stream, list_object<DataT> &o)
    {
      cout << "Enter information: " << endl;
      stream >> o.info;
      return stream;
    } */
 };

template <class DataT> class linked_list : public list_object<DataT> {
   list_object<DataT> *start, *end;
 public:
   linked_list() {start = end = NULL;}
   void store(DataT c);
//   void store(list_object<DataT> ob);
   void remove(list_object<DataT> *ob);
   void frwdlist();
   void bkwdlist();
   list_object<DataT> *find(list_object<DataT> ob);
   list_object<DataT> *getstart() {return start;}
   list_object<DataT> *getend() {return end;}
 };

template <class DataT> void linked_list<DataT>::store(DataT c)
 {
   list_object<DataT> *p;

   p = new list_object<DataT>;
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

/* template <class DataT> void linked_list<DataT>::store(list_object<DataT> ob)
 {
   list_object<DataT> *p;

   p = new list_object<DataT>;
   if(!p) {
      cout << "Allocation error." << endl;
      exit(1);
    }
   p->info = ob.info;
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
 } */


template <class DataT> void linked_list<DataT>::remove(list_object<DataT> *ob)
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

template <class DataT> void linked_list<DataT>::frwdlist()
 {
   list_object<DataT> *temp;

   temp = start;
   do {
      cout << temp->info << " ";
      temp = temp->getnext();
    } while(temp);
   cout << endl;
 }

template <class DataT> void linked_list<DataT>::bkwdlist()
 {
   list_object<DataT> *temp;

   temp = end;
   do {
      cout << temp->info << " ";
      temp = temp->getprevious();
   } while(temp);
   cout << endl;
 }

template <class DataT> list_object<DataT> *linked_list<DataT>::find(list_object<DataT> ob)
 {
   list_object<DataT> *temp;

   temp = start;
   while(temp) {
      if(ob.info==temp->info) return temp;
      temp = temp ->getnext();
    }
   return NULL;
 }


void main(void)
 {
   linked_list<Book> list;
   Book cbib("Jamsa's C/C++ Programmer's Bible", "Jamsa and Klander", "Jamsa Press", 49.95);
   Book vbtips("1001 Visual Basic Programmer's Tips", "Jamsa and Klander", "Jamsa Press", 54.95);
   Book hacker("Hacker Proof", "Klander", "Jamsa Press", 54.95);
   Book c;
   list_object<Book> *p;

   list.store(cbib);
   list.store(vbtips);
   list.store(hacker);

   cout << "here are some items." << endl;
//   list.bkwdlist();
//   list.frwdlist();
   cout << endl;
   cout << "'Manually' walk through the list." << endl;
   p = list.getstart();
   while(p) {
      p->getinfo(c);
      c.show();
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
 }








