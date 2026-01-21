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
        // Terminal error codes for easier error handling
        enum Error : u8;
        /// @brief Main module class for implementing modules to a terminal
        class Module{
        public:
            /// @brief Constructor
            Module(const std::string& Command, const std::function<const void*(std::string_view)>& Digest, const std::function<void(const void* const)>& Handler)noexcept:
                                      name(Command),                                               digest(Digest),                                       handler(Handler){}
            /// @brief Modules name for quick hashing lookup via hash-table
            const std::string name;
            /// @brief Digests an argument string
            const std::function<const void*(const std::string_view)> digest;
            /// @brief Handles modules error block for error reporting & handling
            const std::function<void(const void* const)> handler;
        };
        /// @brief  Implements a constant module to the terminal
        /// @return Terminal error code
        static Error implement(const Module* const mod);
        /// @brief  Digests a input string to its module else handles error
        /// @return Terminal error code
        static Error digest(const std::string_view input);
        /// @brief Handles a terminal error code
        static void handler(const Error err);
    private:
        /// @brief Terminals help module for listing all loaded modules
        static const Module helpMod;
        /// @brief Terminals exit module for exiting the application
        static const Module exitMod;
        /// @brief Hash table for fast cmd detection
        /// @note Pre-filled with help & exit modules
        inline static std::unordered_map<std::string, const Module*> hashTable_ = {
            {"help", &helpMod},
            {"exit", &exitMod}
        };
        /// @brief Error messages array for fast error handling
        inline static constexpr const char* errMessages[] = {
            "Name(noErr)\nDesc(No Error)\n",
            "Name(invCmd)\nDesc(No Module Found For Given Command)\n",
            "Name(ovlMod)\nDesc(During Module Implementation Overlapping Module Found)\n",
            "Name(nullPtr)\nDesc(Function argument was a null pointer)\n"
        };
    };
}   // namespace SimpleTerminal

/// @brief Implementation File
#include "Terminal.inl"