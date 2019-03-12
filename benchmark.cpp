#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "constants.hpp"

using u_int = unsigned int;

class singleCorpusEntry
{ // single entry of data in dict
  public:
    singleCorpusEntry(){
        freq = 0;
        word = "";
    }
    singleCorpusEntry(int f, std::string w)
    {
        freq = f;
        word = w;
    }
    singleCorpusEntry(const singleCorpusEntry &p)
    {
        freq = p.freq;
        word = p.word;
    }

    int freq;
    std::string word;
};

class TXTRow //read a single row from wordlist.txt
{
  public:
    void readNextRow(std::istream &str)
    {
        std::string line;
        std::getline(str, line);
        if (line == "")
            return; //trailling empty line
        std::stringstream lineStream(line);
        lineStream>>freq>>word;
        data = singleCorpusEntry(freq, word);

    }

    void print()
    {
        std::cout << "freq=" << freq << " word:" << word << std::endl;
    }
    singleCorpusEntry data;

  private:
    std::string word;
    int freq;
};

std::istream &operator>>(std::istream &str, TXTRow &data)
{
    data.readNextRow(str);
    return str;
}


class Corpus{
    public:
    Corpus(){
        std::ifstream file("wordlist.txt");
        std::string line;
        TXTRow row;
        std::getline(file, line);
        while (file >> row)
        {
            wordlist.push_back(row.data);
        }
    }

    long benchmark(Dict &dict){
        //benchmark new layout and return a weight
        return 0;
    }

    std::vector<singleCorpusEntry> wordlist{};
};

int main(){
    Corpus corpus;
    std::cout<<corpus.wordlist.size();

}