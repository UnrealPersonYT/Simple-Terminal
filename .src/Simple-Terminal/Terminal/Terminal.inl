/// @file  Simple-Terminal/Terminal/Terminal.inl
/// @brief The main implementation file for The Terminal class
#pragma once
#include "Terminal.h"
#include <cstdlib>

namespace SimpleTerminal{
    enum Terminal::Error : u8{
        noErr = 0,
        invCmd = 1,
        ovlMod = 2,
        nullPtr = 3
    };
    Terminal::Error Terminal::implement(const Module* const mod){
        if(!mod)
            return nullPtr;
        auto it = hashTable_.find(mod->name);
        if(it != hashTable_.end())
            return ovlMod;
        hashTable_.emplace(mod->name, mod);
        return noErr;
    }
    Terminal::Error Terminal::digest(std::string_view input){
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
        if(it == hashTable_.end()) // Not found
            return invCmd;
        const Module* mod = it->second;
        // Get arguments after command
        std::string_view args = input.substr(leading + size);
        // Skip leading spaces in arguments
        while(!args.empty() && args.front() == ' ')args.remove_prefix(1);
        // Get error block
        const void* errBlock = mod->digest(args);
        if(errBlock) // Use handler if block is given
            mod->handler(errBlock);
        return noErr; // No terminal error occurred
    }
    void Terminal::handler(const Error err){
        std::printf("Err(%u)\n%s", err, errMessages[err]);
    }
    const Terminal::Module Terminal::helpMod(
        "help",
        [](std::string_view args) -> const void*{
            std::printf("Loaded modules:\n");
            for(const auto& [name, mod] : Terminal::hashTable_)
                std::printf("  %s\n", name.c_str());
            return nullptr; // No error
        },
        [](const void* err){ // Not possible to reach
            std::printf("Help module error\n");
        }
    );
    const Terminal::Module Terminal::exitMod(
        "exit",
        [](std::string_view args) -> const void*{
            std::exit(0);
            return nullptr; // No error
        },
        [](const void* err){ // Not possible to reach
            std::printf("Exit module error\n");
        }
    );
}   // namespace SimpleTerminal