//
// Created by Timothy Diguiet on 18/03/2021.
//

#include "library.h"
#include <iostream>

void EntryPoint(int argc, const char * argv) {
    #pragma EXPORT
    std::cout << "Hello, World!" << std::endl;
}