/// @file  Simple-Terminal/Terminal/Cleanup.inl
/// @brief The main implementation file for The Terminal's automatic cleanup
#pragma once
#include "Terminal.h"
#include <csignal>

namespace SimpleTerminal{
    void Terminal::initializeCleanup(){
        std::atexit([](){
            std::printf("\033[0m"); // reset terminal color on exit cmdlet
        });
        std::signal(SIGTERM, [](int){
            std::printf("\033[0m"); // reset terminal color on force close
            std::fflush(stdout);    // ensure it prints immediately
            std::exit(143);         // SIGTERM exit code
        });
        std::signal(SIGINT, [](int){
            std::printf("\033[0m"); // reset terminal color on force close
            std::fflush(stdout);    // ensure it prints immediately
            std::exit(130);         // SIGINT exit code
        });
    }
namespace{
    // Auto initialize terminal cleanup (from calling exit)
    const bool cleanupInit = [](){
        SimpleTerminal::Terminal::initializeCleanup();
        return true;
    }();
}
}   // namespace SimpleTerminal