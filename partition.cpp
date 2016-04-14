#include "partition.h"

Partition::Partition(int wide, int high)
{
    this->wide = wide;
    this->high = high;

    this->area = wide*high;
}

std::list<CvRect> Partition::GetBoundingRect(IplImage *src){
    std::list<CvRect> ret;

    cvErode(src,src);
    //先做一下形态学腐蚀，花费时间未知

    CvSeq* contours = NULL;
    CvMemStorage* storage = cvCreateMemStorage(0);

    cvFindContours(src, storage, &contours,sizeof(CvContour),CV_RETR_EXTERNAL);
    //返回找到的个数

    for (CvSeq* c = contours; c != NULL; c = c->h_next) {
        CvRect rc =cvBoundingRect(c,0);
        if ((rc.width*rc.height)>this->area){
            //cvDrawRect(ImaskCodeBook, cvPoint(rc.x, rc.y), cvPoint(rc.x + rc.width, rc.y + rc.height), CV_RGB(255, 255, 255));
            ret.push_back(rc);
        }
    }
    cvReleaseMemStorage(&storage);

    return ret;
}
