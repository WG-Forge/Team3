#include "MainWindow.h"

#include <QDebug>
#include <QFileDialog>
#include <iostream>

#include "view/GraphView.h"
#include "drawing/Circle.h"
#include "drawing/Point.h"
#include "drawing/Line.h"
#include "drawing/ClassicalDrawingStrategy.h"
#include "builder/JSONReader.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui_(std::make_unique<Ui::MainWindow>())
        , graphView_(std::make_unique<GraphView>(this)) {
    ui_->setupUi(this);
    ui_->verticalLayout->addWidget(graphView_.get());

    ui_->styleBox->addItem("Classical");
    ui_->styleBox->addItem("Minimalism");
}

void MainWindow::on_load_graph_clicked() {
    QString fileName = QFileDialog::getOpenFileName(
                                        this,
                                        tr("Load graph"),
                                        "../graphsJSON",
                                        tr("Graph (*.json)"));
    //std::cout << fileName.toStdString();
    if (!fileName.isEmpty()) {
        std::unique_ptr<Graph> graph = std::make_unique<Graph>(1, "map01");
        graph->addNode(std::make_shared<Node>(1, 2));
        graph->addNode(std::make_shared<Node>(2, 3));
        graph->addEdge(std::make_unique<Edge>(1, 5,
                                              graph->nodes[0], graph->nodes[1]));
        graph->addEdge(std::make_unique<Edge>(2, 5,
                                              graph->nodes[0], graph->nodes[1]));
        graph->addEdge(std::make_unique<Edge>(3, 5,
                                              graph->nodes[0], graph->nodes[1]));
        graph->addEdge(std::make_unique<Edge>(4, 5,
                                              graph->nodes[0], graph->nodes[1]));
        graph->nodes[0]->setShape(std::make_unique<Circle>(Point(50, 50), 10));
        graph->nodes[1]->setShape(std::make_unique<Circle>(Point(100, 100), 20));
        graph->edges[0]->setShape(std::make_unique<Line>(Point(220, 50), Point(350, 100)));
        graph->edges[1]->setShape(std::make_unique<Line>(Point(20, 300), Point(150, 300)));
        graph->edges[2]->setShape(std::make_unique<Line>(Point(40, 10), Point(40, 100)));
        graph->edges[3]->setShape(std::make_unique<Line>(Point(400, 400), Point(420, 350)));
        //std::unique_ptr<Graph> graph = JSONReader::readGraph(fileName.toStdString());
        graphView_->setGraph(std::move(graph));
        graphView_->update();
    }
}

void MainWindow::on_styleBox_currentIndexChanged(int index) {
    switch (index) {
        case minimalism:
            graphView_->setStrategy(std::make_unique<MinimalisticDrawingStrategy>());
            break;
        case classical:
            graphView_->setStrategy(std::make_unique<ClassicalDrawingStrategy>());
            break;
    }
    graphView_->update();
}

void MainWindow::on_exit_clicked() {
    QApplication::exit(0);
}
