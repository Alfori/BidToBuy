#include "User.hpp"
#include <vector>
#include "Message.hpp"
#include "Product.hpp"
#include <iostream>
#include <string>

class Buyer : public User
{
private:
    std::vector<Product> purchaseHistory;

public:
    Buyer(std::string userID, std::string name, std::string email, std::string address, float accountBalance)
        : User(userID, name, email, address, accountBalance) {}

    void addToPurchaseHistory(Product product)      // MAKE SURE TO ADD THIS IF USER BUYS A PRODUCT
    { 
        purchaseHistory.push_back(product);
    }

    void viewPurchaseHistory();

    void placeBid();
    void viewProducts();
    void accessMessaging();
    void viewMessages();
    void sendMessage();
    void getAccountBalances();
    void updateUserInfo();
};