/// @file  Simple-Terminal/Terminal/Terminal.inl
/// @brief The main implementation file for The Terminal class
#pragma once
#include "Terminal.h"
#include <cstdlib>

namespace SimpleTerminal{
    bool Terminal::implement(const Module* const mod){
        if(!mod)
            return true;
        auto it = hashTable_.find(mod->command);
        if(it != hashTable_.end())
            return false;
        hashTable_.emplace(mod->command, mod);
        return true;
    }
    void Terminal::digest(std::string_view input){
        // Find where command starts via skipping leading zeros
        u64 leading = 0;
        while(input[leading] == ' ')++leading;
        // Find total command size
        u64 size = 0;
        while(leading + size < input.size() && input[leading + size] != ' ')++size;
        // Construct command
        const std::string cmd(input.substr(leading, size));
        // Test if cmd exists in modules
        auto it = hashTable_.find(cmd);
        if(it == hashTable_.end()){
            std::printf("Simple-Terminal[Error]: \"%s\" Cmdlet Not Found\n", cmd.data());
            return;
        }
        const Module* mod = it->second;
        // Get arguments after command
        std::string_view args = input.substr(leading + size);
        // Skip leading spaces in arguments
        while(!args.empty() && args.front() == ' ')args.remove_prefix(1);
        // Digest
        mod->digest(args);
    }
    const Terminal::Module Terminal::helpMod(
        "help",
        "Prints All Modules And Their Brief Descriptions",
        [](std::string_view args){
            std::printf("Loaded modules:\n");
            for(const auto& [name, mod] : Terminal::hashTable_)
                std::printf("  %-15s -%s\n", name.c_str(), mod->brief.c_str());
        }
    );
    const Terminal::Module Terminal::exitMod(
        "exit",
        "Exits The Application",
        [](std::string_view args){
            std::exit(0);
        }
    );
}   // namespace SimpleTerminal