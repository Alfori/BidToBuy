#include "AuctionHouse.hpp"
#include "Product.hpp"
#include "Utilities.hpp"
#include "Electronics.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <limits>
#include "Buyer.hpp"
#include "Seller.hpp"

AuctionHouse* AuctionHouse::instance = nullptr;

AuctionHouse* AuctionHouse::getInstance()   // method to get the instance of the auction house using the singleton pattern/method
{
    if (instance == nullptr) 
    {
        instance = new AuctionHouse(); // make new if doesnt exist
    }
    return instance;
}

// adds a product to the auction house
void AuctionHouse::addProduct(Product& product)
{
    std::string temp = generateRandomProductID();

    while (products.find(temp) != products.end())       // ensure that a unique product ID is generated
    {
        temp = generateRandomProductID();
    }

    product.setId(temp);
    products[product.getId()] = product;
}

// In User.cpp
std::string User::getuserId() const
{
    return this->userId;
}



void AuctionHouse::bidsToCSV(const std::string& filePath)
{
    std::ofstream file(filePath, std::ios::app);

    for (const auto& bid : completedBids)
    {
        file << bid.toCSVString() << std::endl;
    }

    file.close();
}

void AuctionHouse::completeBid(const Bid& bid) 
{
    completedBids.push_back(bid);
}

// removes a product from the auction house by utiliizing the id
void AuctionHouse::removeProduct(const std::string& productID)
{
    auto it = products.find(productID);

    it->second.removeId();
    if (it != products.end())       // make sure prodcuct is found
    {
        products.erase(it);
    }
}


// gets a product by its product id
Product* AuctionHouse::getProduct(const std::string& productID)
{
    auto it = products.find(productID);
    if (it != products.end())
    {
        return &it->second; // return a pointer to product
    }
    return nullptr; // return ull if product isnt found
}

void AuctionHouse::addDummyData()
{
    srand(static_cast<unsigned>(time(nullptr)));
    // create dummies
    Product product1("P023", "iPhone 12", "Brand new iPhone 12", 799.99, ProductQuality::New, "F2942", "Active", 0.0);      // create some dummy products
    Product product2("P026", "Samsung Galaxy S21", "Brand new Samsung Galaxy S21", 699.99, ProductQuality::New, "F2942", "Active", 0.0);
    Product product3("P021", "MacBook Pro", "Brand new MacBook Pro", 1299.99, ProductQuality::New, "F2942", "Active", 0.0);
    Electronics myNewPhone("P223", "Smartphone", "Latest model with high-resolution camera", 999.99, ProductQuality::Used_Good, 12, "Apple", "iPhone 12", false);

    std::string newCode = generateRandomProductID();        //create a random ID
    product1.setId(newCode);                                // set it's ID
    newCode = generateRandomProductID();
    product2.setId(newCode);
    newCode = generateRandomProductID();
    product3.setId(newCode);
    newCode = generateRandomProductID();
    myNewPhone.setId(newCode);

    // add to the auction house
    addProduct(product1);
    addProduct(product2);       // add products to the auction house
    addProduct(product3);
    addProduct(myNewPhone);
}

void AuctionHouse::listProducts()
{
    for (auto& product : products)
    {
        product.second.printProduct();      // loop through the products and print
    }
}

void AuctionHouse::listSoldProducts()
{
    for (auto& product : products)
    {
        if(product.second.getStatus() == "Sold")
        {
            product.second.printProduct();      // loop through them products and print them
        }
    }
}

std::vector<Product> AuctionHouse::getProductsBySeller(const std::string& sellerId) {
    std::vector<Product> sellerProducts;        // create a vector to store the seller products
    for (const auto& pair : products) 
    {
        const auto& product = pair.second;
        if (product.getSellerId() == sellerId)
        {
            sellerProducts.push_back(product);  // add the product to the vector
        }
    }

    return sellerProducts;
}

std::vector<Bid> AuctionHouse::getActiveBidsForProduct(const std::string& productId) 
{
    std::vector<Bid> productBids;    // create a vector to store the product bids
    for (const auto& bid : activeBids)  // loop through the active bids
    {
        if (bid.getProductID() == productId) 
        {
            productBids.push_back(bid);    // add the bid to the vector
        }
    }
    return productBids;
}

