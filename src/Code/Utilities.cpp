#include <limits> // Add this line
#include "Utilities.hpp"
#include <random>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <limits>

int getInput(const std::string& prompt)     // get input from user return an integer
{
    int input;  // input variable
    std::cout << prompt;
    while (!(std::cin >> input)) 
    {
        std::cin.clear(); // clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear the buffer
    return input;
}

std::string generateRandomUserID() 
{
    // random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // found this method online, works pretty well
    std::uniform_int_distribution<int> distribution(1, 1000);
    
    // generate a random number and convert it to a string, starts with U then number
    return "U" + std::to_string(distribution(gen));
}

std::string generateRandomProductID() 
{
    // random number generator
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    
    // found this method online, works pretty well
    std::uniform_int_distribution<int> distribution(1, 1000);
    
    // generate a random number and convert it to a string, starts with P then number
    return "P" + std::to_string(distribution(gen));
}


std::string getStringInput(const std::string& prompt) 
{
    std::cout << prompt;    // show the prompt
    std::string input;
    std::getline(std::cin, input);  // get the input
    return input;  // return the input
}