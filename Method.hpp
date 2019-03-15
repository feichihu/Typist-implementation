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
#include <sstream>
#include <cctype>
#include "Operator.hpp"
#include "FittsLaw.hpp"
#include "Emma.hpp"
#include "keyLayout.hpp"

#define Reconitive_flow_size 54
#define Motor_flow_size 45
#define Perceptual_Duration 340
#define Cognitive_Duration 50
#define Motor_Duration 50
/*  ASSUMPTION: This typist follows the priciples of Assumption 1-7 in the TYPIST paper, with the following modifications:
We use a 246mm * 185mm (12mm) with resolution 1024 * 768 tablet for transcribe task.
This time any typist need to do visual searches on keyboard for each single key.
Therefore, the typing time is significantly longer than previous settings in Assigment1.
Also, since its a tablet, moving fingers takes longer time than on phones. 
  In Assumption 2b, the typist uses both hands, with one finger for each hand in typing
  In Assumption 3, the perceptual processor stays 3 chunks ahead
  In Assumption 4, the typist use a word as a chunk and there is no restricted view issue
  In Assumption 5, 
  In Assumption 6, 
    Perceptual duration is 340ms
    Cognitive duration for fetching a word is 50 ms
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
    
    public:
        /**
         * Method to parse a phrase into a method. Subclasses should implement their specific strategy and store it as a list of operators.
         */
        Method(bool ifNovice, keyLayout &k);//init method
        void process(std::string phrase); // encode given phrase into schedule chart
        void clear();
        void updateLayout(keyLayout &k);
        long benchmarkSingle(singleCorpusEntry p);
        void initDict();//initialize (from, to) dictionary for distance and other data
        bool ifValid(std::string input);//detect if input is valid string
        void find_path();// find path from schedule chart
        bool if_samehand(std::string a, std::string b); //determine if a and b are typed by the same hand
        long benchmark(); //return the gross weight of corpus under current layout
        /**
         * Method to compute duration (in seconds) that would take to execute the method.
         */
        int duration();
        std::string convert2lower(std::string str);//convert string to lowercase
    protected:
        //Pointers for each operator
        std::vector<Operator*> operators;
        std::vector<Operator*> Perceptual{};
        std::vector<Operator*> Cognitive{};
        std::vector<Operator*> Motor{};

        //Characters and words in each operator
        std::vector<std::string> Perceptual_flow{};
        std::vector<std::string> Cognitive_flow{};
        std::vector<std::string> Motor_flow{};

        //location of whole words in cognitive operators
        std::vector<int> words_location{};

        //distance and IDs for each key pair
        Dict dict{};

        //instance of Emma and Fitts
        Emma cogs;
        Fitts motors;

        //layout
        keyLayout key;
        Corpus corpus;
};

std::istream &operator>>(std::istream &str, CSVRow &data);

class NoviceMethod: public Method
{
 public:
    NoviceMethod(keyLayout& k): Method(1, k) {
    }
};

class ExpertMethod: public Method
{
 public:
    ExpertMethod(keyLayout& k): Method(0, k) {}
};

#endif /* Method_hpp */
