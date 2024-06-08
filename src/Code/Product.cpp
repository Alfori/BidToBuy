#include "Product.hpp"
#include <iostream>
#include <ctime>


std::string qualityToString(ProductQuality quality)     // convert quality to string, makes things easier
{
    switch (quality) 
    {
        case ProductQuality::New: return "New";
        case ProductQuality::Used_VeryGood: return "Used - Very Good";
        case ProductQuality::Used_Good: return "Used - Good";
        case ProductQuality::Used_Okay: return "Used - Okay";
        default: return "Unknown";
    }
}

void Product::printProduct()        // print product details
{
    std::cout << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << "Product ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Base Price: " << basePrice << std::endl;
    std::cout << "Quality: " << qualityToString(quality) << std::endl;
    std::cout << "Status: " << status << std::endl;
    std::cout << "Current Bid: " << currentBid << std::endl;
    std::cout << "Seller ID: " << sellerID << std::endl;
    std::cout << "Buyer ID: " << buyerID << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << std::endl;
}