// didnt end up needing./using this
void AuctionHouse::closeBid(const std::string& bidId) 
{
    activeBids.erase(std::remove_if(activeBids.begin(), activeBids.end(), [&bidId](const Bid& bid)
    {
        return bid.getBidID() == bidId;   // remove the bid
    }), activeBids.end());
}

void AuctionHouse::sendMessage(const std::string& senderId, const std::string& recipientId, const std::string& content) 
{
    messages.emplace(recipientId, Message(senderId, recipientId, content));     // add a message to the map
}

void AuctionHouse::displayMessages(const std::string& userId)
{
    for (const auto& messagePair : messages)    // loop through the messages
    {
        if (messagePair.first == userId) 
        {
            const Message& message = messagePair.second;
            std::cout << "From: " << message.senderId << " - " << message.content << std::endl;

            // Option to respond
            std::cout << "Do you want to respond to this message? (y/n): ";
            char response;
            std::cin >> response;

            if (response == 'y' || response == 'Y') 
            {
                std::cout << "Enter your message: ";
                std::string replyContent;
                std::cin.ignore();
                std::getline(std::cin, replyContent);
                sendMessage(userId, message.senderId, replyContent);
            }
        }
    }
}

std::shared_ptr<User> AuctionHouse::loginOrCreateUser(int Role)
{
    std::string userId;
    std::string name, email, address;
    std::cout << "Enter your user ID or press Enter to create a new account: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear the buffer
    std::getline(std::cin, userId);    // get the user ID

    std::shared_ptr<User> testUser = getUserById(userId);  // get the user by the ID

    if (Role == 1 && testUser->getRole() == "Buyer")
    {
        std::cout << "You are a seller, you cannot log in as a buyer!" << std::endl;
        return nullptr;
    }

    if (Role == 2 && testUser->getRole() == "Seller")
    {
        std::cout << "You are a buyer, you cannot log in as a seller!" << std::endl;
        return nullptr;
    }

    std::shared_ptr<User> newUser;

    if (userId.empty() || !userExists(userId))  // check if the user exists or if the user ID is empty
    {
        std::cout << "Your ID is either not found or you asked to create a new account!" << std::endl;

        userId = generateRandomUserID();

        while (userExists(userId))
        {
            userId = generateRandomUserID();    // generate a random user ID by utinsg utility
        }

        std::cout << "Enter your name: ";
        std::getline(std::cin, name);
        std::cout << "Enter your email: ";
        std::getline(std::cin, email);
        std::cout << "Enter your address: ";
        std::getline(std::cin, address);
        std::shared_ptr<User> newUser = std::make_shared<User>(userId, name, email, address, 0.0);  // create a new user
        std::cout << "Your new user ID is: " << userId << std::endl;        // output the user ID so they can log in in the future

        newUser = std::make_shared<User>(userId, name, email, address, 0.0);
        users[userId] = newUser;

        std::cout << "Total users: " << users.size() << std::endl;
        std::cout << "User exists: " << userExists(userId) << std::endl;
    }

    else if(testUser->getRole() == "Seller" && Role == 2)
    {
        std::cout << "You are a seller, you cannot log in as a buyer!" << std::endl;
        return nullptr;
    }

    else if(testUser->getRole() == "Buyer" && Role == 1)
    {
        std::cout << "You are a buyer, you cannot log in as a seller!" << std::endl;
        return nullptr;
    }

    else
    {
        std::cout << "Welcome back, " << users[userId]->getName() << "!" << std::endl;
        newUser = users[userId];
        return newUser;
    }
    std::ofstream outFile("../CSV/users.csv", std::ios::app); // Open in append mode
    
    
    if (Role == 1)  // check the role if its a seller
    {
        if (outFile) 
        {
            outFile << userId << "," << name << ",Seller," << email << "," << address << ",0.0\n";
            std::cout << "Seller added to CSV file.\n" << std::endl;
        }

        else 
        {
            std::cerr << "Failed to open users.csv for writing.\n";
            std::cout << "Seller not added to CSV file.\n" << std::endl;
        }
    }

    else        // if its a buyer
    {
        if (outFile) 
        {
            outFile << userId << "," << name << ",Buyer," << email << "," << address << ",0.0\n";
            std::cout << "Buyer added to CSV file.\n" << std::endl;
        } 

        else
        {
            std::cerr << "Failed to open users.csv for writing.\n";
            std::cout << "Buyer not added to CSV file.\n" << std::endl;
        }
    }
    


    return newUser;
}

