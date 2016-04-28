#include "controler.h"

Controler::Controler(string fileCapturePath)
{

#ifdef Q_OS_WIN32
    capture = cvCreateFileCapture("D:/WorkSpace/BPCS/clip2.mp4");
#elif defined(Q_OS_LINUX)
    capture = cvCreateFileCapture("../BusPassagerCountingSystem/clip2.mp4");
#endif

    if (!capture){
        std::cout<<"Open file failed"<<std::endl;
    }

    rawImage = cvQueryFrame(capture);
    cout<<rawImage->width<< " " <<rawImage->height<<endl;

    captureSize = cvGetSize(rawImage);

    cb = new CodeBook(captureSize);
    trace = new TargetTrace(150);

    passagerNumber = 0;

    pparams.wide = 200;
    pparams.high = 200;
}

Controler::~Controler()
{
    delete cb;
    delete trace;
    cvReleaseCapture(&capture);
}

void Controler::QueryRawFrame(IplImage **_rawFrame)
{
    //TODO 错误处理
    if (!(rawImage = cvQueryFrame(this->capture))){
        assert(false);
    }
    //cout<<rawImage->width<< " " <<rawImage->height<<endl;
    *_rawFrame = cvCreateImage(captureSize,rawImage->depth,rawImage->nChannels);
    cvCopy(rawImage,*_rawFrame);
    //_rawFrame = rawImage;
}

int Controler::GetPassagerNumber()
{
    return passagerNumber;
}

int Controler::Trace()
{
    IplImage* ImaskCodeBook;
    ImaskCodeBook = cvCreateImage(captureSize,IPL_DEPTH_8U,1);
    // 为ImaskCodeBook 分配一个和rawImage 尺寸相同,8位单通道图像
    cb->Diff(rawImage,ImaskCodeBook);

    //这个参数有待调整
    Partition partition(pparams);
    std::vector<CvRect> rects = partition.GetBoundingRect(ImaskCodeBook);
    int ret = trace->refresh(rects);
    passagerNumber += ret;
    if (ret!=0){
        cout<<passagerNumber<<" "<<ret<<endl<<endl;
    }
    cvReleaseImage(&ImaskCodeBook);
    return passagerNumber;
}

void Controler::QueryMaskImg(IplImage *&ImaskCodeBook)
{
    ImaskCodeBook = cvCreateImage(captureSize,IPL_DEPTH_8U,1);
    // 为ImaskCodeBook 分配一个和rawImage 尺寸相同,8位单通道图像
    cb->Diff(rawImage,ImaskCodeBook);

    IplImage* clone;
    clone = cvCreateImage(captureSize,IPL_DEPTH_8U,1);
    cvCopy(ImaskCodeBook,clone);

    //这个参数有待调整
    Partition partition(pparams);
    std::vector<CvRect> rects = partition.GetBoundingRect(clone);

    for (int i = 0;i<rects.size();i++){
        CvRect rc = rects[i];
        TargetStatus ts(rc);
        cvDrawRect(ImaskCodeBook, cvPoint(rc.x, rc.y), cvPoint(rc.x + rc.width, rc.y + rc.height), CV_RGB(255, 255, 255));
    }
    cvReleaseImage(&clone);
}

void Controler::Learn()
{
    //最开始初始化CodeBook的时候浪费了一帧

    //学习的帧数暂时固定成30
    cb->learn(rawImage);
    for (int i = 0;i<30;i++){
        rawImage = cvQueryFrame(capture);
        cb->learn(rawImage);
        cout<<"learn:"<<i<<endl;
    }
    cb->clear();
}
