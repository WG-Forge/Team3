#include "DrawingStrategy.h"

void DrawingStrategy::setPainter(QPainter* painter) {
    painter_ = painter;
}

void DrawingStrategy::clearPainter() {
    painter_ = nullptr;
}

