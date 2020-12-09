#pragma once

#include <string>

class Player {
private:
    std::string name_;
    std::string password_;
    std::string idx_;
    bool isMe_;
    uint32_t rating_;

public:
    const std::string& getName() const;
    const std::string& getPassword() const;
    const std::string& getIdx() const;
    uint32_t getRating() const;

    bool isMe() const;

    void setName(const std::string& name);
    void setPassword(const std::string& password);
    void setIdx(const std::string& idx);
    void setOwner(bool isMe);
    void setRating(uint32_t rating);

    void setupPlayer(const std::string& name, const std::string& idx,
                     bool isMe, uint32_t rating, const std::string& password = "");
};
