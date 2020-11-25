#ifndef MYVIDEOCAPTURE_H
#define MYVIDEOCAPTURE_H

#include <QPixmap>
#include <QImage>
#include <QThread>
#include <opencv2/opencv.hpp>

#define ID_CAMERA 0

class MyVideoCapture : public QThread
{
    Q_OBJECT
public:
    MyVideoCapture(QObject *parent = nullptr);
    QPixmap pixmap() const
    {
        return mPixmap;
    }
signals:
    void newPixmapCapture(); //capture a frame
protected:
    void run() override;
private:
    QPixmap mPixmap;              //Qt image
    cv::Mat mFrame;               //OpenCV image
    cv::VideoCapture mVideoCap;   //video capture

    QImage cvMatToQImage(const cv::Mat &inMat);
    QPixmap cvMatToQPixmap(const cv::Mat &inMat );
};

#endif // MYVIDEOCAPTURE_H
