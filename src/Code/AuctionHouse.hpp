#ifndef AUCTIONHOUSE_HPP
#define AUCTIONHOUSE_HPP

#include <map>
#include <string>
#include <memory>
#include <vector>
#include "Bid.hpp"
#include "Product.hpp"
#include "User.hpp"
#include "Bid.hpp"
#include "Message.hpp"
#include <algorithm>
#include <limits>

class AuctionHouse
{
    private:
        static AuctionHouse* instance; // singleton instance
        
        std::map<std::string, std::shared_ptr<User>> users; // map of users
        std::map<std::string, Product> products; // map of productid
        std::vector<Bid> activeBids;            // map of activeBids
        std::vector<Bid> completedBids;         // map of completeBids
        std::multimap<std::string, Message> messages;

        AuctionHouse(){}
        ~AuctionHouse(){}

    public:
        static AuctionHouse* getInstance(); // get instance of auction house / singleton method

        // adds a product to the auction house
        void addProduct(Product& product);
        void addUser(const std::shared_ptr<User>& user);
        void closeBid(const std::string& productId, std::string sellerID, std::string buyerID);
        void bidsToCSV(const std::string& filePath);
        void addBid(const Bid& bid) {activeBids.push_back(bid);}
        void completeBid(const Bid& bid);

        // new bids
        std::vector<Product> getProductsBySeller(const std::string& sellerId);
        std::vector<Bid> getActiveBidsForProduct(const std::string& productId);
        void closeBid(const std::string& productId);
        Product getProductById(const std::string& productId);
        std::shared_ptr<User> getUserById(const std::string& userId);


        // removes a product from auction house
        void removeProduct(const std::string& productID);

        // get product by id
        Product* getProduct(const std::string& productID);

        void addDummyData();

        void addMessage(const Message& message);

        std::vector<Message> getMessagesForUser(const std::string& userId);

        void listProducts();

        std::map<std::string, Product> getProducts() {return products;}

        void sendMessage(const std::string& senderId, const std::string& recipientId, const std::string& content);  // send message
        void displayMessages(const std::string& userId);    // display messages

        bool userExists(const std::string& userId)
        {
            return users.find(userId) != users.end();   // check if user exists by using find
        }

        void initializeApplicationsFromCSV(const std::string& userCSVPath, const std::string& productCSVPath);

        std::shared_ptr<User> loginOrCreateUser(int Role);  // login or create user

        void updateProduct(const Product& updatedProduct);  // update product

        void updateProductsCSV();   // update products to csv

        void saveProductsToCSV(const std::string& filePath);    // save products to csv

        void listSoldProducts();        // list of all the sold products

        void updateProductDetails(const std::string& productId, const std::string& newName, const std::string& newDescription, double newBasePrice, const std::string& newStatus);
};

#endif