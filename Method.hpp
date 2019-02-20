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
#include <cctype>
#include "Operator.hpp"

#define Reconitive_flow_size 54
#define Motor_flow_size 45
#define Perceptual_Duration 340
#define Recognitive_Duration 50
#define Motor_Duration 50
/*  ASSUMPTION: This typist follows the priciples of Assumption 1-7 in the TYPIST paper, with the following modifications:
  In Assumption 2b, the typist uses both hands, with one finger for each hand in typing
  In Assumption 3, the perceptual processor stays 3 chunks ahead
  In Assumption 4, the typist use a word as a chunk and there is no restricted view issue
  In Assumption 5, 
  In Assumption 6, 
    Perceptual duration is 340ms
    Cognitive duration for fetch a word is 50 ms
    Cognitive duration for single key is keyboard search time
    Motor duration is fitts' law movement time
  !!!The only difference bewtween different typists(methods) is their keyboard search duration
*/

/* Here is one important assumption:
    This program only simulate input of letters and space. Any other character is not supported due to lack of experimental data.
    Also, this program does not distinguish UPPER or lower cases(no shift key), since usually mobile keyboard will automatically switch cases.
*/
/*
    ASSUMPTION: We reperesent schedule chart by linked list of operators. The dependency is represented by 
    the pointing relations.
*/




class Method
{
    private:
        std::list<Operator*> operators;
    
    public:
        /**
         * Method to parse a phrase into a method. Subclasses should implement their specific strategy and store it as a list of operators.
         */
        Method(bool ifNovice);//init schedule chart
        void process(std::string phrase){
            // encode given phrase into schedule chart
        }
        bool ifValid(std::string input);
        void find_path();// find path from schedule chart
        bool if_samehand(std::string a, std::string b); //determine if a and b are typed by the same hand
        /**
         * Method to compute duration (in seconds) that would take to execute the method.
         */
        double duration();
    protected:
        std::vector<Operator*> Perceptual;
        std::vector<Operator*> Recognitive;
        std::vector<Operator*> Motor;
        std::vector<std::string> Perceptual_flow;
        std::vector<std::string> Recognitive_flow;
        std::vector<std::string> Motor_flow;
};

class NoviceMethod: public Method
{
 public:
    NoviceMethod(): Method(1) {
    }
};

class ExpertMethod: public Method
{
 public:
    ExpertMethod(): Method(0) {}
};

#endif /* Method_hpp */
