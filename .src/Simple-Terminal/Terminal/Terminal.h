/// @file  Simple-Terminal/Terminal/Terminal.h
/// @brief The main declaration file for The Terminal class & utilities
#pragma once
#include "stdint.h"
#include <string>
#include <string_view>
#include <functional>
#include <cstdio>

namespace SimpleTerminal{
    /// @brief Main terminal class for easy module implementation
    class Terminal{
    public:
        /// @brief Main module class for implementing modules to a terminal
        class Module{
        public:
            /// @brief Constructor
            Module(const std::string& Command, const std::string& Brief, const std::function<void(std::string_view)>& Digest)noexcept:
                                      command(Command),           brief(Brief),                                       digest(Digest){}
            /// @brief Modules command for quick hashing lookup via hash-table
            const std::string command;
            /// @brief A brief description of the function for the help command
            const std::string brief;
            /// @brief Digests an argument string
            const std::function<void(const std::string_view)> digest;
        };
        /// @brief  Implements a constant module to the terminal
        /// @return False if command name already has a module
        static bool implement(const Module* const mod);
        /// @brief  Digests a input string to its module else handles error
        static void digest(const std::string_view input);
    private:
        /// @brief Parses a string and turns environment variables to their hashed string if found
        /// @return Returns new parsed string
        static std::string parseVars(const std::string_view input);
        /// @brief Terminals help module for listing all loaded modules
        static const Module helpMod;
        /// @brief Terminals listev module for listing environment variables
        static const Module listMod;
        /// @brief Terminals setev module for setting environment variables
        static const Module setMod;
        /// @brief Terminals remev module for removing environment variables
        static const Module remMod;
        /// @brief Hash table for fast cmd detection
        /// @note Pre-filled with help, lev, sev, & rev modules
        inline static std::unordered_map<std::string, const Module*> cmdLets_ = {
            {"help", &helpMod}, {"lev", &listMod}, {"sev", &setMod}, {"rev", &remMod}
        };
        /// @brief Hash table for fast environment variable parsing
        inline static std::unordered_map<std::string, std::string> envVars_;
    };
}   // namespace SimpleTerminal

/// @brief Implementation File
#include "Terminal.inl"