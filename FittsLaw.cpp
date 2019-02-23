#include "FittsLaw.hpp"

//These constants are found in the FFitts paper.
double a = 52.4;
double b = 292.2;
//The calculation for this constant is in Emma.hpp
double degreePermm = 1.165;

Fitts::Fitts()
{
}
Fitts::Fitts(Dict &dic)
{
    dict = dic;
}
double Fitts::Time(std::string from, std::string to)
{
    double IDn = dict.query(from, to).ID;
    //std::cout<<"Fitts takes"<<a*IDn +b<<" time"<<std::endl;
    return a * IDn + b;
}
