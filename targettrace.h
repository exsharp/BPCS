#ifndef TARGETTRACE_H
#define TARGETTRACE_H
//跟踪

#include <opencv2/opencv.hpp>
#include <math.h>
#include <list>

class TargetStatus{
    //一个跟踪的目标对应一个这个类的实例化
    //若完成一次“跨越”的状态，就析构这个类？这个方法待定
public:
    TargetStatus(CvRect const &rect);
    enum Status{
        up,//表示在标线上
        down,//表示在标线下
        none,
    };
    int getCenterX(){
        return center_x;
    }
    int getCenterY(){
        return center_y;
    }
    int getDistance(int x,int y);

    static int radius;//两个对象之间的半径相隔这么多则认为是同一个对象
    friend bool operator & (TargetStatus const &ts1,TargetStatus const &ts2){
        double tmp = pow(double(ts1.center_x-ts2.center_x),2)\
                +pow(double(ts2.center_y-ts2.center_y),2);
        double distance = sqrt(tmp);
        if (distance > radius){
            //ts1与ts2相距在radius外
            return false;
        }else{
            return true;
        }

    }

private:
    //表明这个目标所在的地方
    int center_x;
    int center_y;

    Status status_init;//最开始出现目标时候的状态
    Status status_now;//目标最新跟踪到的状态

    int mark;

    friend class TargetTrace;
};

class TargetTrace
{
public:
    TargetTrace(int threshold);

    //返回值正数表示增加的人数，负数表示减少的人数，0不变
    int refresh(std::vector<CvRect> &rects);

private:
    int boundary_top; //坐标的上边界
    int boundary_button; //坐标的下边界

    int threshold; //判断通过的坐标

    std::vector<TargetStatus> targets;

private:
    int count();
};

#endif // TARGETTRACE_H
