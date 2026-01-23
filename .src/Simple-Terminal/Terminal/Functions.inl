/// @file  Simple-Terminal/Terminal/Functions.inl
/// @brief The main implementation file for The Terminal class's functions
#pragma once
#include "Terminal.h"
#include <cstdlib>
#include <filesystem>

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
            std::printf("[Error]:\n\"%s\" Cmdlet Not Found\n", cmd.c_str());
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
    bool Terminal::implement(const Module* const mod){
        if(!mod)
            return true;
        auto it = cmdLets_.find(mod->command);
        if(it != cmdLets_.end())
            return false;
        cmdLets_.emplace(mod->command, mod);
        return true;
    }
    std::string Terminal::getEnvVar(const std::string_view var){
        auto it = envVars_.find(std::string(var));
        if(it == envVars_.end())
            return std::string();
        return it->second;
    }
}   // namespace SimpleTerminal