#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

// global variable
std::string generateRandomProductID();                      // generate a random product id
int getInput(const std::string& prompt);                    // get input from user return an integer
std::string generateRandomUserID();                         // generate a random user id
std::string loginOrCreateUser();                            // login or create a new user
std::string getStringInput(const std::string& prompt);      // get input from user return a string

#endif