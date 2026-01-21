/// @file  Simple-Terminal/Modules/Echo/Echo.inl
/// @brief The Main Implementation File For The Echo Module
#pragma once
#include "../../Terminal/inc.h"

namespace SimpleTerminal{
namespace Modules{
namespace Echo{
    static const Terminal::Module mod(
        "echo",
        "Prints Given Arguments To Terminal",
        [](std::string_view args){
            std::printf("%.*s\n", static_cast<int>(args.size()), args.data());
        }
    );
    namespace{
        const bool imp = [](){
            Terminal::implement(&mod);
            return true;
        }();
    }
}   // namespace Echo
}   // namespace Modules
}   // namespace SimpleTerminal