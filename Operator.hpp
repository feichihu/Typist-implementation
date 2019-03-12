//
//  Operator.hpp
//  Assignment1
//
//  Created by nbanovic.
//  Copyright © 2019 Nikola Banovic. All rights reserved.
//

#ifndef Operator_hpp
#define Operator_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

/**
 * Interface for an operator in a schedule chart.
 * All your operators (perceptual, cognitive, and motor)
 * should implement this interface.
 */
class Operator
{
    public:
        Operator(std::string word, double duration, std::string t);//init, where duration is hardcoded or given by Emma/Fitts
        virtual ~Operator();
        virtual double duration();
        virtual void push(Operator* op);//adding dependency
        void set_backtrace(Operator* op);//backtrace in the algorithm
        Operator* back();
        void print();//print essential information
        double update();//updata data related to critical path
        double time_elapsed();
        virtual std::string content();//give basic information of the operator

    protected:
        std::vector<Operator*> next{};//dependency
        Operator* backtrace{};//previous operator in the critical path
        bool visited = false;//if critical path to this operator has been computed
        double highest_duration=0.0;
        double Real_duration = 340.0;
        std::string chunck;
        std::string type="perceptual";
};


#endif /* Operator_hpp */
