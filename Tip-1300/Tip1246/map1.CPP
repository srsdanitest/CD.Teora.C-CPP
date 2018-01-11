#ifdef __BCPLUSPLUS__
#include <map.h>
#else
#include <map>
#endif

#include <iostream.h>
#include <string.h>

using namespace std;
class ltstr
 {
  public:
    bool operator()(const char* s1, const char* s2) const
     { return (strcmp(s1, s2) < 0);}
 };

void main(void)
{
  map<const char*, int, ltstr> months;
  
  months["January"] = 31;
  months["February"] = 28;
  months["March"] = 31;
  months["April"] = 30;
  months["May"] = 31;
  months["June"] = 30;
  months["July"] = 31;
  months["August"] = 31;
  months["September"] = 30;
  months["October"] = 31;
  months["November"] = 30;
  months["December"] = 31;
  
  cout << "june -> " << months["June"] << endl;
  map<const char*, int, ltstr>::iterator cur  = months.find("June");
  map<const char*, int, ltstr>::iterator prev = cur;
  map<const char*, int, ltstr>::iterator next = cur;
  ++next;
  --prev;
  cout << "Previous (in alphabetical order) is " << (*prev).first << endl;
  cout << "Next (in alphabetical order) is " << (*next).first << endl;
}
