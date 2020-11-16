#include "DrawingStrategy.h"

void DrawingStrategy::setPainter(QPainter* painter) {
    painter_ = painter;
}

void DrawingStrategy::clearPainter() {
    painter_ = nullptr;
}

DrawingStrategy::DrawingStrategy(QString background)
                    : background_(background) {}

QString DrawingStrategy::getBackground() {
    return background_;
}

