#ifndef CONTROLER_H
#define CONTROLER_H

#include <opencv2/opencv.hpp>
#include <string>

#include "util.h"
#include "partition.h"
#include "CodeBook.h"
#include "targettrace.h"

using std::string;
using std::cout;
using std::endl;

class Controler
{
public:
    // !!!!!暂时是固定参数的
    Controler(string fileCapturePath);
    ~Controler();
    void Learn();
    void QueryRawFrame(IplImage **_rawFrame);
    void QueryMaskImg(IplImage *&ImaskCodeBook);
    int GetPassagerNumber();
    int Trace();


private:
    //TODO
    //获得原始图像
    //
    CvSize captureSize;

    CvCapture* capture; //摄像头数据
    IplImage* rawImage; //摄像头获得的原始画面

    // 编码本算法类，区分前后景
    CodeBook* cb;

    // 目标跟踪类
    TargetTrace* trace;

    int passagerNumber;

private:
    //参数集合
    //目标分割参数
    PParams pparams;

private:

};

#endif // CONTROLER_H
