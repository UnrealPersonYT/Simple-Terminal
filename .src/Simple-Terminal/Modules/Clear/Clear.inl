/// @file  Simple-Terminal/Modules/Clear/Clear.inl
/// @brief The Main Implementation File For The Clear Module
#pragma once
#include "../../Terminal/inc.h"

namespace SimpleTerminal{
namespace Modules{
namespace Clear{
    static const Terminal::Module mod(
        "clear",
        [](std::string_view args) -> const void*{
            std::printf("\033[2J\033[H");
            return nullptr; // No error
        },
        [](const void* err){ // Not possible to reach
            std::printf("Echo module error\n");
        }
    );
    namespace{
        const bool imp = [](){
            Terminal::implement(&mod);
            return true;
        }();
    }
}   // namespace Clear
}   // namespace Modules
}   // namespace SimpleTerminal