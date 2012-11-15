#include "hashMap.cpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

hashMap<string,vector<string> > computeAdjacentWords(const vector<string> &);
vector<string> parseDictionary(string filePath)
{

}

int main()
{
  fstream wordsFile;
  string word;
  vector<string> words;
  string input;

  wordsFile.open("words.txt");

  while(wordsFile.good())
  {
    getline(wordsFile,word);
    words.push_back(word);
  }

  hashMap<string,vector<string> > adjWords = computeAdjacentWords(words);
  cin >> input;
  vector<string> foundWords = adjWords[input];
  vector<string>::const_iterator itr;
  for (itr = foundWords.begin(); itr != foundWords.end(); ++itr)
  {
    cout << *itr << endl;
  }
}

hashMap<string,vector<string> > computeAdjacentWords( const vector<string> & words )
{
  hashMap<string,vector<string> > adjWords;
  hashMap<int,vector<string> > wordsByLength;

  for( int i = 0; i < words.size(); ++i)
  {
    wordsByLength[ words[i].length()].push_back(words[i]);
  }

  hashMap<int,vector<string> >::const_iterator itr;
  for( itr = wordsByLength.begin(); itr != wordsByLength.end(); ++itr)
  {
    const vector<string> & groupsWords = itr->second;
    int groupNum = itr->first;

    for(int i = 0; i < groupNum; i++)
    {
      hashMap<string,vector<string> > repToWord;
      for(int j = 0; j < groupsWords.size(); j++)
      {
        string rep = groupsWords[j];
        rep.erase(i,1);
        repToWord[rep].push_back(groupsWords[j]);
      }

      hashMap<string,vector<string> >::const_iterator itr2;
      for( itr2 = repToWord.begin(); itr2 != repToWord.end(); ++itr2)
      {
        const vector<string> & clique = itr2->second;
        if( clique.size() >= 2)
        {
          for( int p = 0; p < clique.size(); p++)
          {
            for( int q = p+1; q < clique.size(); q++)
            {
              adjWords[clique[p]].push_back( clique[q]);
              adjWords[clique[q]].push_back( clique[p]);
            }
          }
        }
      }
    }
  }
  return adjWords;
}
