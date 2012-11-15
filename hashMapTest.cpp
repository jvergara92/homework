#include <iostream>
#include "hashMap.cpp"
#include <string>

using namespace std;

int main()
{
  hashMap<int,int> test;
  hashMap<int,int> test2(test);
  hashMap<int,int> test3;
  test = test3;
  test[5] = 5;
  hashMap<string,string> stringTest;
  stringTest["test"] = "test";
  cout << stringTest["test"];
  hashMap<int,int> test4(50);
  test[5] = 5;
  test[55] = 5;
  cout << test[5] << test[55] << endl;
}
