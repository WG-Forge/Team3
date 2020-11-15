#ifndef TEAM3_MAINWINDOW_H
#define TEAM3_MAINWINDOW_H

#include <QMainWindow>

#include "ui_mainwindow.h"
#include "view/GraphView.h"
#include "drawing/MinimalisticDrawingStrategy.h"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    std::unique_ptr<Ui::MainWindow> ui_;
    std::unique_ptr<GraphView> graphView_;
    enum Style { classical, minimalism };
private slots:
    void on_load_graph_clicked();
    void on_exit_clicked();
    void on_styleBox_currentIndexChanged(int index);
};


#endif //TEAM3_MAINWINDOW_H
