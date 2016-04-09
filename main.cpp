//#include "mainwindow.h"
//#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
//}
#include "CodeBook.h"
#include <iostream>
#include <QDebug>
#include "util.h"
#include "integralprojection.h"

using namespace std;

int main()
{
    cvNamedWindow("Raw");
    cvNamedWindow("CodeBook");

#ifdef Q_OS_WIN32
    CvCapture* capture = cvCreateFileCapture("D:/WorkSpace/BPCS/clip.mp4");
#elif Q_OS_LINUX
    CvCapture* capture = cvCreateFileCapture("../BusPassagerCountingSystem/clip.mp4");
#endif
    if (!capture){
        cout<<"Open file failed"<<endl;
    }
    IplImage* rawImage = cvQueryFrame(capture);

    CodeBook cb(cvGetSize(rawImage));
    IntegralProjection ip(cvGetSize(rawImage));

    cb.learn(rawImage);
    for (int i = 0;i<30;i++){
        rawImage = cvQueryFrame(capture);
        cb.learn(rawImage);
        cout<<"Learn:"<<i<<endl;
    }
    cb.clear();

    for (int i = 30;;i++){
        if (!(rawImage = cvQueryFrame(capture))){
            break;
        }

        IplImage* ImaskCodeBook;
        ImaskCodeBook = cvCreateImage(cb.getSize(),IPL_DEPTH_8U,1);
        // 为ImaskCodeBook 分配一个和rawImage 尺寸相同,8位单通道图像
        cb.Diff(rawImage,ImaskCodeBook);

        ip.TEST(ImaskCodeBook);

        cvShowImage("Raw",rawImage);
        cvShowImage("CodeBook",ImaskCodeBook);

        cvReleaseImage(&ImaskCodeBook);

        if (cvWaitKey(30) == 27)
            break;
        //if (i >= 100){
        //    cvWaitKey();
        //}
    }


    cout<<"exit"<<endl;
}
