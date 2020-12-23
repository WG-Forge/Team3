#include <Player.h>

#include <utility>

Player::Player(std::string name, std::string idx, uint32_t rating, bool isMe) :
               name_(std::move(name)), idx_(std::move(idx)), isMe_(isMe) {
    rating_ = rating;
}

const std::string& Player::getName() const {
    return name_;
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

void Player::setRating(uint32_t rating) {
    rating_ = rating;
}
