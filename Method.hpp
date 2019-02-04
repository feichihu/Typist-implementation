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
#include "Operator.hpp"

class Method
{
    private:
        std::list<Operator> operators;
    
    public:
        /**
         * Method to parse a phrase into a method. Subclasses should implement their specific strategy and store it as a list of operators.
         */
        virtual void process(std::string phrase);
    
        /**
         * Method to compute duration (in seconds) that would take to execute the method.
         */
        double duration();
};

class NoviceMethod: public Method
{
    
};

class IntermediateMethod: public Method
{
    
};

class ExpertMethod: public Method
{
    
};

#endif /* Method_hpp */
