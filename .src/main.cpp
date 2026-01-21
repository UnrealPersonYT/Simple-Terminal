#include "Simple-Terminal/inc.h"
#include <iostream>

using namespace SimpleTerminal;

i32 main(){
    while(true){
        std::string inputLine;
        std::cout << "Simple-Terminal: ";
        std::getline(std::cin, inputLine); // Read entire line into std::string
        const std::string_view inputView(inputLine); // Create a view over the string
        const Terminal::Error err = Terminal::digest(inputView);
        if(err != Terminal::Error::noErr)
            Terminal::handler(err);
    }
    return 0;
}