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
        //std::cout<<duration<<std::endl;
    }
    duration = duration/1000.0;//convert ms to s
    return duration;
}

bool Method::ifValid(std::string input){
    for(int i = 0; i<input.length(); i++){
        if(input[i]!=' ' && !isalpha(input[i])) {
            cout<<"!!!!!warning!!!!!!"<<std::endl;
            cout<<"This program only simulates alphabetic input string, please remove any other characters and try again."<<std::endl;
            return false;
        }
        else return true;
    }
}

bool Method::if_samehand(std::string a, std::string b){
    std::set<std::string> left={"q","w","e","r","t","a","s","d","f","g","z","x","c","v","b"};
    std::set<std::string> right={"y","h","n","u","j","m","i","k","o","p","l",",",".",";",":"};
    int A{},B{};
    A = left.find(a)==left.end()? 0:-1;
    if(A==0)
        A = right.find(a)==right.end()? 0:1;
    //A -1:left 0:can use both hand 1 :right
    B = left.find(b)==left.end()? 0:-1;
    if(B==0)
        B = right.find(b)==right.end()? 0:1;
    if(A==0 || B==0) return false;// keys that can be pressed by both hands
    else if (A==B) return true;// keys in same hand
    else return false;// keys in different hands
}


    Method::Method(double motor_duration){//set up the schedule chart
        real_motor_duration = motor_duration;
        for(std::string i : Motor_flow){
            Recognitive.push_back(new Operator(i,Recognitive_Duration, "recognitive"));
        }
        for(std::string i : Motor_flow){
            Motor.push_back(new Operator(i, real_motor_duration, "motor"));
        }
        //std::cout<<"finish Rec and Motor intialization"<<std::endl;
        //std::cout<<"their sizes are:"<<Recognitive.size()<<" "<<Motor.size()<<std::endl;


        //adding dependency, a this step, cognitive flow is exactly the same as motor flow(withour the LTM process)
        //1. cognitive to cognitive

        //std::cout<<"Adding cog to cog dependency"<<std::endl;
        for(int i = 0; i<Motor_flow_size-1;i++){
            Recognitive[i]->set_next_cog(Recognitive[i+1]);
        }
        //2. cognitive to motor
        //std::cout<<"Adding cog to motor dependency"<<std::endl;
        for(int i = 0; i<Motor_flow_size;i++){
            Recognitive[i]->set_next_motor(Motor[i]);
        }
        //3. motor to cognitive
        //std::cout<<"Adding motor to cog dependency"<<std::endl;
        for(int i = 0; i<Motor_flow_size-1;i++){
            if(if_samehand(Motor_flow[i],Motor_flow[i+1])){
                Motor[i]->set_next_cog(Recognitive[i+1]);
            }
        }
        //4. motor to motor
        //std::cout<<"Adding motor to motor dependency"<<std::endl;
        for(int i = 0; i<Motor_flow_size-1;i++){
            Motor[i]->set_next_motor(Motor[i+1]);
        }

        //Adding LTM process into the cognitive flow ("One_")
        //this part is hardcoded
        std::vector<int> LTM_places{0,6,13,20,25,32,38,43,49};
        for(int i=0; i<(int)LTM_places.size(); i++){
            //std::cout<<"adding LTM dependency at"<<Perceptual_flow[i]<<std::endl;
            Recognitive.insert(Recognitive.begin()+LTM_places[i], new Operator(Perceptual_flow[i], Recognitive_Duration, "recognitive"));
            if(i==0){
                Recognitive[0]->set_next_cog(Recognitive[1]);
            }
            else{
                int p = LTM_places[i];
                Recognitive[p]->set_next_cog(Recognitive[p+1]);
                Recognitive[p-1]->set_next_cog(Recognitive[p]);
            }
        }
        //std::cout<<"finish LTM intialization"<<std::endl;
        //std::cout<<"their sizes are:"<<Recognitive.size()<<" "<<Motor.size()<<std::endl;
    }


void  Method::find_path(){
        //iterate through the first cognitive task
        //std::cout<<"starting finding path "<<Recognitive.size()<<std::endl;
        for(Operator* i: Recognitive){
            i->update();
        }
        Operator* it = Motor.back();
        while(it->back()!=nullptr){
            operators.push_front(it);
            it = it->back();
        }
        Operator* first = new Operator("Once_", Perceptual_Duration, "perceptual");
        operators.push_front(first);
    }

