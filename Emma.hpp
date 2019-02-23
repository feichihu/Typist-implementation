#ifndef Emma_hpp
#define Emma_hpp

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
        We use a 246mm * 185mm (12inch) with resolution 1024 * 768 tablet
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
    Emma();
    Emma(Dict &dic, bool ifNovice);
    double Time(std::string from, std::string to); // This function inputs (from, to) pair and return the keyboard searching time
    inline double Encoding(double freq, double epsilon);
    inline double LTM();

  private:
    Dict dict{};
    bool Novice{};
};

#endif