#include "Camera.h"
#include <iostream>

Camera::Camera(sf::FloatRect bounds)
                        : camera_(std::make_unique<sf::View>(bounds))
                        , bounds_(bounds) {
    camera_->zoom(1);
}

void Camera::zoom(double direction) {
    double newZoom = 1 - zoomStep * direction;
    if ((camera_->getSize().x < maxHeight && newZoom > 1) ||
            (camera_->getSize().x > minHeight && newZoom < 1)) {
        camera_->zoom(newZoom);
    }
}

void Camera::move(double xOffset, double yOffset) {

    camera_->move(xOffset * moveStep, yOffset * moveStep);
}

sf::View *Camera::getView() {
    return camera_.get();
}
