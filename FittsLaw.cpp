#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <cmath>
#include <unordered_map>
#include <utility>


const double a = 0.0;
const double b = 0.0;

class CSVRow //read a single row from csv
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

    inline void calculation(){ //calculate M_T 
        // Using Fitts Law on one dimension here, approximate the keyboard to 
        // be of 1-D.
        ID = log2(distance/width+1);//Shannon formulation
        MT = a + b * ID; 
    }

    void print(){
        std::cout<<"from"<<from<<"to"<<to<<"width"<<width<<"distance"<<distance<<std::endl;
    }

        double ID; 
    private:
        std::string from;
        std::string to;
        double width;
        double distance;
        double MT;
};

class dict
{
    public:
    double query(std::string from, std::string to){//return movement time from Fitts' Law
        if(keys2time.find(from+to)!=keys2time.end()){
            return keys2time[from+to];
        }
        else{
            std::cerr<<"can't find ("<<from<<", "<<to<<") pair in the dict";
            return 0.0;
        }
    }

    private:
        std::unordered_map<std::string, double> keys2time; // record key_pair to movement time
        
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
    double min = 100;
    double max = 0;
    while(file>>row)
    {
       row.print(); 
       row.calculation();
       if(row.ID<min&&row.ID!=0) min = row.ID;
       if(row.ID>max) max = row.ID;
    }

    std::cout<< "the ID range is ("<< min<<", "<<max<<")";
    std::string phrase;
    std::cin>>phrase;
}