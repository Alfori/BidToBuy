#include "Seller.hpp"
#include "AuctionHouse.hpp"
#include "Utilities.hpp"
#include "Product.hpp"

// =============================================================================== MANAGE BIDS =============================================================================

void Seller::manageBids() 
{
    auto auctionHouse = AuctionHouse::getInstance();
    const std::map<std::string, Product>& products = auctionHouse->getProducts();

    for (const auto& [productID, product] : products)
    {
        if (product.getSellerId() == this->getUserId())
        {
            std::cout << "-----------------------" << std::endl;
            std::cout << "Product ID: " << product.getId() << std::endl;
            std::cout << "Name: " << product.getName() << std::endl;
            std::cout << "Current Status: " << product.getStatus() << std::endl;
            std::cout << "Current Base Price: " << product.getBasePrice() << std::endl;
            std::cout << "Current Quality: " << static_cast<int>(product.getQuality()) << std::endl;
            std::cout << "Current Description: " << product.getDescription() << std::endl;
            std::cout << "-----------------------" << std::endl;
    
            if (product.getStatus() == "Sold") 
            {
                std::cout << "Already sold! Cannot manage this product." << std::endl;
                continue; // if sold thens kip to the next product
            }
    
            std::cout << "Do you want to [1] Change name, [2] Change description, [3] Change base price, [4] Change status, [5] Go to the next product." << std::endl;
            int choice;
            std::cin >> choice;
    
            std::string newStatus;
            std::string newName;
            std::string newDescription;
            double newBasePrice;
    
            switch (choice) 
            {
                case 1: // change the base price
                    std::cout << "Enter new name: ";
                    std::cin.ignore();
                    std::getline(std::cin, newName);
                    const_cast<Product&>(product).setName(newName);
                    break;
                case 2: // change the description
                    std::cout << "Enter new description: ";
                    std::cin.ignore(); // Consume the leftover newline character
                    std::getline(std::cin, newDescription);
                    const_cast<Product&>(product).setDescription(newDescription); // Assuming setDescription method exists in Product class
                    break;
                case 3: // change base price
                    std::cout << "Enter new base price: ";
                    std::cin >> newBasePrice;
                    const_cast<Product&>(product).setBasePrice(newBasePrice);
                    break;
                case 4: // cahnge the description
                    std::cout << "Enter new status [Open/Closed/Sold]: ";
                    std::cin >> newStatus;


                    if (newStatus == "Sold" || newStatus == "sold")
                    {
                        auctionHouse->closeBid(productID, this->getUserId(), product.getBuyerId());
                        std::cout << "Product has been sold! to " << product.getBuyerId() << std::endl;
                    }

                    const_cast<Product&>(product).setStatus(newStatus);
                    break;
                case 5:
                    std::cout << "Exiting product management." << std::endl;
                    break;
                default:
                    std::cout << "Invalid option. Please try again." << std::endl;
                    break;
            }
           auctionHouse->updateProduct(product);
        }
    }
}


// =============================================================================== VIEW HISTORICAL =============================================================================

void Seller::viewHistoricalPricing()
{
    AuctionHouse* auctionHouse = AuctionHouse::getInstance();
    const std::map<std::string, Product>& products = auctionHouse->getProducts();

    for (const auto& [productID, product] : products)       // loop through products
    {
        if (product.getStatus() == "Sold")
        {
            std::cout << "-----------------------" << std::endl;
            std::cout << "Product ID: " << productID << std::endl;
            std::cout << "Name: " << product.getName() << std::endl;
            std::cout << "Description: " << product.getDescription() << std::endl;
            std::cout << "Base Price: " << product.getBasePrice() << std::endl;
            std::cout << "Quality: " << static_cast<int>(product.getQuality()) << std::endl;
            std::cout << "Status: " << product.getStatus() << std::endl;
            std::cout << "Seller ID: " << product.getSellerId() << std::endl;
            std::cout << "-----------------------" << std::endl;
        }
    }
}

// =============================================================================== UPDATE USER INFO =============================================================================

void Seller::updateUserInfo()
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

            line = tempUserId + "," + newName + ",Seller," + newEmail + "," + newAddress + (remainder.empty() ? "" : "," + remainder);
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

// =============================================================================== GET ACCOUNT BALANCE =============================================================================

void Seller::getAccountBalances()       // get the account balance
{
    std::cout << "Your account balance is: " << this->getAccountBalance() << std::endl;
}

// =============================================================================== ACCESS MESSAGING =============================================================================

