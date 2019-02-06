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
        virtual void set_next_motor(Operator* op){
            Next_motor = op;
        }
        virtual void set_next_cog(Operator* op){
            Next_cog = op;
        }
        void set_backtrace(Operator* op){
            backtrace = op;
        }
        Operator* back(){
            return backtrace;
        }
        double time_elapsed(){
            return highest_duration;
        }
        virtual void update(int t=1){//update t times through the linked relation
            if(t<0) return;
                if(Next_cog) Next_cog->get_update(this, highest_duration+duration());
                if(Next_motor){
                    Next_motor->get_update(this, highest_duration+duration());
                    Next_motor->update(t-1);
                }
            }
        virtual bool get_update(Operator* op, double new_duration){
            if(new_duration>highest_duration){
                backtrace = op;
                highest_duration = new_duration;
                return true;
            }
            return false;
        }
        virtual std::string content(){
            return type+":"+chunck;
        }
        bool if_motor(){
            return type=="motor";
        }

    protected:
        Operator* Next_cog = nullptr;
        Operator* Next_motor = nullptr;
        Operator* backtrace = nullptr;
        double highest_duration=0.0;
        double Real_duration = 340.0;
        std::string chunck;
        std::string type="perceptual";
};


#endif /* Operator_hpp */
