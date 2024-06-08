#include "User.hpp"
#include <vector>
#include "Message.hpp"
#include "Product.hpp"
#include <iostream>
#include <string>

class Seller : public User 
{
private:
    std::list<std::string> productsForSale;
    std::list<std::string> soldProducts;
    std::string sellerID;
    
public:
    Seller(std::string userID, std::string name, std::string email, std::string address, float accountBalance)
        : User(userID, name, email, address, accountBalance) {}

    void addProductForSale();
    void listBids();
    void viewHistoricalPricing();
    void manageBids();
    void getAccountBalances();
    void updateUserInfo();
    void accessMessaging();
    void viewMessages();
    void sendMessage();
};