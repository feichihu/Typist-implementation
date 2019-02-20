#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <cmath>
#include <unordered_map>
#include <utility>
#include "Constants.hpp"

const double a = 0.0;
const double b = 0.0;
const double degreePermm = 1.165;



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

    //std::cout << "the ID range is (" << min << ", " << max << ")";
    std::cout<<dict.query("f","t").distance<<std::endl;
    std::cout<<dict.query("t","f").distance<<std::endl;
    std::string phrase;
    std::cin >> phrase;
}