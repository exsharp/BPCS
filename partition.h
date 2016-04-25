#ifndef PARTITION_H
#define PARTITION_H

#include <opencv2/opencv.hpp>

#include <list>

class Partition
{
public:
    Partition(int wide,int high);
    std::vector<CvRect> GetBoundingRect(IplImage *src);

private:
    int wide;
    int high;

    int area;

};

#endif // PARTITION_H
