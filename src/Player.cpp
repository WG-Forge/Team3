#include <Player.h>

const std::string& Player::getName() const {
    return name_;
}

const std::string& Player::getPassword() const {
    return password_;
}

const std::string& Player::getIdx() const {
    return idx_;
}

uint32_t Player::getRating() const {
    return rating_;
}

bool Player::isMe() const {
    return isMe_;
}

void Player::setName(const std::string& name) {
    name_ = name;
}

void Player::setPassword(const std::string& password) {
    password_ = password;
}

void Player::setIdx(const std::string& idx) {
    idx_ = idx;
}

void Player::setOwner(bool isMe) {
    isMe_ = isMe;
}

void Player::setRating(uint32_t rating) {
    rating_ = rating;
}

void Player::setupPlayer(const std::string &name, const std::string &idx, bool isMe, uint32_t rating,
                         const std::string &password) {
    name_ = name;
    idx_ = idx;
    isMe_ = isMe;
    rating_ = rating;
    password_ = password;
}
