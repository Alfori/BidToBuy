// Bid.hpp
#ifndef BID_HPP
#define BID_HPP

#include <string>
#include <sstream>
#include "Product.hpp"

class Bid
{
    private:
        std::string bidId;
        std::string productId;
        std::string userId;
        float currentAmount;
        float startingAmount;
        
    public:

        Bid(const std::string& bidID, const std::string& productID, const std::string& userID, float currentAmount, float startingAmount);

        // getters
        std::string getBidID() const {return bidId;}
        std::string getProductID() const {return productId;}
        std::string getUserID() const {return userId;}
        float getCurrentAmount() const {return currentAmount;}
        float getStartingAmount() const {return startingAmount;}

        // setters
        void setCurrentAmount(float newAmount) {currentAmount = newAmount;}
        void setStartingAmount(float newAmount) {startingAmount = newAmount;}

        std::string toCSVString() const 
        {
            std::stringstream ss;
            ss << bidId << "," << productId << "," << userId << "," << currentAmount;
            return ss.str();
        }

        
    };

#endif