//
//  Method.cpp
//  Assignment1
//
//  Created by nbanovic.
//  Copyright © 2019 Nikola Banovic. All rights reserved.
//

#include "Method.hpp"

double Method::duration() {
    double duration = 0.0;
    
    for (std::list<Operator*>::iterator iterator = operators.begin(), end = operators.end(); iterator != end; ++iterator) {
        duration += (*iterator)->duration();
    }
    
    return duration;
}

bool Method::if_samehand(std::string a, std::string b){
    std::set<std::string> left={"q","w","e","r","t","a","s","d","f","g","z","x","c","v","b"};
    std::set<std::string> right={"y","h","n","u","j","m","i","k","o","p","l",",",".",";",":"};
    int A{},B{};
    A = left.find(a)==left.end()? 0:-1;
    A = right.find(a)==right.end()? 0:1;
    B = left.find(b)==left.end()? 0:-1;
    B = right.find(b)==right.end()? 0:1;
    if(A==0 || B==0) return false;// keys that can be pressed by both hands
    else if (A==B) return true;// keys in same hand
    else return false;// keys in different hands
}


    Method::Method(double motor_duration){//set up the schedule chart
        real_motor_duration = motor_duration;
        for(std::string i : Motor_flow){
            Recognitive.push_back(new RecognitiveOperator(i));
        }
        for(std::string i : Motor_flow){
            Recognitive.push_back(new MotorOperator(i, real_motor_duration));
        }

        //adding dependency, a this step, cognitive flow is exactly the same as motor flow(withour the LTM process)
        //1. cognitive to cognitive
        for(int i = 0; i<Motor_flow_size-1;i++){
            Recognitive[i]->set_next(Recognitive[i+1]);
            Recognitive[i+1]->set_previous(Recognitive[i]);
        }
        //2. cognitive to motor
        for(int i = 0; i<Motor_flow_size;i++){
            Recognitive[i]->set_next(Motor[i]);
            Motor[i]->set_previous(Recognitive[i]);
        }
        //3. motor to cognitive
        for(int i = 0; i<Motor_flow_size;i++){
            if(if_samehand(Motor_flow[i],Motor_flow[i+1])){
                Motor[i]->set_next(Recognitive[i+1]);
                Recognitive[i+1]->set_previous(Motor[i]);
            }
        }
        //4. motor to motor
        for(int i = 0; i<Motor_flow_size-1;i++){
            Motor[i]->set_next(Motor[i+1]);
            Motor[i+1]->set_previous(Motor[i]);
        }

        //Adding LTM process into the cognitive flow ("One_")
        //this part is hardcoded
        std::vector<int> LTM_places{0,6,13,20,25,32,38,43,49};
        for(int i=0; i<(int)LTM_places.size(); i++){
            Recognitive.insert(Recognitive.begin()+LTM_places[i], new RecognitiveOperator(Perceptual_flow[i]));
            if(i==0){
                Recognitive[0]->set_next(Recognitive[1]);
                Recognitive[1]->set_previous(Recognitive[0]);
            }
            else{
                Recognitive[i]->set_next(Recognitive[i+1]);
                Recognitive[i+1]->set_previous(Recognitive[i]);
                Recognitive[i-1]->set_next(Recognitive[i]);
                Recognitive[i]->set_previous(Recognitive[i-1]);
            }
        }
        
    }


void  Method::find_path(){
        //iterate throught the first cognitive task
        for(auto i: Recognitive){
            i->update();
        }
        std::cout<<"-------totol time elapsed is"<<Motor.back()->time_elapsed()<<std::endl;
        Operator* it = Motor.back();
        while(it->back()!=nullptr){
            operators.push_front(it);
            it = it->back();
        }
    }

