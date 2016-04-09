#include "integralprojection.h"

IntegralProjection::IntegralProjection(CvSize size)
{
    //二值化的阀值之类的东西，又是一个要调整的东西
    this->threshold = 50;
    this->max_value = 255;

    vertical = new int[size.width];
    horizontal = new int[size.height];
}

IntegralProjection::~IntegralProjection(){
    delete []vertical;
    delete []horizontal;
}

void IntegralProjection::Threshold(){

     //cvThreshold(iplImage,iplImage,threshold,max_value,CV_THRESH_BINARY);
     memset(vertical,0,sizeof(int)*iplImage->width);
     memset(horizontal,0,sizeof(int)*iplImage->height);

     int x,y;
     CvScalar s;
     for(x=0;x<iplImage->width;x++)
     {
         for(y=0;y<iplImage->height;y++)
         {
             s=cvGet2D(iplImage,y,x);
             if(s.val[0]==0)
                 vertical[x]++;
         }
     }

     for(y=0;y<iplImage->height;y++)
     {
         for(x=0;x<iplImage->width;x++)
         {
             s=cvGet2D(iplImage,y,x);
             if(s.val[0]==0)
                 horizontal[y]++;
         }
     }
}

void IntegralProjection::Partition(){

}

void IntegralProjection::TEST(IplImage *iplimage){
    this->iplImage = iplimage;

    this->Threshold();

    IplImage* paintx=cvCreateImage(cvGetSize(iplImage),IPL_DEPTH_8U, 1 );
    IplImage* painty=cvCreateImage(cvGetSize(iplImage),IPL_DEPTH_8U, 1 );
    cvZero(paintx);
    cvZero(painty);

    int x,y;
    CvScalar t;
    for(x=0;x<iplImage->width;x++)
    {
        for(y=0;y<vertical[x];y++)
        {
            t.val[0]=255;
            cvSet2D(paintx,y,x,t);
        }
    }

    for(y=0;y<iplImage->height;y++)
    {
        for(x=0;x<horizontal[y];x++)
        {
            t.val[0]=255;
            cvSet2D(painty,y,x,t);
        }
    }
    cvNamedWindow("垂直积分投影");
    cvNamedWindow("水平积分投影");
    cvShowImage("垂直积分投影",paintx);
    cvShowImage("水平积分投影",painty);
}
