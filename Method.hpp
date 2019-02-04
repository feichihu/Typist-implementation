//
//  Method.hpp
//  Assignment1
//
//  Created by nbanovic.
//  Copyright © 2019 Nikola Banovic. All rights reserved.
//

#ifndef Method_hpp
#define Method_hpp

#include <stdio.h>
#include <list>
#include <set>
#include <string>
#include "Operator.hpp"
/*  ASSUMPTION: This typist follows the priciples of Assumption 1-7 in the TYPIST paper, with the following modifications:
  In Assumption 2b, the typist uses both hands, with one finger for each hand in typing
  In Assumption 3, the perceptual processor stays 3 chunks ahead
  In Assumption 4, the typist use a word as a chunk and there is no restricted view issue
  In Assumption 5, 
  In Assumption 6, 
    Perceptual duration is 340ms
    Cognitive duration is 50ms
  In Assumption 7, The only difference bewtween different typists(methods) is their motor operator duration:
    Novice is 230ms
    Intermediate is 170ms
    Expert is 30ms
*/

/* Here is one important observation:
    !!!The Perceptual operator will not apppear in the critical path except at the beginning.
    This is because the shortest 3 words chunk in the sample phrase is "the lazy dog",
    which is has a duration larger than 600ms, even if we only consider the cognitive durations.
    Therefore, critical path can only pass nodes in cognitive operators and motor operators after the first word.
    Thus, for the purpose of reducing complexity, we only consider cognitive and motor operators in this program,
    while adding 340ms to the final result to represent the perceptual of the first word.
*/
/*
    ASSUMPTION: We reperesent schedule chart by doubly linked list of operators. The dependency is represented by 
    the pointing relations.
*/
#define Reconitive_flow_size 54
#define Motor_flow_size 45


class Method
{
    private:
        std::list<Operator*> operators;
    
    public:
        /**
         * Method to parse a phrase into a method. Subclasses should implement their specific strategy and store it as a list of operators.
         */
        Method(double motor_duration);
        ~Method(){
            for(auto i:Recognitive){
                delete i;
            }
            for(auto i:Motor){
                delete i;
            }
        }
        void process(std::string phrase){
            find_path();
        }
        bool if_samehand(std::string a, std::string b); //determine if a and b are typed by the same hand
    
        /**
         * Method to compute duration (in seconds) that would take to execute the method.
         */
        double duration();
        void find_path();
        std::string Perceptual_flow[9] = {"The_","quick_","brown_","fox_", "jumps_", "over_", "the_", "lazy_", "dog."};
        std::string Recognitive_flow[Reconitive_flow_size] = {"The_","shift", "t", "h", "e", "_", "quick_", "q", "u", "i", "c", "k", "_", "brown_", "b", "r", "o", "w", "n", "_", "fox_", "f", "o", "x", "_", "jumps_", "j", "u", "m", "p", "s", "_", "over_", "o", "v", "e", "r", "_", "the_", "t", "h", "e", "_", "lazy_", "l", "a", "z", "y", "_", "dog.", "d", "o", "g", "."};
        std::string Motor_flow[Motor_flow_size] = {"shift", "t", "h", "e", "_", "q", "u", "i", "c", "k", "_", "b", "r", "o", "w", "n", "_", "f", "o", "x", "_", "j", "u", "m", "p", "s", "_", "o", "v", "e", "r", "_", "t", "h", "e", "_", "l", "a", "z", "y", "_", "d", "o", "g", "."};
    private:
        std::vector<Operator*> Recognitive;
        std::vector<Operator*> Motor;
        double real_motor_duration;

};

class NoviceMethod: public Method
{
 public:
    NoviceMethod(): Method(230.0) {}
};

class IntermediateMethod: public Method
{
 public:
    IntermediateMethod(): Method(170.0) {}
};

class ExpertMethod: public Method
{
 public:
    ExpertMethod(): Method(30.0) {}
};

#endif /* Method_hpp */
