#include "Simple-Terminal/inc.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <mach-o/dyld.h>
#include <limits.h>
#else // Linux/Unix
#include <unistd.h>
#include <limits.h>
#endif

using namespace SimpleTerminal;

int main(){
    // ----------- Get current exe path ----------- 
    std::string path;
#ifdef _WIN32
    char buffer[MAX_PATH];
    DWORD len = GetModuleFileNameA(NULL, buffer, MAX_PATH);
    if (len > 0)
        path = std::string(buffer, len);
#elif __APPLE__
    char buffer[PATH_MAX];
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) == 0)
        path = std::string(buffer);
#else // Linux
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        path = std::string(buffer);
    }
#endif
    // ----------- Set home variable in Terminal -----------
    Terminal::digest("sev home " + path);
    // Print terminal version on startup
    Terminal::digest("version");
    // ----------- Main terminal loop -----------
    while(true){
        std::string inputLine;
        std::cout << "Simple-Terminal: ";
        std::getline(std::cin, inputLine);
        Terminal::digest(inputLine);
    }
    return 0;
}