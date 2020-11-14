#ifndef TEAM3_GRAPHVIEW_H
#define TEAM3_GRAPHVIEW_H

#include <QMainWindow>

#include <vector>
#include "../graph/Graph.h"
#include "../drawing/Circle.h"
#include "../drawing/Point.h"
#include "../drawing/Line.h"

class MainWindow;

class GraphView : public QMainWindow {
public:
    explicit GraphView(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent*) override;
    void setGraph(std::unique_ptr<Graph> graph);
    void setStrategy(std::unique_ptr<DrawingStrategy> strategy);
private:
    MainWindow* parent_;
    std::unique_ptr<Graph> graph_;
    std::unique_ptr<DrawingStrategy> strategy_;
};


#endif //TEAM3_GRAPHVIEW_H
