#include "./GraphView.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#include <cstdlib>

#include "MainWindow.h"

GraphView::GraphView(QWidget *parent)
        : QMainWindow(parent)
        , parent_(dynamic_cast<MainWindow *>(parent)) {
    setFocus();
}


void GraphView::paintEvent(QPaintEvent *) {
    QPainter p;
    p.begin(this);
    p.drawLine(0, 0, 100, 100);
    p.end();
}