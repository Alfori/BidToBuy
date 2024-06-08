#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <ctime>

struct Message 
{
    std::string senderId;
    std::string recipientId;
    std::string content;
    std::time_t timestamp;

    // constructor
    Message(const std::string& senderId, const std::string& recipientId, const std::string& content)
        : senderId(senderId), recipientId(recipientId), content(content) 
        {
            timestamp = std::time(nullptr);
        }
};

#endif