void Seller::accessMessaging()
{
    AuctionHouse* auctionHouse = AuctionHouse::getInstance();       // get the instance of the auction house
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
                viewMessages();     // view the messages    
                break;
            case 2:
                sendMessage();          // send a message
                break;
            case 3:
                isRunning = false;          // exit the messaging menu
                std::cout << "Exiting messaging menu.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Seller::viewMessages() 
{
    AuctionHouse* auctionHouse = AuctionHouse::getInstance();
    std::vector<Message> messages = auctionHouse->getMessagesForUser(this->getUserId());

    std::cout << "Received Messages:\n";
    for (const auto& msg : messages) 
    {
        std::cout << "From: " << msg.senderId << " - " << msg.content << "\n";
    }
}


void Seller::sendMessage()
{
    AuctionHouse* auctionHouse = AuctionHouse::getInstance();
    std::string recipientId, content;
    std::cout << "Enter recipient ID: ";
    std::cin >> recipientId;
    std::cin.ignore();
    std::cout << "Enter message: ";
    std::getline(std::cin, content);

    Message newMessage(this->getUserId(), recipientId, content);
    auctionHouse->addMessage(newMessage);

    std::cout << "Message sent.\n";
}

// =============================================================================== LIST BIDS =============================================================================

void Seller::listBids()
{
    AuctionHouse* auctionHouse = AuctionHouse::getInstance();
    const std::map<std::string, Product>& products = auctionHouse->getProducts();

    for (const auto& [productID, product] : products)
    {
        if (product.getSellerId() == this->getUserId())
        {
            std::cout << "-----------------------" << std::endl;
            std::cout << "Product ID: " << productID << std::endl;
            std::cout << "Name: " << product.getName() << std::endl;
            std::cout << "Description: " << product.getDescription() << std::endl;
            std::cout << "Base Price: " << product.getBasePrice() << std::endl;
            std::cout << "Quality: " << static_cast<int>(product.getQuality()) << std::endl;
            std::cout << "Status: " << product.getStatus() << std::endl;
            std::cout << "Seller ID: " << product.getSellerId() << std::endl;
            std::cout << "Current Highest Bid: " << product.getCurrentBid() << std::endl;
            std::cout << "-----------------------" << std::endl;
        }
    }
}

// =============================================================================== ADD PRODUCT FOR SALE =============================================================================

void Seller::addProductForSale()
{
    std::string sellerID = this->getUserId();

    // select the product type
    std::cout << "Select the product type:\n";
    std::cout << "1. Clothing\n";
    std::cout << "2. Electronics\n";
    std::cout << "3. Home\n";
    std::cout << "4. Shoes\n";
    std::cout << "5. Pet Supplies\n";
    std::cout << "Enter choice: ";
    
    int productTypeSelection;
    std::cin >> productTypeSelection;
    std::cin.ignore();

    productClass pc;
    switch (productTypeSelection) 
    {
        case 1:
            pc = productClass::Clothing;
            break;
        case 2:
            pc = productClass::Electronics;
            break;
        case 3:
            pc = productClass::Home;
            break;
        case 4:
            pc = productClass::Shoes;
            break;
        case 5:
            pc = productClass::petSupplies;
            break;
        default:
            std::cout << "Invalid selection, defaulting to generic product.\n";
            pc = productClass::Default;
            break;
    }

    std::string productName, productDescription;
    double basePrice;
    std::cout << "Enter product name: ";
    std::getline(std::cin, productName);
    std::cout << "Enter product description: ";
    std::getline(std::cin, productDescription);
    std::cout << "Enter base price: ";
    std::cin >> basePrice;
    std::cin.ignore();

    // choose quality
    int qualitySelection = 0;
    ProductQuality productQuality;
    while (true) 
    {
        std::cout << "Select product quality:\n";
        std::cout << "1. New\n2. Used - Very Good\n3. Used - Good\n4. Used - Okay\n";
        std::cout << "Enter your choice (1-4): ";
        std::cin >> qualitySelection;
        std::cin.ignore();

        switch (qualitySelection)
        {
            case 1:
                productQuality = ProductQuality::New;
                break;
            case 2:
                productQuality = ProductQuality::Used_VeryGood;
                break;
            case 3:
                productQuality = ProductQuality::Used_Good;
                break;
            case 4:
                productQuality = ProductQuality::Used_Okay;
                break;
            default:
                std::cout << "Not an option! Try again.\n";
                continue;
        }
        break;
    }

    std::string status;
    int statusSelection = 0;
    while (true) 
    {
        std::cout << "Select if the product is open or closed:\n";
        std::cout << "1. Open\n2. Closed\n3. Sold\n";
        std::cout << "Enter your choice (1-3): ";
        std::cin >> statusSelection;
        std::cin.ignore();

        switch (statusSelection) 
        {
            case 1:
                status = "Open";
                break;
            case 2:
                status = "Closed";
                break;
            case 3:
                status = "Closed";
                break;
            default:
                std::cout << "Not an option! Try again.\n";
                continue;
        }
        break;
    }

    std::string tempProductID = generateRandomProductID();      // generate a random product id

    Product newProduct(tempProductID, productName, productDescription, basePrice, productQuality, sellerID);

    newProduct.setId(tempProductID);

    newProduct.setCurrentBid(basePrice);

    // add product to the auction house
    auto auctionHouse = AuctionHouse::getInstance();
    auctionHouse->addProduct(newProduct);

    Bid initialBid("BidID", newProduct.getId(), this->getUserId(), basePrice, basePrice);
    auctionHouse->addBid(initialBid);

    // update bids.csv
    std::string filePath = "../CSV/bids.csv";
    std::ofstream outFile(filePath, std::ios::app);     // open the file

    if (outFile) 
    {
        std::string qualityString;
        switch (productQuality)         // switch statement to get the quality of the product
        {   
            case ProductQuality::New:
                qualityString = "New";
                break;
            case ProductQuality::Used_VeryGood:
                qualityString = "Used - Very Good";
                break;
            case ProductQuality::Used_Good:
                qualityString = "Used - Good";
                break;
            case ProductQuality::Used_Okay:
                qualityString = "Used - Okay";
                break;
        }

        // write to the file
        outFile << tempProductID << "," << productName << "," << productDescription << "," << basePrice << "," << qualityString << "," << status << "," << sellerID << "\n";
        std::cout << "Product added to CSV file.\n" << std::endl;
    }

    else        // if sfailed to open
    {
        std::cerr << "Failed to open " << filePath << std::endl;
    }
}

// =============================================================================== ADD TO SOLD LIST ====================================================================

// void Seller::addToSoldList(const std::string& productId, const std::string& buyerId)
// {
//     AuctionHouse* auctionHouse = AuctionHouse::getInstance();
//     auctionHouse->closeBid(productId, this->getUserId(), buyerId);
// }