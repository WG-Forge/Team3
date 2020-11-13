#ifndef TEAM3_GRAPHVIEW_H
#define TEAM3_GRAPHVIEW_H

#include <QMainWindow>

#include <vector>


class MainWindow;

class GraphView : public QMainWindow {
public:
    explicit GraphView(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent*) override;

    template <typename T>
    void DrawPlayingObject(QPainter* p, const T& objects) {
        for (const auto& object : objects) {
            object.Draw(p);
        }
    }


private:
    MainWindow* parent_;
};


#endif //TEAM3_GRAPHVIEW_H
