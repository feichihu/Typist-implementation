#ifndef keyLayout_hpp
#define keyLayout_hpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

#include "Constants.hpp"

extern Dict dict;

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
    private:
    friend class Method;
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

    std::string word;
    int freq;
};

std::istream &operator>>(std::istream &str, TXTRow &data);



class Corpus{
    public:
    Corpus(){
        std::ifstream file("wordlist.txt");
        std::string line;
        TXTRow row;
        std::getline(file, line);
        int count{};
        while (file >> row)
        {
            count++;
            totalWeight += row.freq;
            //the whole corpus takes very long time
            //for the purpose of demonstration, we take first 2000 words for illustration
            if(count>2000) break;
            wordlist.push_back(row.data);
        }
    }

    long totalWeight{};
    std::vector<singleCorpusEntry> wordlist{};
};


class keyLayout{
    public:
    const std::vector<char> defaultLayout = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    const std::vector<char> qwertyLayout = {'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m'};

    keyLayout(){
        layout = defaultLayout;
    }
    keyLayout(const keyLayout &p){
        layout = p.layout;
    }
    keyLayout(keyLayout &p){
        layout = p.layout;
    }
    keyLayout(std::vector<char> &p){
        layout = p;
    }
    int operator=(const keyLayout &p){
         layout = p.layout;
         return 0;
    }
    void shuffle(){
        std::cout<<"shuffuling layout"<<std::endl;
        srand(time(NULL)); 
        std::random_shuffle(layout.begin(), layout.end());
    }

    keyLayout neighbor(){
        keyLayout temp(layout);
        temp.swap();
        return temp;
    }

    bool swap(){
        srand(time(NULL));
        int a = rand() % 26;
        int b;
        do{
            b = rand() % 26;
        }while (b == a);
        char temp;
        temp = layout[b];
        layout[b] = layout[a];
        layout[a] = temp; 
        return true;
    }

    int inline Idx(char p){
        return p-'a';
    }

    inline std::string map(std::string in){
        char a = in[0];
        a = layout[Idx(a)];
        return std::string(1,a);
    }
    void printLayout(){
        for(int i = 0; i < 9; i++){
            std::cout<<layout[Idx(qwertyLayout[i])]<<' ';
        }
        std::cout<<layout[Idx(qwertyLayout[9])]<<std::endl;
        std::cout<<' ';
        for(int i = 0; i < 8; i++){
            std::cout<<layout[Idx(qwertyLayout[10 + i])]<<' ';
        }
        std::cout<<layout[Idx(qwertyLayout[18])]<<std::endl;
        std::cout<<"  ";
        for(int i = 0; i < 6; i++){
            std::cout<<layout[Idx(qwertyLayout[19+i])]<<' ';
        }
        std::cout<<layout[Idx(qwertyLayout[25])]<<std::endl;
    }

    private:
    std::vector<char> layout;

};


#endif