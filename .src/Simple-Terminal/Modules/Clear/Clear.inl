/// @file  Simple-Terminal/Modules/Clear/Clear.inl
/// @brief The Main Implementation File For The Clear Module
#pragma once
#include "../../Terminal/inc.h"

namespace SimpleTerminal{
namespace Modules{
namespace Clear{
namespace{
    #ifdef _WIN32
        inline constexpr std::string_view clearStr = "cls";
    #else
        inline constexpr std::string_view clearStr = "clear";
    #endif
}
    static const Terminal::Module mod(
        "clear",
        [](std::string_view args) -> const void*{
            std::system(clearStr.data());
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