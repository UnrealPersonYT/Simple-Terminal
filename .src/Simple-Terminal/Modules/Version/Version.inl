/// @file  Simple-Terminal/Modules/Version/Version.inl
/// @brief The Main Implementation File For The Version Module
#pragma once
#include "../../Terminal/inc.h"

namespace SimpleTerminal{
namespace Modules{
namespace Version{
    inline static constexpr u32 Major = 1;
    inline static constexpr u32 Minor = 0;
    inline static constexpr u32 Patch = 0;
    static const Terminal::Module mod(
        "version",
        "Displays Current Terminal Version",
        [](std::string_view args){
            std::printf("Terminal Version: %u.%u.%u\n", Major, Minor, Patch);
        }
    );
    namespace{
        const bool imp = [](){
            Terminal::implement(&mod);
            return true;
        }();
    }
}   // namespace Version
}   // namespace Modules
}   // namespace SimpleTerminal