#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
//#include <iostream>
//#include <QDebug>
//#include "controler.h"

//using namespace std;

//int main(int argc,char **argv)
//{
//    cvNamedWindow("Raw");
//    cvNamedWindow("CodeBook");

//    //IplImage *img = cvLoadImage("/home/zfliu/Pictures/银河桌面图.jpg");
//    //cvShowImage("Raw",img);
//    //printf("%p",img);

//    //cvWaitKey();

//    Controler aa("aaa");
//    aa.Learn();
//    IplImage* rawImage = aa.GetRawFrameAddr();
//    IplImage* maskImage;


//    for (int i = 0;;i++){
//        //cout<<i<<endl;

//        aa.QueryRawFrame();
//        aa.QueryMaskImg(maskImage);
//        aa.Trace();

//        cvShowImage("Raw",rawImage);
//        cvShowImage("CodeBook",maskImage);
//        cvReleaseImage(&maskImage);
//        if (cvWaitKey(30) == 27)
//            break;
//    }
//    cout<<"exit"<<endl;
//}



