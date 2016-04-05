#include "util.h"

QImage *IplImageToQImage(const IplImage *img)
{
    //std::cout<<img->width<<" "<<img->height<<std::endl;
    IplImage *dst;
    if (img){
        dst = cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
        cvCvtColor(img,dst,CV_BGR2RGB);
    }else{
        CvSize size;
        size.height=10;
        size.width=10;
        dst = cvCreateImage(size,8,3);
    }
    uchar *imgData=(uchar *)dst->imageData;
    QImage *image=new QImage(imgData,dst->width,dst->height,QImage::Format_RGB888);
    //cvReleaseImage(&dst);
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

