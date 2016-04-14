#include "targettrace.h"

int TargetStatus::radius = 100;

TargetStatus::TargetStatus(CvRect const &rect){
    this->center_x = int((rect.x+rect.width)/2);
    this->center_y = int((rect.y+rect.height)/2);
}

TargetTrace::TargetTrace(int threshold)
{
    this->threshold = threshold;
}

void TargetTrace::refresh(std::list<CvRect> rects){

    int rs = rects.size();
    int ts = targets.size();

    if (rs==ts){
        //已经存在的数量与识别出来的书香相等，可以直接一一对应
    }else if (rs>ts){
        //本次识别出来的目标多于已经识别出来的

    }else if (rs<ts){
        //与上面的相反

    }else{
        //理论上不会有这种情况发生，强迫症写上
    }
}
