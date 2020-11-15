#include "MainWindow.h"

#include <QDebug>
#include <QFileDialog>
#include <iostream>

#include "view/GraphView.h"
#include "drawing/Circle.h"
#include "drawing/Point.h"
#include "drawing/Line.h"
#include "builder/JSONReader.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui_(std::make_unique<Ui::MainWindow>())
        , graphView_(std::make_unique<GraphView>(this)) {
    ui_->setupUi(this);
    ui_->verticalLayout->addWidget(graphView_.get());

    ui_->styleBox->addItem("Summer");
    ui_->styleBox->addItem("Minimalism");
}

void MainWindow::on_load_graph_clicked() {
    QString fileName = QFileDialog::getOpenFileName(
                                        this,
                                        tr("Load graph"),
                                        "../graphsJSON",
                                        tr("graph (*.json)"));
//    std::cout << fileName.toStdString();
//    std::unique_ptr<Graph> graph = std::make_unique<Graph>(1, "map01");
//    graph->addNode(std::make_shared<Node>(1, 2));
//    graph->addNode(std::make_shared<Node>(2, 3));
//    graph->addEdge(std::make_unique<Edge>(1, 5,
//                                          graph->nodes[0], graph->nodes[1]));
//    graph->nodes[0]->setShape(std::make_unique<Circle>(Point(10, 10), 10));
//    graph->nodes[1]->setShape(std::make_unique<Circle>(Point(100, 100), 20));
//    graph->edges[0]->setShape(std::make_unique<Line>(Point(20, 10), Point(150, 100)));
    std::unique_ptr<Graph> graph = JSONReader::readGraph(fileName.toStdString());
//    std::cout << graph->nodes[0]->idx_;
    graphView_->setGraph(std::move(graph));
//    graphView_->update();
}

void MainWindow::on_styleBox_currentTextChanged(const QString &text) {
    //std::cout << text.toStdString() << std::endl;
    graphView_->setStrategy(std::make_unique<MinimalisticDrawingStrategy>());
    graphView_->update();
}

void MainWindow::on_exit_clicked() {
    QApplication::exit(0);
}
