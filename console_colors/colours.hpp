#include<iostream>
#ifndef COLOURS_HPP
#define COLOURS_HPP
/**
 * @file colours.hpp
 * @brief A header-only C++ file for ANSI color-coded terminal output.
 *
 * Includes constants for standard (16) and extended (256-color)
 * ANSI escape codes, organized within the 'colors' namespace.
 *
 * Usage:
 * #include "colors.hpp"
 */ 
// Define a namespace for ANSI color constants
namespace colors {
    // --- Standard 16 Colors ---
    // Reset
    constexpr const char* RESET = "\033[0m";
    constexpr const char* BG_BLUE = "\033[44m";
    // Regular
    constexpr const char* BLACK = "\033[30m";
    constexpr const char* RED = "\033[31m";
    constexpr const char* GREEN = "\033[32m";
    constexpr const char* YELLOW = "\033[33m";
    constexpr const char* BLUE = "\033[34m";
    constexpr const char* MAGNETA = "\033[35m";
    constexpr const char* CYAN = "\033[36m";
    constexpr const char* WHITE = "\033[37m";
    constexpr const char* BOLD = "\033[1m";
    
    // Bright
    constexpr const char* BRIGHT_BLACK= "\033[90m";
    constexpr const char* BRIGHT_RED = "\033[91m";
    constexpr const char* BRIGHT_GREEN = "\033[92m";
    constexpr const char* BRIGHT_YELLOW = "\033[93m";
    constexpr const char* BRIGHT_BLUE = "\033[94m";
    constexpr const char* BRIGHT_MAGNETA = "\033[95m";
    constexpr const char* BRIGHT_CYAN = "\033[96m";
    constexpr const char* BRIGHT_WHITE = "\x1b[97m";

    // --- 256-Color Additions ---
    // Note: These require a 256-color compatible terminal.
    
    /**
     * @brief A 256-color approximation for Orange.
     * (Color index 208)
     */
    constexpr const char* orange = "\033[38;5;208m";

    /**
     * @brief A 256-color approximation for Indigo.
     * (Color index 54)
     */
    constexpr const char* indigo = "\033[38;5;54m";


    template<typename T>
    void cprint(bool use_color, T text, const char* COLOR = BRIGHT_WHITE, bool make_bold = false){
         if (use_color && !make_bold) {
             std::cout << COLOR << text << RESET;
         }
         else if (make_bold && use_color){
                  std::cout << COLOR << BOLD << text << RESET;
         }
         else {
             std::cout << text;
         }
    }
}

#endif
