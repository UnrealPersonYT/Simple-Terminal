#include "Simple-Terminal/inc.h"
#include <iostream>

using namespace SimpleTerminal;

int main(){
    // Print terminal version on startup
    Terminal::digest("version");
    // ----------- Main terminal loop -----------
    while(true){
        std::string inputLine;
        std::getline(std::cin, inputLine);
        Terminal::digest(inputLine);
    }
    return 0;
}