#pragma once

#include <memory>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Camera {
private:
    float moveStep_ = 5;
    float zoomStep_ = 0.1;
    int32_t maxHeight_;
    int32_t minHeight_ = 50;
    std::unique_ptr<sf::View> camera_;
    sf::FloatRect bounds_;
    float moveOutLimitPortion_ = 0.3;
    float getLimitedOffset(float currentPosition, int32_t offset, int32_t size) const;
public:
    explicit Camera(sf::FloatRect bounds);
    void zoom(float zoom, int32_t x, int32_t y, sf::RenderWindow* window);
    void zoomIn(int32_t x, int32_t y, sf::RenderWindow* window);
    void zoomOut(int32_t x, int32_t y, sf::RenderWindow* window);
    void moveLeft(int32_t offset);
    void moveRight(int32_t offset);
    void moveUp(int32_t offset);
    void moveDown(int32_t offset);
    sf::View* getView();
    float getMoveStep() const;
};

