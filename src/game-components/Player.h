#pragma once

#include <string>

class Player {
private:
    const std::string name_;
    const std::string idx_;
    const bool isMe_;
    uint32_t rating_;

public:
    Player(std::string name, std::string idx, uint32_t rating, bool isMe = false);

    const std::string& getName() const;
    const std::string& getIdx() const;
    uint32_t getRating() const;

    bool isMe() const;

    void setRating(uint32_t rating);
};
