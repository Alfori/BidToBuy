#include <iostream>
#include "Seller.hpp"
#include "Buyer.hpp"
#include "Utilities.hpp"
#include "Message.hpp"
#include "AuctionHouse.hpp"
#include <thread>

int main() 
{
    // initialize CSV files
    auto auctionHouse = AuctionHouse::getInstance();

    std::cout << "Welcome to BidToBuy!" << std::endl;
    auctionHouse->initializeApplicationsFromCSV("../CSV/users.csv", "../CSV/bids.csv");
    

    // simple welcome message

    // get whether they are seller or buyer
    std::cout << "Are you a Seller (1) or a Buyer (2)? Enter your choice: ";
    int userRole;
    std::cin >> userRole;

    auto user = auctionHouse->loginOrCreateUser(userRole);

    if (user == nullptr) 
    {
        std::cout << "Failed to login or create user. Exiting." << std::endl;

        for (int i = 3; i > 0; i--) 
        {
            std::cout << "Exiting in " << i << " seconds..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        return 1;
    }
    
    if (userRole == 1) // seller
    {  
        auto seller = std::dynamic_pointer_cast<Seller>(user);

        while (true)
        {
            int action = getInput("Seller Actions: [1] Post Product, [2] View Historical Pricing, [3] Send Message, [4] Manage Bids, [5] Update User Info, [6] Get Account Balance, [7] View Your Products, [8] Log out: ");

            switch (action)
            {
                case 1:
                    seller->addProductForSale();        // DONE
                    break;
                case 2:
                    auctionHouse->listSoldProducts();        // DONE (JUST ADD BUYER ID TO THE PRODUCT)
                    break;
                case 3:
                    seller->accessMessaging();              // NEED TO IMPLEMENT
                    break;
                case 4:
                    seller->manageBids();               // DONE
                    break;
                case 5:
                    seller->updateUserInfo();           // DONE
                    break;
                case 6:
                    seller->getAccountBalances();       // DONE
                    break;
                case 7:
                    seller->listBids();                 // DONE
                    break;
                case 8:
                    std::cout << "Logge out, goodbye !" << std::endl;       // DONE
                    return 0;
                default:
                    std::cout << "Not one of the options !" << std::endl;     // DONE
            }
        }
    } 
    
    else if (userRole == 2)   // buyer
    {
        auto buyer = std::dynamic_pointer_cast<Buyer>(user);

        while (true)
        {
            int action = getInput("Buyer Actions: [1] View Products, [2] Place Bid, [3] Access Messaging, [4] View Purchase History, [5] View Balance, [6] Update User Info, [7] Logout: ");

            switch (action)
            {
                case 1:
                    buyer->viewProducts();      // SHOULD BE EASY
                    break;
                case 2:
                    buyer->placeBid();          // NEED TO IMPLEMENT
                    break;
                case 3:
                    buyer->accessMessaging();       // NEED TO IMPLEMENT
                    break;
                case 4:
                    buyer->viewPurchaseHistory();       // NEED TO IMPLEMENT
                    break;
                case 5:
                    buyer->getAccountBalances();     // DONE
                    break;
                case 6:
                    buyer->updateUserInfo();        // DONE
                    break;
                case 7:
                    std::cout << "Logge out, goodbye !" << std::endl;       // DONE
                    return 0;
                default:
                    std::cout << "Not one of the options !" << std::endl;     // DONE
            }
        }
    } 
    
    else 
    {
        std::cout << "That's not a role, exiting." << std::endl;
        return 1;
    }

    return 0;
}
