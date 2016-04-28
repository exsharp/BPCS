#ifndef PARTITION_H
#define PARTITION_H
//分割

#include <opencv2/opencv.hpp>

#include <list>

struct PParams{
    int wide;
    int high;
};

class Partition
{
public:
    Partition(PParams pparams);
    std::vector<CvRect> GetBoundingRect(IplImage *src);

private:
    int wide;
    int high;

    int area;

};

#endif // PARTITION_H
