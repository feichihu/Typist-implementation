#ifndef Fitt_hpp
#define Fitts_hpp

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <cmath>
#include <unordered_map>
#include <utility>
#include "Constants.hpp"


class Fitts{// this is an instance of Fitts' Law on tablet key board, it takes an input (from, to) pair and return the movement time
    //Assume Expert and Novice users have the same motor operator

    public: 
        Fitts();
        Fitts(Dict& dic);
        double Time(std::string from, std::string to);
    private:
        Dict dict;
};

#endif


