/// @file  Simple-Terminal/Terminal/Terminal.inl
/// @brief The main implementation file for The Terminal class
#pragma once
#include "Terminal.h"
#include <cstdlib>

namespace SimpleTerminal{
    std::string Terminal::parseVars(std::string_view input){
        std::string parsed;
        u64 index = 0;
        while(index < input.size()){
            u64 start = index;
            // Copy text until '$'
            while(index < input.size() && input[index] != '$')
                ++index;
            parsed += input.substr(start, index - start);
            // End reached
            if(index >= input.size())
                break;
            // Check for ${VAR}
            if(index + 1 < input.size() && input[index + 1] == '{'){
                u64 nameStart = index + 2; // after ${
                u64 nameEnd = input.find('}', nameStart);
                if(nameEnd == std::string_view::npos){
                    // malformed, copy literally
                    parsed += input.substr(index);
                    break;
                }
                std::string variable(input.substr(nameStart, nameEnd - nameStart));
                auto it = envVars_.find(variable);
                if(it != envVars_.end())
                    parsed += it->second;
                else
                    parsed += input.substr(index, nameEnd - index + 1);
                index = nameEnd + 1;
            }else{
                // Just a '$'
                parsed += '$';
                ++index;
            }
        }
        return parsed;
    }
    bool Terminal::implement(const Module* const mod){
        if(!mod)
            return true;
        auto it = cmdLets_.find(mod->command);
        if(it != cmdLets_.end())
            return false;
        cmdLets_.emplace(mod->command, mod);
        return true;
    }
    void Terminal::digest(const std::string_view input){
        // Parse the string for environment variables
        const std::string parsed = parseVars(input);
        std::string_view parsedView(parsed);
        // Skip leading spaces
        size_t leading = 0;
        while(leading < parsedView.size() && parsedView[leading] == ' ')
            ++leading;
        // Find first space (end of command)
        size_t pos = parsedView.find(' ', leading);
        // Command length
        size_t cmdLength = (pos == std::string_view::npos) ? parsedView.size() - leading : pos - leading;
        // Construct command
        const std::string cmd(parsedView.substr(leading, cmdLength));
        // Test if cmd exists in modules
        auto it = cmdLets_.find(cmd);
        if(it == cmdLets_.end()){
            std::printf("Simple-Terminal[Error]: \"%s\" Cmdlet Not Found\n", cmd.c_str());
            return;
        }
        const Module* mod = it->second;
        // Arguments substring
        std::string_view args;
        if(pos == std::string_view::npos)
            args = {}; // no arguments
        else
            args = parsedView.substr(pos + 1); // skip space
        // Skip leading spaces in arguments
        while(!args.empty() && args.front() == ' ')
            args.remove_prefix(1);
        // Digest
        mod->digest(args);
    }
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
}   // namespace SimpleTerminal