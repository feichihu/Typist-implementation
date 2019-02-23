//
//  Method.cpp
//  Assignment1
//
//  Created by nbanovic.
//  Copyright © 2019 Nikola Banovic. All rights reserved.
//

#include "Method.hpp"


std::istream &operator>>(std::istream &str, CSVRow &data)
{
    data.readNextRow(str);
    return str;
}

void Method::process(std::string phrase){
    //transform into lower case
    //separate by space
    //  init perceputal operator
    //  adding p2p denpendency
    //adding character by character vector
    //  init motor and cog operators
    //  adding m2m, c2c dependency
    /*
    dependency order:
    p2p
    m2m
    c2m
    m2c
    adding words to cog
    c2c
    p2c
    c2p
    */
    phrase = convert2lower(phrase);
    std::stringstream phraseStream(phrase);
    std::string temp;
    while(getline(phraseStream,temp, ' ')){
        Perceptual_flow.push_back(temp);
    }
    for(char i: phrase){
        std::string t(1, i);
        Cognitive_flow.push_back(t);
        Motor_flow.push_back(t);
    }
    for(auto i:Perceptual_flow){
        Perceptual.push_back(new Operator(i, Perceptual_Duration, "Perceptual" ));
    }
    //adding p2p dependency
    for(int i = 0; i<(int)Perceptual.size()-1; i++){
        Perceptual[i]->push(Perceptual[i+1]);
    }
    //init motor and cog
    Cognitive.push_back(new Operator(Cognitive_flow[0], Cognitive_Duration, "Cognitive"));
    Motor.push_back(new Operator(Motor_flow[0], Motor_Duration, "Motor"));
    for(int i=1; i<(int)Cognitive_flow.size(); i++){
        double motor_time = motors.Time(Cognitive_flow[i-1],Cognitive_flow[i]);
        double cog_time = cogs.Time(Cognitive_flow[i-1],Cognitive_flow[i]);
        Cognitive.push_back(new Operator(Cognitive_flow[i], cog_time, "Cognitive"));
        Motor.push_back(new Operator(Motor_flow[i], motor_time, "Motor"));
        //adding m2m dependency
        Motor[i-1]->push(Motor[i]);
    }
    for(int i=0; i<(int)Cognitive_flow.size(); i++){
        //adding c2m depency
        Cognitive[i]->push(Motor[i]);
    }
    //adding m2c depency
    for(int i=0; i<(int)Cognitive_flow.size()-1; i++){
        if(if_samehand(Motor_flow[i], Motor_flow[i+1])){
            Motor[i]->push(Cognitive[i+1]);
        }
    }

    //adding words to cog
    int count{};
    for(int i = 0; i<(int)Perceptual_flow.size(); i++){
        words_location.push_back(count);
        count++;
        count += Perceptual_flow[i].length();
    }
    //adding cog operators for words
    for(int i = 0; i<(int)Perceptual_flow.size(); i++){
        Operator* temp = new Operator(Perceptual_flow[i], Cognitive_Duration, "Cognitive");
        Cognitive.insert(Cognitive.begin()+words_location[i], temp);
    }

    //adding c2c dependency
    for(int i = 0; i<(int)Cognitive.size()-1; i++){
        Cognitive[i]->push(Cognitive[i+1]);
    }

    //adding p2c dependency
    for(int i = 0; i<(int)Perceptual_flow.size(); i++){
        Perceptual[i]->push(Cognitive[words_location[i]]);
    }
    //adding c2p dependency
    for(int i = 1; i+2<(int)Perceptual_flow.size(); i++){
        Cognitive[words_location[i]-1]->push(Perceptual[i+2]);
    }
}

void Method::initDict() {
    std::ifstream file("Keyboard.csv");
    std::string line;
    CSVRow row;
    std::getline(file, line);
    double min = 100;
    double max = 0;
    while (file >> row)
    {
        dict.insert(row);
        if (row.ID < min && row.ID != 0)
            min = row.ID;
        if (row.ID > max)
            max = row.ID;
    }
    //std::cout << "the ID range is (" << min << ", " << max << ")";
}

double Method::duration() {
    find_path();
    double duration = 0.0;
    for (std::list<Operator*>::iterator iterator = operators.begin(), end = operators.end(); iterator != end; ++iterator) {
        duration += (*iterator)->duration();
        std::cout<<"duration:"<<duration<<std::endl;
    }
    duration = duration/1000.0;//convert ms to s
    return duration;
}

bool Method::ifValid(std::string input){
    for(int i = 0; i<(int)input.length(); i++){
        if(input[i]!=' ' && !isalpha(input[i])) {
            std::cout<<"!!!!!warning!!!!!!"<<std::endl;
            std::cout<<"This program only simulates alphabetic input string, please remove any other characters and try again."<<std::endl;
            return false;
        }
    }
    return true;
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



Method::Method(bool ifNovice){
    initDict();
    cogs = Emma(dict, ifNovice);
    motors = Fitts(dict);
}


void  Method::find_path(){
      // 
      Perceptual[0]->update();
      Operator* p = Perceptual[0];
      while(p){
          operators.push_back(p);
          p = p->back();
      }
    }

