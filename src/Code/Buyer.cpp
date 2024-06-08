#include "Buyer.hpp"
#include "AuctionHouse.hpp"
#include <iostream>
#include <string>
#include "Utilities.hpp"

// =============================================================================== VIEW ALL BIDS =============================================================================

void Buyer::viewProducts() 
{
    auto auctionHouse = AuctionHouse::getInstance(); // get singleton isntantce
    auto products = auctionHouse->getProducts();    // get list of products

    std::cout << "Available Products:\n";
    for (auto& [id, product] : products)
    {
        if (product.getStatus() == "open" || product.getStatus() == "Open")
        {
            product.printProduct();
        }
    }
}

// =============================================================================== VIEW PURCHASE HISTORY =============================================================================

void Buyer::viewPurchaseHistory()
{
    std::cout << "Your Purchase History:\n";

    auto auctionHouse = AuctionHouse::getInstance();
    auto products = auctionHouse->getProducts();

    bool hasPurchasedProducts = false;


    for (auto& productPair : products) 
    {
        auto& theProduct = productPair.second;
        if ((theProduct.getStatus() == "Sold" || theProduct.getStatus() == "sold") && theProduct.getBuyerId() == this->getUserId()) 
        {
            theProduct.printProduct();
            hasPurchasedProducts = true;
        }
    }

    if (!hasPurchasedProducts) 
    {
        std::cout << "You have not purchased any products yet.\n";
    }
}


// =============================================================================== PLACE BIDS =============================================================================

void Buyer::placeBid()
{
    auto auctionHouse = AuctionHouse::getInstance();
    auto products = auctionHouse->getProducts(); // get list of products

    std::string tempProductId = getStringInput("Enter the ID of the product you want to bid on: ");

    auto product = products.find(tempProductId);        // find product by id
    if (product != products.end() && (product->second.getStatus() == "open" || product->second.getStatus() == "Open"))      // check if product exists and is open
    {
        double currentBid = product->second.getCurrentBid();    // get current bid
        double newBid = getInput("Enter your bid amount: ");    // get new bid amounts

        if (newBid > currentBid && getAccountBalance() >= newBid)   // check if bid is higher than current bid and user has enough balance
        {
            product->second.setCurrentBid(newBid);  // set new bid
            product->second.setBuyerId(getUserId());    // set buyer id
            std::cout << "Your bid has been placed successfully on " << product->second.getName() << "." << std::endl;
        }

        else if (getAccountBalance() < newBid)  // check if user has enough balance
        {
            std::cout << "You do not have enough balance to place this bid.\n";
        }

        else if (newBid <= currentBid)  // check if bid is higher than current bid
        {
            std::cout << "Your bid amount must be higher than the current bid.\n";
        }

        else if (product->second.getStatus() != "open" || product->second.getStatus() != "Open")    // check if product is open
        {
            std::cout << "This product is not open for bidding.\n";
        
        }

        else
        {
            std::cout << "Please use a valid number.\n";    // invalid input
        }
    }

    else 
    {
        std::cout << "Product not found.\n";    // product not found / incorrect id
    }
}


void Buyer::accessMessaging()
{
    AuctionHouse* auctionHouse = AuctionHouse::getInstance();   // get singleton instance
    bool isRunning = true;
    while (isRunning) 
    {
        std::cout << "Messaging Menu:\n";
        std::cout << "1. View Messages\n";
        std::cout << "2. Send Message\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        switch (choice) 
        {
            case 1:
                viewMessages(); // view messages
                break;
            case 2:
                sendMessage();  // send message
                break;
            case 3:
                isRunning = false;      // exit
                std::cout << "Exiting messaging menu.\n";
                break;
            default:        // reloop
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Buyer::viewMessages() 
{
    AuctionHouse* auctionHouse = AuctionHouse::getInstance();       // get singleton instance
    std::vector<Message> messages = auctionHouse->getMessagesForUser(this->getUserId());    // get messages for user

    std::cout << "Received Messages:\n";
    for (const auto& msg : messages) 
    {
        std::cout << "From: " << msg.senderId << " - " << msg.content << "\n";  // print messages
    }
}

void Buyer::sendMessage()
{
    AuctionHouse* auctionHouse = AuctionHouse::getInstance();
    std::string recipientId, content;
    std::cout << "Enter recipient ID: ";
    std::cin >> recipientId;
    std::cin.ignore();
    std::cout << "Enter message: ";
    std::getline(std::cin, content);  // use getlint to allow spaces in the messages

    Message newMessage(this->getUserId(), recipientId, content);
    auctionHouse->addMessage(newMessage);  // add message

    std::cout << "Message sent.\n";
}

void Buyer::getAccountBalances()       // get the account balance
{
    std::cout << "Your account balance is: " << this->getAccountBalance() << std::endl;
}

void Buyer::updateUserInfo()
{
    AuctionHouse* auctionHouse = AuctionHouse::getInstance();

    std::string newName, newEmail, newAddress;
    std::cout << "Enter new name: ";
    std::getline(std::cin >> std::ws, newName);
    std::cout << "Enter new email: ";
    std::getline(std::cin, newEmail);
    std::cout << "Enter new address: ";
    std::getline(std::cin, newAddress);
    // get te path to the csv file, rest of comments are in Buyer.cpp
    std::string filePath = "../CSV/users.csv";
    std::ifstream inFile(filePath);
    std::vector<std::string> lines;
    std::string line;

    // update it
// update it
    while (getline(inFile, line))
    {
        std::stringstream ss(line);
        std::string tempUserId;
        getline(ss, tempUserId, ',');

        if (tempUserId == this->getUserId())
        {
            // Construct the new line by skipping the next three fields (name, role, email, and address)
            // and then appending the new name, role, email, and address along with the remaining fields
            std::string ignoredField;
            for (int i = 0; i < 4; ++i) // Skip next three fields (name, role, and email)
                getline(ss, ignoredField, ',');

            std::string remainder;
            getline(ss, remainder); // Capture the rest of the line after the address

            line = tempUserId + "," + newName + ",Buyer," + newEmail + "," + newAddress + (remainder.empty() ? "" : "," + remainder);
        }
        lines.push_back(line);
    }

    inFile.close();

    std::ofstream outFile(filePath);
    for (const auto& updatedLine : lines)
    {
        outFile << updatedLine;
        if (&updatedLine != &lines.back())      // if the updated line is not the last line
        {
            outFile << std::endl;
        }
    }
    outFile.close();

    std::cout << "User info updated!" << std::endl;
}