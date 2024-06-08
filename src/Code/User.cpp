#include "User.hpp"
#include "Seller.hpp"
#include "AuctionHouse.hpp"
#include "Utilities.hpp"
#include "Product.hpp"

void User::setName(const std::string& newName) 
{
    this->name = newName;
}

void User::setEmail(const std::string& newEmail) 
{
    this->email = newEmail;
}

void User::setAddress(const std::string& newAddress) 
{
    this->address = newAddress;
}

std::string User::getUserId() const 
{
    return userId;
}

std::string User::getName() const
{
    return name;
}

std::string User::getEmail() const
{
    return email;
}

std::string User::getAddress() const
{
    return address;
}

std::string User::getRole() const
{
    return role;
}

void User::setRole(const std::string& newRole)
{
    this->role = newRole;
}


// void User::accessMessaging()
// {
//     AuctionHouse* auctionHouse = AuctionHouse::getInstance();   // get instance of auction house
//     bool isRunning = true;  // set isRunning to true so it keeps loooping till its false
//     while (isRunning) 
//     {
//         std::cout << "Messaging Menu:\n";
//         std::cout << "1. View Messages\n";
//         std::cout << "2. Send Message\n";
//         std::cout << "3. Exit\n";
//         std::cout << "Choose an option: ";

//         int choice;
//         std::cin >> choice;

//         switch (choice) 
//         {
//             case 1:
//                 viewMessages();

//                 break;
//             case 2:
//                 sendMessage();
//                 break;
//             case 3:
//                 isRunning = false;
//                 std::cout << "Exiting messaging menu.\n";
//                 break;
//             default:
//                 std::cout << "Invalid choice. Please try again.\n";
//         }
//     }
// }

// void User::viewMessages() 
// {
//     AuctionHouse* auctionHouse = AuctionHouse::getInstance();
//     std::vector<Message> messages = auctionHouse->getMessagesForUser(this->getUserId());

//     std::cout << "Received Messages:\n";
    
//     for (const auto& msg : messages) 
//     {
//         std::cout << "From: " << msg.senderId << " - " << msg.content << "\n";
//     }
// }


// void User::sendMessage()
// {
//     AuctionHouse* auctionHouse = AuctionHouse::getInstance();
//     std::string recipientId, content;
//     std::cout << "Enter recipient ID: ";
//     std::cin >> recipientId;    
//     std::cin.ignore();  // have to use ignore to clear buffer
//     std::cout << "Enter message: ";
//     std::getline(std::cin, content);  // use getline to allow spaces in the messages

//     Message newMessage(this->getUserId(), recipientId, content);
//     auctionHouse->addMessage(newMessage); // add the message

//     std::cout << "Message sent.\n";
// }

// void User::updateUserInfo()
// {
//     std::string newName, newEmail, newAddress;
//     std::cout << "Enter new name: ";
//     std::getline(std::cin >> std::ws, newName);         // whitespace
//     std::cout << "Enter new email: ";
//     std::getline(std::cin, newEmail);
//     std::cout << "Enter new address: ";
//     std::getline(std::cin, newAddress);

//     // get path to cvs file
//     std::string filePath = "../CSV/users.csv";
//     std::ifstream inFile(filePath);
//     std::vector<std::string> lines;
//     std::string line;

//     // read content + updtae the user info
//     while (getline(inFile, line))
//     {
//         std::stringstream ss(line);
//         std::string tempUserId;
//         getline(ss, tempUserId, ',');

//         if (tempUserId == this->getUserId())
//         {
//             std::string restOfLine;
//             getline(ss, restOfLine);
//             // skip over next 3 using a for loop
//             std::stringstream restSS(restOfLine);
//             std::string skip;
//             for (int i = 0; i < 3; ++i) getline(restSS, skip, ','); // skip the name email and address
//             std::string remainder;
//             getline(restSS, remainder); // get rest of line
//             line = tempUserId + "," + newName + "," + newEmail + "," + newAddress + "," + remainder;    // update the line
//         }
//         lines.push_back(line);  // add the line to the vector
//     }
//     inFile.close();

//     // add the updated info to the file
//     std::ofstream outFile(filePath);
//     for (const auto& updatedLine : lines)
//     {
//         outFile << updatedLine;
//         if (&updatedLine != &lines.back())
//         {
//             outFile << std::endl;
//         }
//     }
//     outFile.close();

//     std::cout << "User info updated!" << std::endl;
// }