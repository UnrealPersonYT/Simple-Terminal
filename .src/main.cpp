#include "Simple-Terminal/inc.h"
#include <iostream>

using namespace SimpleTerminal;

int main(){
    // ----------- Set path variable in Terminal -----------
    Terminal::digest("sev path " + std::filesystem::current_path().string());
    // Print terminal version on startup
    Terminal::digest("version");
    // ----------- Main terminal loop -----------
    while(true){
        std::string inputLine;
        std::cout << "ST " << Terminal::getEnvVar("path") << ">";
        std::getline(std::cin, inputLine);
        Terminal::digest(inputLine);
    }
    return 0;
}