#include "mainwindow.h"
#include <QHBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QDebug>

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    camLabel = new QLabel(this);
    drawingView = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    drawingView->setScene(scene);
    handItem = scene->addEllipse(0, 0, 30, 30, QPen(Qt::black), QBrush(Qt::green));

    QWidget *central = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(central);
    layout->addWidget(camLabel);
    layout->addWidget(drawingView);
    setCentralWidget(central);

    cap.open(0);
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);

    if (!cap.isOpened()) {
        qDebug() << "Erreur d'ouverture caméra";
    }

    if (!handCascade.load("C:/Users/archo/OneDrive/Bureau/Cam_slice/palm.xml")) {
        qDebug() << "Erreur chargement palm.xml";
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::processFrame);
    timer->start(15);
}

MainWindow::~MainWindow() {}

void MainWindow::processFrame() {
    Mat frame, gray;
    cap >> frame;
    if (frame.empty()) return;

    flip(frame, frame, 1);
    cvtColor(frame, gray, COLOR_BGR2GRAY);

    std::vector<Rect> hands;
    handCascade.detectMultiScale(gray, hands, 1.1, 4, 0, Size(50, 50));

    // Si une main détectée : déplacer le cercle
    if (!hands.empty()) {
        const Rect &hand = hands[0];
        if (hand.width > 80 && hand.height > 80) {
            handItem->setRect(hand.x / 4, hand.y / 4, 30, 30);
        }
    }

    // Affichage webcam dans le QLabel
    QImage qimg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_BGR888);
    camLabel->setPixmap(QPixmap::fromImage(qimg));
}
