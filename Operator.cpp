//
//  Operator.cpp
//  Assignment1
//
//  Created by nbanovic.
//  Copyright © 2019 Nikola Banovic. All rights reserved.
//

#include "Operator.hpp"

Operator::Operator(std::string word, double duration, std::string t)
{
    chunck = word;
    Real_duration = duration;
    type = t;
}

Operator::~Operator() {
    next.clear();
    backtrace = nullptr;
    //std::cout<<this<<std::endl;
}

double Operator::duration()
{
    //std::cout << type << " operator " << "handles --" << chunck << "-- at " << time_elapsed() << std::endl;
    return Real_duration;
}

void Operator::push(Operator *op)
{
    next.push_back(op);
}

void Operator::set_backtrace(Operator *op)
{
    backtrace = op;
}

Operator *Operator::back()
{
    return backtrace;
}

void Operator::print()
{
    std::cout << type << " operator works on " << chunck << " with duration" << Real_duration << " Highest_duration" << highest_duration << std::endl;
}

double Operator::update()
{
    if (visited)
        return highest_duration + Real_duration;
    else
    {
        for (auto i : next)
        {
            double t;
            t = i->update();
            if (t > highest_duration)
            {
                backtrace = i;
                highest_duration = t;
            }
        }
        //print();
        visited = true;
        return highest_duration + Real_duration;
    }
}

double Operator::time_elapsed()
{
    return highest_duration;
}

std::string Operator::content()
{
    return type + ":" + chunck;
}

