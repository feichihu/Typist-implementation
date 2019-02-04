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
    
    for (std::list<Operator>::iterator iterator = operators.begin(), end = operators.end(); iterator != end; ++iterator) {
        duration += iterator->duration();
    }
    
    return duration;
}
