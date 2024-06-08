#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
#include <iostream>
#include <ostream>

// enum class for the quality of the product
enum class ProductQuality
{
    New,
    Used_VeryGood,
    Used_Good,
    Used_Okay
};

// enum class for the subclass of the product
enum class productClass
{
    Electronics, 
    Clothing, 
    Home, 
    Shoes, 
    petSupplies,
    Default
};

class Product
{
private:
    std::string id; // identifier for the product
    std::string name; // name of the product
    std::string description; // description of the product
    double basePrice; // starting price
    ProductQuality quality; // quality of product
    std::string status; // set the status to active or sold
    double currentBid; // current bid on the product
    std::string sellerID; // id of the buyer
    std::string buyerID;    // id of the buyer
    productClass classType;     // class of the product
    

public:
    // default constructor
    Product() : basePrice(0.0), quality(ProductQuality::New) {}

    // constructor jsut to initialize a product
    Product(const std::string id, const std::string& name, const std::string& description, double basePrice, ProductQuality quality, std::string sellerID, std::string status = "Open", double currentBid = 0.0f, std::string buyerID = "None", productClass classType = productClass::Default)
        : id(id), name(name), description(description), basePrice(basePrice), quality(quality), sellerID(sellerID), status(status), currentBid(currentBid), buyerID(buyerID), classType(classType) {}


    // getter
    std::string getId() const {return id;}
    std::string getProductId() const {return id;}
    std::string getName() const {return name;}
    std::string getDescription() const {return description;}
    double getBasePrice() const {return basePrice;}
    ProductQuality getQuality() const {return quality;}
    std::string getSellerId() const {return sellerID;}
    std::string getStatus() const {return status;}
    std::string getBuyerId() const {return buyerID;}
    double getCurrentBid() const {return currentBid;}
    productClass getClassType() const {return classType;}

    // setters
    void setName(const std::string& newName) {name = newName;}
    void setDescription(const std::string& newDescription) { description = newDescription;}

    void setBasePrice(double newBasePrice) 
    {
        basePrice = newBasePrice;
    }

    void setProductClass(productClass newClass) {classType = newClass;}
    void setQuality(ProductQuality newQuality) {quality = newQuality;}
    void setId(std::string newId) {id = newId;}
    void removeId() {id = "";}
    void setStatus(std::string newStatus) {status = newStatus;}
    void setSellerId(std::string newSellerId) {sellerID = newSellerId;}
    void setCurrentBid(double newCurrentBid) {currentBid = newCurrentBid;}
    void setBuyerId(std::string newBuyerId) {buyerID = newBuyerId;}
    

    virtual void printProduct();
};

#endif