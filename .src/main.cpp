#include "Simple-Terminal/inc.h"
#include <iostream>

using namespace SimpleTerminal;

i32 main(){
    // Print terminal version on startup
    Terminal::digest("version");
    while(true){
        std::string inputLine;
        std::cout << "Simple-Terminal: ";
        std::getline(std::cin, inputLine);
        const std::string_view inputView(inputLine);
        Terminal::digest(inputView);
    }
    return 0;
}