//
//  main.cpp
//  Assignment1
//
//  Created by nbanovic.
//  Copyright © 2019 Nikola Banovic. All rights reserved.
//

#include <iostream>
#include "Method.hpp"

int main(int argc, const char * argv[]) {
    
    std::string phrase = std::string("The quick brown fox jumps over the lazy dog.");
    
    // Instantiate a new Method instance, representing a schedule chart for a novice typist. Make sure you justify your schedule chart as comments in the NoviceMethod class.
    Method noviceMethod = NoviceMethod();
    noviceMethod.process(phrase);
    
    std::cout << "It would take a novice typist ";
    std::cout << noviceMethod.duration();
    std::cout << " seconds to type the phrase '";
    std::cout << phrase;
    std::cout << "'\n";
  
    // Instantiate a new Method instance, representing a schedule chart for an expert typist. Make sure you justify your schedule chart as comments in the ExpertMethod class.
    Method expertMethod = ExpertMethod();
    expertMethod.process(phrase);
    
    std::cout << "It would take an expert typist ";
    std::cout << expertMethod.duration();
    std::cout << " seconds to type the phrase '";
    std::cout << phrase;
    std::cout << "'\n";
    
    return 0;
}
