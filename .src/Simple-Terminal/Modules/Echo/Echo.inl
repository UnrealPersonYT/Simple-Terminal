/// @file  Simple-Terminal/Modules/Echo/Echo.inl
/// @brief The Main Implementation File For The Echo Module
#pragma once
#include "../../Terminal/inc.h"

namespace SimpleTerminal{
namespace Modules{
namespace Echo{
    static const Terminal::Module mod(
        "echo",
        [](std::string_view args) -> const void*{
            std::printf("%.*s\n", static_cast<int>(args.size()), args.data());
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
}   // namespace Echo
}   // namespace Modules
}   // namespace SimpleTerminal