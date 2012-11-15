#include <string>
#include <iostream>
#include <vector>

using namespace std;

template <class Key,class Value>
class hashMap
{
  public:
    explicit hashMap( int size = 101 ) : arraySize( size ){
      array.clear();
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
      array.clear();
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
        int count = 1;
        int initial = 1;
        while (array[pos].active != false && array[pos].first != key && count < arraySize)
        {
          pos = initial+(count*count);
          pos %= arraySize;
          ++count;
        }
        if(count == arraySize)
        {
          rehash();
          return operator[](key);
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
        const cell * operator->()
        {
          return &(hm->findAtPos(pos));
        }
        const const_iterator & operator++()
        {
          pos = hm->findNext(pos);
          return *this;
        }
        bool operator!=(const const_iterator & rhs)
        {
          if(pos == rhs.pos && hm == rhs.hm)
          {
            return false;
          }
          return true;
        }
      private:
        int pos;
        hashMap * hm;
      friend class hashMap;
    };

    const const_iterator begin(){
      const_iterator itr;
      int pos = 0;
      if (array[0].active == false)
      {
        pos = findNext(pos);
      }
      itr.hm = this;
      itr.pos = pos;
      return itr;
    }
    
    const const_iterator end(){
      const_iterator itr;
      itr.pos = arraySize;
      itr.hm = this;
      return itr;
    }

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
    int findNext(int pos)
    {
      do{
        ++pos;
      }while(array[pos].active == false && pos != arraySize);
      return pos;
    }
    cell & findAtPos(int pos)
    {
      return array[pos];
    }
    void rehash()
    {
      vector<cell> oldArray = array;
      array.clear();
      array.resize(arraySize*2+1);
      int hashVal;
      for(int i = 0; i != arraySize; ++i)
      {
        if(oldArray[i].active == false)
        {
          continue;
        }
        hashVal = hash(oldArray[i].first, arraySize*2);
        array[hashVal].first = oldArray[i].first;
        array[hashVal].second = oldArray[i].second;
        array[hashVal].active = true;
      }
      arraySize *= 2;
      
    }
};
