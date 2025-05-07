#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void processFrame();

private:
    QLabel *camLabel;
    QGraphicsView *drawingView;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *handItem;

    QTimer *timer;
    cv::VideoCapture cap;
    cv::CascadeClassifier handCascade;
};

#endif // MAINWINDOW_H
