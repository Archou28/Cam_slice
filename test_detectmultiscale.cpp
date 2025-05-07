#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/objdetect.hpp>

#include <cstdio>
#include <iostream>

using namespace cv;
using namespace std;

int main(int, char**)
{
    int frameWidth = 640;
    int frameHeight = 480;

    VideoCapture cap(0); // open the default camera
    cout << "width :" << cap.get(CAP_PROP_FRAME_WIDTH) << endl;
    cout << "height :" << cap.get(CAP_PROP_FRAME_HEIGHT) << endl;

    cap.set(CAP_PROP_FRAME_WIDTH, frameWidth);
    cap.set(CAP_PROP_FRAME_HEIGHT, frameHeight);

    if (!cap.isOpened()) {
        cerr << "Error opening the default camera" << endl;
        return -1;
    }

    // Charger le classifieur Haar pour la main
    CascadeClassifier hand_cascade;
    if (!hand_cascade.load("C:/Users/archo/OneDrive/Bureau/Cam_slice/palm.xml")) {
        cerr << "Error loading palm cascade" << endl;
        return -1;
    }

    // Init fenêtre de sortie
    namedWindow("WebCam", 1);

    while (waitKey(5) < 0)
    {
        Mat frame, frame_gray;
        std::vector<Rect> hands;

        cap >> frame;
        flip(frame, frame, 1); // Effet miroir

        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        // equalizeHist(frame_gray, frame_gray); // optionnel

        // Détection de la main
        hand_cascade.detectMultiScale(frame_gray, hands, 1.1, 4, 0, Size(50, 50));

        // Affichage des rectangles de détection
        for (int i = 0; i < hands.size(); i++) {
            if (hands[i].width > 80 && hands[i].height > 80) {
                rectangle(frame, hands[i], Scalar(0, 255, 0), 2);
            }
        }
        imshow("WebCam", frame);
    }


    return 0;
}
