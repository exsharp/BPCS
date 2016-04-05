#ifndef UTIL_H
#define UTIL_H

#include <QImage>
#include <opencv2/opencv.hpp>

QImage *IplImageToQImage(const IplImage *img);
IplImage *QImageToIplImage(const QImage *qImage);

#endif // UTIL_H
