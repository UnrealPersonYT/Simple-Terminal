/// @file  Simple-Terminal/Modules/System/System.inl
/// @brief The Main Implementation File For The System Module
#pragma once
#include "../../Terminal/inc.h"

namespace SimpleTerminal{
namespace Modules{
namespace System{
    static const Terminal::Module mod(
        "sys",
        "Writes Arguments To OS's Cmd/Shell",
        [](std::string_view args){
            std::system(args.data());
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