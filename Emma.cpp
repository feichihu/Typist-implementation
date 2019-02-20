#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <cmath>
#include <unordered_map>
#include <utility>
#include "Constants.hpp"


const double tau = 4.0;
const double d = 0.5;
const double F = 1.06;
const double f = 1.53;
const double sigma_M = 0.6;
const double alpha = 0.02;
const double sigma_U = 0.26;
const double  K = 0.4;
const double  k = 0.006;
const double  t_prep = 0.2;
const double  t_exec = 0.070;
const double  t_sacc = 0.002;
const double  sigma_V = 0.1;
const double degreePermm = 1.165;
const std::unordered_map<char,double> eng_freq = {{'a', 0.082}, {'b', 0.015}, {'c', 0.028}, {'d', 0.043}, {'e', 0.127}, {'f', 0.022}, {'g', 0.02}, {'h', 0.061}, {'i', 0.07}, {'j', 0.002}, {'k', 0.008}, {'l', 0.04}, {'m', 0.024}, {'n', 0.067}, {'o', 0.075}, {'p', 0.019}, {'q', 0.001}, {'r', 0.06}, {'s', 0.063}, {'t', 0.091}, {'u', 0.028}, {'v', 0.01}, {'w', 0.024}, {'x', 0.002}, {'y', 0.02}, {'z', 0.001}};

/*
    Emma is an instance of the model EMMA in keyboard search
    Here are a few assumptions:
    Please note that the following assumptions have been tested on the given emphirical data in the paper.
    1.  Keyboard never change, so there is no controller and utility function.
    2.a We use the simplest case for VISION that encoding time equals eye movement time.
        So we only consider encoding time for vision. In fact, I don't have enough data to 
        implement a random key search simulator.
    2.b There is not second fixation in any case. Anyone lands on the target in one go. 
    2.c Therefore, VSTM is useless in this model.
    2.d Assume we are using a tablet PC for typing. According to the data in this paper: https://core.ac.uk/download/pdf/11031705.pdf
        We use a 246mm * 185mm (12mm) with resolution 1024 * 768 tablet
        Assume length data in  keyboard.csv is in mm
        1 pixel = 0.028 degrees.
        1 mm = 4.16 pixels = 1.165 degrees.

    3.a Novice user has empty LTM and never learns.
    3.b Expert user has constant LTM that all B_i = ln(2).
    3.c That is the only difference between Novice and Expert in cognition operator.
    4. There is no noise of any kind. Our users are robust cyborgs.
*/
class Emma
{
    public:

    // This function inputs (from, to) pair and return the keyboard searching time
    double search(std::string from, std::string to){
        return 0.0;
    }

    private:


    //LTM



};