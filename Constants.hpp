#ifndef Constants_hpp
#define Constants_hpp

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <unordered_map>

//Constants
extern double tau;
extern double d ;
extern double F;
extern double f;
extern double sigma_M;
extern double alpha;
extern double sigma_U;
extern double  K;
extern double  k;
extern double  t_prep;
extern double  t_exec;
extern double  t_sacc;
extern double  sigma_V;
extern std::unordered_map<char,double> eng_freq;
extern double degreePermm;
extern double a;
extern double b;



class singleEntry
{ // single entry of data in dict
  public:
    singleEntry(){
        distance = 0;
        width = 0;
        ID = 0;
        degree = 0;
    }
    singleEntry(double d, double w)
    {
        distance = d;
        width = w;
        ID = log2(d/ w+ 1); //Shannon formulation
        degree = d* degreePermm;
    }
    singleEntry(const singleEntry &p)
    {
        distance = p.distance;
        width = p.width;
        ID = p.ID;
        degree = p.degree;
    }
    double distance;
    double width;
    double ID;
    double degree;
};

class CSVRow //read a single row from csv
{
  public:
    void readNextRow(std::istream &str)
    {
        std::string line;
        std::getline(str, line);
        if (line == "")
            return; //trailling empty line
        std::stringstream lineStream(line);
        std::string cell;
        std::getline(lineStream, from, ','); //from
        std::getline(lineStream, to, ',');   //to
        std::getline(lineStream, cell, ','); //width
        std::cout << "reading cell" << cell << std::endl;
        double width = std::stod(cell);
        std::getline(lineStream, cell, ','); //height
        std::getline(lineStream, cell);      //distance
        std::cout << "reading cell" << cell << std::endl;
        double distance = std::stod(cell);
        data = singleEntry(distance, width);

    }

    inline void calculation()
    { //calculate M_T
        // Using Fitts Law on one dimension here, approximate the keyboard to
        // be of 1-D.
        ID = log2(data.distance / data.width + 1); //Shannon formulation
        MT = a + b * ID;
    }
    
    inline std::string key(){
        return from+to;
    }

    void print()
    {
        std::cout << "from" << from << "to" << to << "width" << data.width << "distance" << data.distance << std::endl;
    }

    double ID;
    friend class Dict;

  private:
    std::string from;
    std::string to;
    singleEntry data;
    double MT;
};



class Dict // We use this dict to query any (from, to) pair related data
{
  public:
    Dict(){
        keys2time.clear();
    }
    Dict(const Dict& p){
        keys2time = p.keys2time;
    }
    singleEntry query(std::string from, std::string to)
    { //return movement time from Fitts' Law
        if (keys2time.find(from + to) != keys2time.end())
        {
            return keys2time[from + to];
        }
        else
        {
            std::cout << "can't find (" << from << ", " << to << ") pair in the dict";
            return singleEntry();
        }
    }
    void insert(CSVRow &row)
    {
        keys2time[row.key()] = row.data;
    }

  private:
    std::unordered_map<std::string, singleEntry> keys2time; // record key_pair to movement time
};

#endif