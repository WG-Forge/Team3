#pragma once

#include <memory>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Camera {
private:
    int32_t moveStep_ = 5;
    double zoomStep_ = 0.1;
    int32_t maxHeight_;
    int32_t minHeight_ = 50;
    std::unique_ptr<sf::View> camera_;
    sf::FloatRect bounds_;
    double moveOutLimitPortion_ = 0.3;
    int32_t getLimitedOffset(int32_t currentPosition, int32_t offset, int32_t size);
public:
    Camera(sf::FloatRect bounds);
    void zoom(double zoom, int32_t x, int32_t y, sf::RenderWindow* window);
    void zoomIn(int32_t x, int32_t y, sf::RenderWindow* window);
    void zoomOut(int32_t x, int32_t y, sf::RenderWindow* window);
    void moveLeft(int32_t offset);
    void moveRight(int32_t offset);
    void moveUp(int32_t offset);
    void moveDown(int32_t offset);
    sf::View* getView();
    int32_t getMoveStep() const;
};

