#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>

// base class for all users
class User
{

private:
    std::string userId;
    std::string name;
    std::string email;
    std::string address;
    float accountBalance;
    std::string role;

public:
    User(std::string userId, std::string name, std::string email, std::string address, float accountBalance = 200.)
        : userId(userId), name(name), email(email), address(address), accountBalance(accountBalance) {}

    virtual ~User() {}

    // getters
    std::string getUserId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getAddress() const;
    std::string getuserId() const;
    std::string getRole() const;
    float getAccountBalance() const {return accountBalance;}

    // setters
    void setRole(const std::string& newRole);
    void setName(const std::string& newName);
    void setEmail(const std::string& newEmail);
    void setAddress(const std::string& newAddress);
    void updateAccountBalance(float amount) {accountBalance += amount;}
   // void updateUserInfo();
    //void accessMessaging();
    //void viewMessages();
    //void sendMessage();
};

#endif