#ifndef TEAM3_CAMERA_H
#define TEAM3_CAMERA_H

#include <memory>
#include <cmath>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Camera {
private:
    int moveStep_ = 5;
    double zoomStep_ = 0.1;
    int maxHeight_;
    int minHeight_ = 50;
    std::unique_ptr<sf::View> camera_;
    sf::FloatRect bounds_;
    double moveOutLimitPortion_ = 0.3;
    int getLimitedOffset(int currentPosition, int offset, int size);
public:
    Camera(sf::FloatRect bounds);
    void zoom(double zoom, int x, int y, sf::RenderWindow* window);
    void zoomIn(int x, int y, sf::RenderWindow* window);
    void zoomOut(int x, int y, sf::RenderWindow* window);
    void moveLeft(int offset);
    void moveRight(int offset);
    void moveUp(int offset);
    void moveDown(int offset);
    sf::View* getView();
    int getMoveStep() const;
};


#endif //TEAM3_CAMERA_H
