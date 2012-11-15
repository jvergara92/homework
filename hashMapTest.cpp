#include <iostream>
#include "hashMap.cpp"
#include <string>

using namespace std;

int main()
{
  hashMap<string,string> stringTest;
  stringTest["test"] = "test";
  cout << stringTest["test"];
}
