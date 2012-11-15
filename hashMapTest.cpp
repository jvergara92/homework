#include <iostream>
#include "hashMap.cpp"
#include <string>

using namespace std;

int main()
{
  hashMap<string,string> stringTest;
  stringTest["test"] = "test";
  stringTest["test2"] = "test2";
  hashMap<string,string>::const_iterator itr;
  for(itr = stringTest.begin(); itr != stringTest.end(); ++itr)
  {
    cout << itr->second << endl;
  }
}
