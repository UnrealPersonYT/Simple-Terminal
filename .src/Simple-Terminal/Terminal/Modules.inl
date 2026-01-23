/// @file  Simple-Terminal/Terminal/Modules.inl
/// @brief The main implementation file for The Terminal class's builtin modules
#pragma once
#include "Terminal.h"

namespace SimpleTerminal{
    const Terminal::Module Terminal::helpMod(
        "help",
        "Prints All Modules And Their Brief Descriptions",
        [](std::string_view args){
            std::printf("Loaded Modules:\n");
            for(const auto& [name, mod] : Terminal::cmdLets_)
                std::printf("  %-15s -%s\n", name.c_str(), mod->brief.c_str());
        }
    );
    const Terminal::Module Terminal::listMod(
        "lev",
        "List All Current Environment Variables",
        [](std::string_view args){
            std::printf("Environment Variables:\n");
            for(const auto& [name, replacement] : Terminal::envVars_)
                std::printf("  %-15s -%s\n", name.c_str(), replacement.c_str());
        }
    );
    const Terminal::Module Terminal::setMod(
        "sev",
        "Links A Word To An Environment Variable Refrence",
        [](std::string_view args){
            if(args.empty())
                return;
            // Find first word
            u64 pos = args.find(' ');
            if(pos == std::string_view::npos)
                return; // no reference provided
            std::string name(args.substr(0, pos));
            // Skip spaces
            u64 valueStart = args.find_first_not_of(' ', pos);
            if(valueStart == std::string_view::npos)
                return;
            std::string reference(args.substr(valueStart));
            envVars_[name] = reference;
        }
    );
    const Terminal::Module Terminal::remMod(
        "rev",
        "Remove A Environment Variable",
        [](std::string_view args){
            if(args.empty())
                return;
            // Cant remove path variable
            static const std::string protectedVar = "path";
            if(args == protectedVar){
                std::printf("Tried To Remove Protected \"path\" Environment Variable:\nError Access Denied!\n");
                return;
            }
            const std::string stringified(args);
            envVars_.erase(stringified);
        }
    );
}   // namespace SimpleTerminal