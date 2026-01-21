/// @file  Simple-Terminal/Modules/Exit/Exit.inl
/// @brief The Main Implementation File For The Exit Module
#pragma once
#include "../../Terminal/inc.h"

namespace SimpleTerminal{
namespace Modules{
namespace Exit{
    static const Terminal::Module mod(
        "exit",
        "Exits The Application",
        [](std::string_view args){
            std::exit(0);
        }
    );
    namespace{
        const bool imp = [](){
            Terminal::implement(&mod);
            return true;
        }();
    }
}   // namespace Exit
}   // namespace Modules
}   // namespace SimpleTerminal