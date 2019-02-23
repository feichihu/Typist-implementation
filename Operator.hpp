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
        Operator(std::string word, double duration, std::string t) {
            chunck = word;
            Real_duration = duration;
            type = t;
        }
        virtual ~Operator(){ }
        virtual double duration(){ 
            //std::cout << type << " operator " << "handles --" << chunck << "-- at " << time_elapsed() << std::endl;
            return Real_duration;
        }
        virtual void push(Operator* op){
            next.push_back(op);
        }
        void set_backtrace(Operator* op){
            backtrace = op;
        }
        Operator* back(){
            return backtrace;
        }
        double update(){
            if(visited) return highest_duration + Real_duration;
            else{
                double max = 0.0;
                for(auto i:next){
                    double t;
                    t = i->update();
                    if(t>max){
                        backtrace = i;
                        max = t;
                    }
                }
                visited = true;
                return max + Real_duration; 
            }
        }
        double time_elapsed(){
            return highest_duration;
        }
        virtual std::string content(){
            return type+":"+chunck;
        }
        bool if_motor(){
            return type=="motor";
        }

    protected:
        std::vector<Operator*> next;
        Operator* backtrace;
        bool visited = false;
        double highest_duration=0.0;
        double Real_duration = 340.0;
        std::string chunck;
        std::string type="perceptual";
};


#endif /* Operator_hpp */
