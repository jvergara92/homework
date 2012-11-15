#include <string>
#include <iostream>
#include <vector>

using namespace std;

template <class Key,class Value>
class hashMap
{
  public:
    explicit hashMap( int size = 101 ) : arraySize( size ){
      array.resize(arraySize+1);
    }
    hashMap(const hashMap & rhs){
      arraySize = rhs.arraySize;
      array.resize(arraySize+1);
      for(int i = 0; i < arraySize; i++)
      {
        array[i] = rhs.array[i];
      }
    }
    ~hashMap()
    {
    }
    hashMap & operator=(const hashMap & rhs){
      if (&rhs != this)
      {
        arraySize = rhs.arraySize;
        array.clear();
        array.resize(arraySize+1);
        for(int i = 0; i < arraySize; i++)
        {
          array[i] = rhs.array[i];
        }
      }
    }
    Value & operator[](const Key & key)
    {
        unsigned long long pos = hash(key, arraySize);
        unsigned long long quad = 1;
        while (array[pos].active != false && array[pos].first != key)
        {
          pos += quad;
          pos %= arraySize;
          quad *= 2;
        }
        array[pos].first = key;
        array[pos].active = true;
        return array[pos].second;
    }

    struct cell{
      Key first;
      Value second;
      bool active;
      cell(){
        active = false;
      }
    };

    class const_iterator
    {
      public:
        cell operator*()
        {
          return array[pos];
        }
      private:
        int pos;
    };

  private:
    vector<cell> array;
    int arraySize;
    int hash(const std::string & key, int tableSize)
    {
      int hashVal = 0;
      
      for(int i = 0; i < key.length(); i++)
      {
        hashVal = 37 * hashVal + key[i];
      }

      hashVal %= tableSize;
      if(hashVal < 0)
      {
        hashVal += tableSize;
      }

      return hashVal;
    }
    int hash(int key, int tableSize)
    {
      return key%tableSize;
    }
};
