#include "FittsLaw.hpp"

double a = 52.4;
double b = 292.2;
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
    return a * IDn + b;
}
