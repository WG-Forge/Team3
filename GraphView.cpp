#include "./GraphView.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#include "MainWindow.h"

GraphView::GraphView(QWidget *parent)
        : QMainWindow(parent)
        , parent_(dynamic_cast<MainWindow *>(parent)) {
    setFocus();
}


void GraphView::paintEvent(QPaintEvent *) {
    QPainter p;
    p.begin(this);
    p.drawLine(20, 20, 120, 120);
    p.drawLine(120, 20, 20, 120);
    p.drawLine(240, 20, 120, 120);
    p.end();
}

void GraphView::setGraph(std::unique_ptr<Graph> graph) {
    graph_ = std::unique_ptr<Graph>(std::move(graph));
}
