#ifndef TEAM3_DRAWINGSTRATEGY_H
#define TEAM3_DRAWINGSTRATEGY_H

#include <QPainter>
#include "Point.h"

class DrawingStrategy {
protected:
    QPainter* painter_;
    QString background_;
public:
    void setPainter(QPainter* painter);
    void clearPainter();
    explicit DrawingStrategy(QString background);
    QString getBackground();
    virtual ~DrawingStrategy() {};
    virtual void drawLine(Point p1, Point p2) = 0;
    virtual void drawCircle(Point center, int r) = 0;
};

#endif //TEAM3_DRAWINGSTRATEGY_H