void AuctionHouse::updateProduct(const Product& updatedProduct) 
{
    products[updatedProduct.getId()] = updatedProduct;  // update the product
    updateProductsCSV();
}



void AuctionHouse::updateProductsCSV()
{
    std::ofstream outFile("../CSV/bids.csv", std::ios::trunc);

    if (!outFile.is_open()) 
    {
        std::cerr << "Failed to open bids.csv for writing." << std::endl;
        return;
    }

    outFile << "ProductID,ProductName,Description,BasePrice,Quality,Status,SellerID" << std::endl;

    for (const auto& [id, product] : products)
        if (!product.getId().empty() && product.getBasePrice() >= 0 && product.getId() != "ProductID")
        {
            outFile << product.getId() << "," << product.getName() << "," << product.getDescription() << "," << product.getBasePrice() << "," << std::to_string(static_cast<int>(product.getQuality())) << "," << product.getStatus() << "," << product.getSellerId() << std::endl;
        }

    outFile.close();    // close the file
}



void AuctionHouse::initializeApplicationsFromCSV(const std::string& userCSVPath, const std::string& productCSVPath)
{
    std::ifstream userFile(userCSVPath);    // open the user file
    std::ifstream productFile(productCSVPath);  // open the product file
    std::string line;   // create a string to store the line

    if (getline(userFile, line)) 
    {
        std::cout << "Skipping user CSV header: " << line << std::endl;
    }

    while (getline(userFile, line))     // loop through the user file and read the data
    {
        std::stringstream ss(line);
        std::string userType, userId, userName, userEmail, userAddress;  // create strings to store the user data
        float accountBalance;
        getline(ss, userId, ',');
        std::cout << "User ID: " << userId << std::endl;
        getline(ss, userName, ',');
        std::cout << "User Name: " << userName << std::endl;
        getline(ss, userType, ',');
        std::cout << "User Type: " << userType << std::endl;
        getline(ss, userEmail, ',');
        std::cout << "User Email: " << userEmail << std::endl;
        getline(ss, userAddress, ',');
        std::cout << "User Address: " << userAddress << std::endl;
        ss >> accountBalance;
        std::cout << "Account Balance: " << accountBalance << std::endl;

        std::cout << "Adding user: " << userId << " " << userName << " " << userEmail << " " << userAddress << " " << accountBalance << "\n" << std::endl;

        if (userType == "Buyer")    // check the user type and create a user accordingly
        {
            std::shared_ptr<User> newUser = std::make_shared<Buyer>(userId, userName, userEmail, userAddress, accountBalance);
            newUser->setRole("Buyer");
            users[userId] = newUser;
        }
        
        else if (userType == "Seller")  // check the user type and create a user accordingly
        {
            std::shared_ptr<User> newUser = std::make_shared<Seller>(userId, userName, userEmail, userAddress, accountBalance);
            newUser->setRole("Seller");
            users[userId] = newUser;
        }

        else
        {
            std::shared_ptr<User> newUser = std::make_shared<Seller>(userId, userName, userEmail, userAddress, accountBalance);
        }
    }

    if (getline(userFile, line)) 
    {
        std::cout << "Skipping user CSV header: " << line << std::endl;
    }

    while (getline(productFile, line))
    {
        std::stringstream ss(line);     // create a string stream
        std::string productId, productName, productDescription, qualityStr, status, sellerId;
        double basePrice;
        ProductQuality quality;

        getline(ss, productId, ',');
        getline(ss, productName, ',');
        getline(ss, productDescription, ',');
        ss >> basePrice;
        ss.ignore();        // ignore the comma since last val was a doubel
        getline(ss, qualityStr, ',');
        getline(ss, status, ',');
        getline(ss, sellerId);

        if (qualityStr == "New") 
        {
            quality = ProductQuality::New;
        } 
        
        else if (qualityStr == "Used_VeryGood") 
        {
            quality = ProductQuality::Used_VeryGood;
        } 
        
        else if (qualityStr == "Used_Good") 
        {
            quality = ProductQuality::Used_Good;
        } 
        
        else if (qualityStr == "Used_Okay") 
        {
            quality = ProductQuality::Used_Okay;
        } 
        
        else 
        {
            quality = ProductQuality::New;
        }

        Product product(productId, productName, productDescription, basePrice, quality, sellerId, status);
        products[productId] = product;
    }
}

