#ifndef TEAM3_CAMERA_H
#define TEAM3_CAMERA_H

#include <memory>
#include <SFML/Graphics/View.hpp>

class Camera {
private:
    int moveStep = 10;
    double zoomStep = 0.1;
    int maxHeight = 750;
    int minHeight = 150;
    std::unique_ptr<sf::View> camera_;
    sf::FloatRect bounds_;
public:
    enum Sign {
        PLUS = 1,
        MINUS = -1,
    };
    Camera(sf::FloatRect bounds);
    void zoom(double direction);
    void move(double xOffset, double yOffset);
    sf::View* getView();
};


#endif //TEAM3_CAMERA_H
