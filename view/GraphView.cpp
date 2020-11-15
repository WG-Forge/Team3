#include "./GraphView.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
//#include <iostream>

#include "../MainWindow.h"

GraphView::GraphView(QWidget *parent)
        : QMainWindow(parent)
        , parent_(dynamic_cast<MainWindow *>(parent)) {
    setFocus();
}


void GraphView::paintEvent(QPaintEvent*) {
    if (strategy_ && graph_) {
        std::unique_ptr<QPainter> p = std::make_unique<QPainter>();
        p->begin(this);
        strategy_->setPainter(p.get());
        graph_->draw(strategy_.get());
        strategy_->clearPainter();
        p->end();
    }
}

void GraphView::setGraph(std::unique_ptr<Graph> graph) {
//    std::cout << "\ni'm in set graph";
    graph_ = std::unique_ptr<Graph>(std::move(graph));
}

void GraphView::setStrategy(std::unique_ptr<DrawingStrategy> strategy) {
    strategy_ = std::move(strategy);
}