void AuctionHouse::updateProductDetails(const std::string& productId, const std::string& newName, const std::string& newDescription, double newBasePrice, const std::string& newStatus) {
    auto it = products.find(productId);

    if (it != products.end())   // check if the product is found
    {
        it->second.setName(newName);    // update the product details
        it->second.setDescription(newDescription);
        it->second.setBasePrice(newBasePrice);
        it->second.setStatus(newStatus);    // update the product details
    } 
    
    else 
    {
        std::cerr << "Product with ID " << productId << " not found." << std::endl;
    }

    saveProductsToCSV("../CSV/bids.csv");   // save the products to the CSV file
}

void AuctionHouse::saveProductsToCSV(const std::string& filePath) 
{
    std::ofstream file(filePath);

    if (!file.is_open())    // check if the file is open
    {
        std::cerr << "Failed to open " << filePath << " for writing." << std::endl;
        return;
    }

    file << "ProductID,Name,Description,BasePrice,Quality,SellerID,Status\n";

    for (const auto& [productID, product] : products)   // parse through the products and write them to the file
    {
        file << productID << ","
             << product.getName() << ","
             << "\"" << product.getDescription() << "\","
             << product.getBasePrice() << ","
             << static_cast<int>(product.getQuality()) << ","
             << product.getStatus() << ","
             << product.getSellerId() << "\n";
    }

    file.close();
}

void AuctionHouse::addMessage(const Message& message)
{
    messages.insert({message.recipientId, message});    // add a message to the map
}

std::vector<Message> AuctionHouse::getMessagesForUser(const std::string& userId)    // method to get messages for a user
{
    std::vector<Message> userMessages;
    for (const auto& [key, msg] : messages)
    {
        if (msg.recipientId == userId) 
        {
            userMessages.push_back(msg);    // loop through the messages and add them to the vector
        }
    }
    return userMessages;
}

Product AuctionHouse::getProductById(const std::string& productId) {
    auto it = products.find(productId); // find the product by its ID
    if (it != products.end()) 
    {
        return it->second;      // return the product
    } 

    else 
    {
        return Product();       // return an empty product
    }
}

std::shared_ptr<User> AuctionHouse::getUserById(const std::string& userId) 
{
    auto it = users.find(userId);
    if (it != users.end()) 
    {
        return it->second;  // return a pointer to the user
    } 
    
    else
    {
        return nullptr;
    }
}


void AuctionHouse::closeBid(const std::string& productId, std::string sellerID, std::string buyerID)     // method to close a bid
{
    auto seller = getUserById(sellerID);       // get the seller
    auto buyer = getUserById(buyerID);         // get the buyer
    auto product = getProductById(productId);       // get the product

    product.setStatus("Sold");      // set the status of the product to sold
    product.setBuyerId(buyerID);     // set the buyer id

    auto sellerBalance = seller->getAccountBalance();       // get the seller's balance
    auto buyerBalance = buyer->getAccountBalance();         // get the buyer's balance

    seller->updateAccountBalance(sellerBalance + product.getCurrentBid());       // set the seller's balance
    buyer->updateAccountBalance(buyerBalance - product.getCurrentBid());         // set the buyer's balance

    updateProduct(product);     // update the product

    std::cout << "The bid has been closed successfully.\n";
}