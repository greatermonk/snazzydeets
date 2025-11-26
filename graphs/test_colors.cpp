#include<iostream>
#include "colours.hpp"
using namespace colors;

int main(){
    short x = 10;
    float y = 3.14F;

    std::cout << "--- My Project's Output ---" << std::endl;
    
    std::cout << GREEN << "Success: " << RESET << "File processed." << std::endl;
    std::cout << YELLOW << "Warning: " << RESET << "Cache is full." << std::endl;
    std::cout << RED << "Error: " << RESET << "File not found!" << std::endl;
    
    std::cout << "\n--- Special Colors ---" << std::endl;
    std::cout << orange << "This is orange." << RESET << std::endl;
    std::cout << indigo << "This is indigo." << RESET << std::endl;

    std::cout << BRIGHT_YELLOW << "This is bright yellow (aka gold!)" << RESET << std::endl;

    std::cout << RED << "Displaying a integer: " << x << RESET << std::endl;
    std::cout << BRIGHT_YELLOW << "Displaying a float: " << BOLD << y << RESET << std::endl;

    std::cout << CYAN << "This is a CYAN" << RESET << std::endl;
    std::cout << BLUE << "This is a BLUE" << RESET << std::endl;
    std::cout << BRIGHT_BLUE << "This is BRIGHT BLUE" << RESET << std::endl;
    std::cout << MAGNETA << "This is a MAGNETA" << RESET << std::endl;
    std::cout << BRIGHT_RED << "This is a BRIGHT RED" << RESET << std::endl;
    std::cout << BRIGHT_CYAN << "This is a BRIGHT CYAN" << RESET << std::endl;
    std::cout << BRIGHT_MAGNETA << "This is a BRIGHT MAGNETA" << RESET << std::endl;
    std::cout << BRIGHT_WHITE << BOLD << "This is a BRIGHT WHITE" << RESET << std::endl;
    std::cout << BRIGHT_GREEN << "This is a BRIGHT GREEN" << RESET << std::endl;

    std::cout << BOLD << BRIGHT_BLACK << "This is BRIGHT BLACK in bold" << std::endl;
    std::cout << BOLD << BLACK << "This is BLACK in bold" << std::endl;
    return 0;
}
