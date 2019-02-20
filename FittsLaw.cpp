#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <cmath>
#include <unordered_map>
#include <utility>
#include "Constants.hpp"

const double a = 52.4;
const double b = 292.2;
const double degreePermm = 1.165;


class Fitts{// this is an instance of Fitts' Law on tablet key board, it takes an input (from, to) pair and return the movement time
    //Assume Expert and Novice users have the same motor operator

    public: 
        Fitts(Dict& dic){
            dict = dic;
        }
        double Time(std::string from, std::string to){
            double IDn = dict.query(from, to).ID;
            return a*IDn + b;
        }
    private:
        Dict dict;

};

std::istream &operator>>(std::istream &str, CSVRow &data)
{
    data.readNextRow(str);
    return str;
}

int main()
{
    std::ifstream file("Keyboard.csv");
    std::string line;
    CSVRow row;
    std::getline(file, line);
    double min = 100;
    double max = 0;
    Dict dict; 
    while (file >> row)
    {
        dict.insert(row);
        row.print();
        if (row.ID < min && row.ID != 0)
            min = row.ID;
        if (row.ID > max)
            max = row.ID;
    }
    Fitts Motor(dict);

    //std::cout << "the ID range is (" << min << ", " << max << ")";
    std::cout<<Motor.Time("f","t")<<std::endl;
    std::cout<<Motor.Time("t","f")<<std::endl;
    std::string phrase;
    std::cin >> phrase;
}