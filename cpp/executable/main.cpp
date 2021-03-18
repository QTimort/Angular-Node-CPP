//
// Created by Timothy Diguiet on 18/03/2021.
//

#include <Windows.h>
#include <iostream>

int main() {
    // Load the specified library. Use AfxLoadLibrary if the library uses threads
    HINSTANCE LoadME = LoadLibrary(R"(library.dll)");

    if (LoadME != nullptr)
        std::cout << "LoadMe library loaded!" << std::endl;
    else
        std::cout << "LoadMe library failed to load!" << std::endl;

    // declare the function signature to load and call
    typedef void (*EntryPointfuncPtr)(int argc, const char * argv );
    // load the function from the library by it's name
    auto LibMainEntryPoint = (EntryPointfuncPtr)GetProcAddress(LoadME,"EntryPoint");
    if (LibMainEntryPoint != nullptr) {
        std::cout << "Found function!" << std::endl;
        LibMainEntryPoint(0, {});
    } else {
        std::cout << "Function not found!" << std::endl;
    }
    FreeLibrary(LoadME);
}

