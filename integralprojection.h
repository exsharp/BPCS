#ifndef INTEGRALPROJECTION_H
#define INTEGRALPROJECTION_H

#include <opencv2/opencv.hpp>

class IntegralProjection
{
public:
    IntegralProjection(CvSize size);
    ~IntegralProjection();
    void TEST(IplImage *iplImage);

private:
    IplImage *iplImage;
    int *vertical;
    int *horizontal;

    void Threshold();
    void Partition();

private:
    //二值化参数：
    int threshold;
    int max_value;
};

#endif // INTEGRALPROJECTION_H
