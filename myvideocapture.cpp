#include "myvideocapture.h"
#include <QDebug>

std::string gstreamer_pipeline(int capture_width, int capture_height, int framerate, int display_width, int display_height) {
    return
            " libcamerasrc ! video/x-raw, "
            " width=(int)" + std::to_string(capture_width) + ","
            " height=(int)" + std::to_string(capture_height) + ","
            " framerate=(fraction)" + std::to_string(framerate) +"/1 !"
            " videoconvert ! videoscale !"
            " video/x-raw,"
            " width=(int)" + std::to_string(display_width) + ","
            " height=(int)" + std::to_string(display_height) + " ! appsink";
}

MyVideoCapture::MyVideoCapture(QObject *parent)
    :QThread { parent }
{
    //pipeline parameters
    int capture_width = 640; //1280 ;
    int capture_height = 480; //720 ;
    int framerate = 15 ;
    int display_width = 640; //1280 ;
    int display_height = 480; //720 ;

    //reset frame average
    std::string pipeline = gstreamer_pipeline(capture_width, capture_height, framerate,
                                              display_width, display_height);

    //  Raspberry Pi Bullseye
    mVideoCap.open(pipeline, cv::CAP_GSTREAMER);

    //  Raspberry Pi Buster or Jetson Nano
//  mVideoCap.open( ID_CAMERA );
}

void MyVideoCapture::run()
{
    if(mVideoCap.isOpened())
    {
        while (true)
        {
            mVideoCap >> mFrame;
            if(!mFrame.empty())
            {
                mPixmap = cvMatToQPixmap(mFrame);
                emit newPixmapCapture();
            }
        }
    }
}

QImage MyVideoCapture::cvMatToQImage( const cv::Mat &inMat )
{
  switch ( inMat.type() )
  {
     // 8-bit, 4 channel
     case CV_8UC4:
     {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_ARGB32 );

        return image;
     }

     // 8-bit, 3 channel
     case CV_8UC3:
     {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_RGB888 );

        return image.rgbSwapped();
     }

     // 8-bit, 1 channel
     case CV_8UC1:
     {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Grayscale8 );
#else
        static QVector<QRgb>  sColorTable;

        // only create our color table the first time
        if ( sColorTable.isEmpty() )
        {
           sColorTable.resize( 256 );

           for ( int i = 0; i < 256; ++i )
           {
              sColorTable[i] = qRgb( i, i, i );
           }
        }

        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Indexed8 );

        image.setColorTable( sColorTable );
#endif

        return image;
     }

     default:
        qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
  }

  return QImage();
}
QPixmap MyVideoCapture::cvMatToQPixmap( const cv::Mat &inMat )
{
  return QPixmap::fromImage( cvMatToQImage( inMat ) );
}
