//
//  main.cpp
//  Assignment1
//
//  Created by nbanovic.
//  Copyright © 2019 Nikola Banovic. All rights reserved.
//

#include <iostream>
#include "Method.hpp"

Dict dict;

int main(int argc, const char *argv[])
{

    std::string phrase0 = std::string("The quick brown fox jumps over the lazy dog");
    std::string phrase;
    std::cout << "Please enter a phrase for typing simulation(enter 0 for default phrase 'The quick...'):" << std::endl;
    bool pass = 0;
    while (!pass)
    {
        getline(std::cin, phrase);
        if (phrase == "0")
        {
            phrase = phrase0;
            break;
        }
        pass = ifValid(phrase);
    }
    std::cout << "------Phrase accepted, start simulation------" << std::endl;

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

bool ifValid(std::string input)
{
    for (int i = 0; i < (int)input.length(); i++)
    {
        if (input[i] != ' ' && !isalpha(input[i]))
        {
            std::cout << "!!!!!warning!!!!!!" << std::endl;
            std::cout << "This program only simulates alphabetic input string, please remove any other characters and try again." << std::endl;
            return false;
        }
    }
    return true;
}