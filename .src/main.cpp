#include "Simple-Terminal/inc.h"
#include <iostream>

using namespace SimpleTerminal;

int main(){
    // Print terminal version on startup
    Terminal::digest("version");
    // ----------- Main terminal loop -----------
    while(true){
        std::string inputLine;
        if(std::getline(std::cin, inputLine)) // Detect if it was actual user input
            Terminal::digest(inputLine);
    }
    return 0;
}