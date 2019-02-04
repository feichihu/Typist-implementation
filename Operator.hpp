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
        virtual double duration();
        void set_next(Operator* op){
            next.push_back(op);
        }
        void set_previous(Operator* op){
            previous.push_back(op);
        }
        void set_backtrace(Operator* op){
            backtrace = op;
        }
        std::vector<Operator*> next_list(){
            return next;
        }
        std::vector<Operator*> previous_list(){
            return previous;
        }
        Operator* back(){
            return backtrace;
        }
        double time_elapsed(){
            return highest_duration;
        }
        bool if_motor(){
            return false;
        }
        void update(int t=1){//update t times through the linked relation
            if(t<0) return;
            for(int i=0; i<next.size(); i++){
                next[i]->get_update(this, highest_duration+duration());
                if(next[i]->if_motor()){//only update motor operators' next
                    next[i]->update(t-1);
                }
            }
        }
        bool get_update(Operator* op, double new_duration){
            if(new_duration>highest_duration){
                backtrace = op;
                highest_duration = new_duration;
                return true;
            }
            return false;
        }

    private:
        std::vector<Operator*> next;
        std::vector<Operator*> previous;
        Operator* backtrace = nullptr;
        double highest_duration=0.0;
};


class PerceptualOperator: public Operator
{
    public:
        double duration(){
            std::cout << type << " operator " << "handles --" << chunck << "-- at " << time_elapsed() << std::endl;
            return Real_duration;
        }
        PerceptualOperator(std::string word, double duration=340.0){
            chunck = word;
            Real_duration = duration;
        }
    private:
        double Real_duration = 340.0;
        std::string chunck;
        std::string type="perceptual";
};



class RecognitiveOperator: public Operator
{
    public:
        double duration(){
            std::cout << type << " operator " << "handles --" << chunck << "-- at " << time_elapsed() << std::endl;
            return Real_duration;
        }
        RecognitiveOperator(std::string word, double duration=50.0){
            chunck = word;
            Real_duration = duration;
        }
    private:
        double Real_duration = 50.0;
        std::string chunck;
        std::string type="recognitive";
};


class MotorOperator: public Operator
{
    public:
        double duration(){
            std::cout << type << " operator " << "handles --" << chunck << "-- at " << time_elapsed() << std::endl;
            return Real_duration;
        }
        MotorOperator(std::string word, double duration){
            chunck = word;
            Real_duration = duration;
        }
        bool if_motor(){
            return true;
        }
    private:
        double Real_duration = 0.0;
        std::string chunck;
        std::string type="motor";
};

#endif /* Operator_hpp */
