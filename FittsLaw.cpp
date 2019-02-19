#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>


class CSVRow
{
    public:
    void readNextRow(std::istream& str)
    {
        std::string line;
        std::getline(str, line);
        if(line=="") return; //trailling empty line
        std::stringstream lineStream(line);
        std::string cell;
        std::getline(lineStream, from, ',');//from
        std::getline(lineStream, to, ',');//to
        std::getline(lineStream, cell, ',');//width
        std::cout<<"reading cell"<<cell<<std::endl;
        width = std::stod(cell);
        std::getline(lineStream, cell, ',');//height
        std::getline(lineStream, cell);//distance
        std::cout<<"reading cell"<<cell<<std::endl;
        distance = std::stod(cell);
    }

    void print(){
        std::cout<<"from"<<from<<"to"<<to<<"width"<<width<<"distance"<<distance<<std::endl;
    }

    private:
        std::string from;
        std::string to;
        double width;
        double distance;
        double ID; 
};

std::istream& operator>>(std::istream& str, CSVRow& data){
    data.readNextRow(str);
    return str;
}

int main(){
    std::ifstream file("Keyboard.csv");
    std::string line;
    CSVRow row;
    std::getline(file, line);
    while(file>>row)
    {
       row.print(); 
    }
}