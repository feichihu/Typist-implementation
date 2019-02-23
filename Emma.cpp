#include "Emma.hpp"

double tau = 4.0;
double d = 0.5;
double F = 1.06;
double f = 1.53;
double sigma_M = 0.6;
double alpha = 0.02;
double sigma_U = 0.26;
double K = 0.4;
double k = 0.006;
double t_prep = 0.2;
double t_exec = 0.070;
double t_sacc = 0.002;
double sigma_V = 0.1;
std::unordered_map<char, double> eng_freq = {{' ', 0.2}, {'a', 0.082}, {'b', 0.015}, {'c', 0.028}, {'d', 0.043}, {'e', 0.127}, {'f', 0.022}, {'g', 0.02}, {'h', 0.061}, {'i', 0.07}, {'j', 0.002}, {'k', 0.008}, {'l', 0.04}, {'m', 0.024}, {'n', 0.067}, {'o', 0.075}, {'p', 0.019}, {'q', 0.001}, {'r', 0.06}, {'s', 0.063}, {'t', 0.091}, {'u', 0.028}, {'v', 0.01}, {'w', 0.024}, {'x', 0.002}, {'y', 0.02}, {'z', 0.001}};

Emma::Emma()
{
    Novice = Novice;
}

Emma::Emma(Dict &dic, bool ifNovice)
{
    dict = dic;
    Novice = ifNovice;
}

// This function inputs (from, to) pair and return the keyboard searching time
// Return value in ms
double Emma::Time(std::string from, std::string to)
{
    // time = Vision + LTM
    //      = Encoding time + LTM
    singleEntry datum = dict.query(from, to);
    char p = from[0];
    double encodingTime = Encoding(eng_freq[p], datum.degree);
    double LTMTime = LTM();
    if(Novice)
        std::cout<<"Novice";
    else
        std::cout<<"Expert ";
    std::cout<<"Emma takes "<< encodingTime<< " "<< LTMTime<<std::endl;

    return 1000*(encodingTime + LTMTime);
}

inline double Emma::Encoding(double freq, double epsilon)
{
    double Te = K * (-log10(freq)) * exp(k * epsilon);
    return Te;
}

inline double Emma::LTM()
{
    double Bi = Novice ? 0 : log(2);
    return F * exp(-f * Bi);
}