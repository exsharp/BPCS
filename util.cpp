#include "util.h"

QImage *IplImageToQImage(const IplImage *img)
{
    QImage *image;
    cvCvtColor(img,img,CV_BGR2RGB);
    uchar *imgData=(uchar *)img->imageData;
    image=new QImage(imgData,img->width,img->height,QImage::Format_RGB888);
    return image;
}

IplImage *QImageToIplImage(const QImage *qImage)
{
    int width = qImage->width();
    int height = qImage->height();
    CvSize Size;
    Size.height = height;
    Size.width = width;
    IplImage *IplImageBuffer = cvCreateImage(Size, IPL_DEPTH_8U, 3);
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            QRgb rgb = qImage->pixel(x, y);
            cvSet2D(IplImageBuffer, y, x, CV_RGB(qRed(rgb), qGreen(rgb), qBlue(rgb)));
        }
    }
    return IplImageBuffer;
}

