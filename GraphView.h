#ifndef TEAM3_GRAPHVIEW_H
#define TEAM3_GRAPHVIEW_H

#include <QMainWindow>

#include <vector>
#include "Graph.h"


class MainWindow;

class GraphView : public QMainWindow {
public:
    explicit GraphView(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent*) override;
    void setGraph(std::unique_ptr<Graph> graph);
private:
    MainWindow* parent_;
    std::unique_ptr<Graph> graph_;
};


#endif //TEAM3_GRAPHVIEW_H
