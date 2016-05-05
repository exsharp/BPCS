#ifndef CODEBOOK_H
#define CODEBOOK_H

#include <opencv2/opencv.hpp>

#define CHANNELS 3 // 设置处理的图像通道数,要求小于等于图像本身的通道数
#define GATE_VALUE_CHANNELS 20 // 用于确定码元各通道的阀值
#define GATE_VALUE_MIN_MOD 20  // 用于背景差分函数中
#define GATE_VALUE_MAX_MOD 70  // 调整其值以达到最好的分割

/////////////////////////////////////////////////
// 下面为码本码元的数据结构
// 处理图像时每个像素对应一个码本,每个码本中可有若干个码元
typedef struct ce {
    uchar   learnHigh[CHANNELS];  // 此码元各通道的阀值上限(学习界限)
    uchar   learnLow[CHANNELS];   // 此码元各通道的阀值下限
    // 学习过程中如果一个新像素各通道值x[i],均有 learnLow[i]<=x[i]<=learnHigh[i],则该像素可合并于此码元
    uchar   max[CHANNELS];  // 属于此码元的像素中各通道的最大值
    uchar   min[CHANNELS];  // 属于此码元的像素中各通道的最小值
    int     t_last_update;  // 此码元最后一次更新的时间,每一帧为一个单位时间,用于计算stale
    int     stale;   // 此码元最长不更新时间,用于删除规定时间不更新的码元,精简码本
}code_element; // 码元的数据结构

typedef struct code_book {
    code_element    **cb;
    // 码元的二维指针,理解为指向码元指针数组的指针,
    // 使得添加码元时不需要来回复制码元,只需要简单的指针赋值即可
    int numEntries;  // 此码本中码元的数目
    int t;  // 此码本现在的时间,一帧为一个时间单位
}codeBook;

int cvupdateCodeBook(uchar *p, codeBook &c, unsigned *cbBounds, int numChannels);
uchar cvbackgroundDiff(uchar *p, codeBook &c, int numChannels, int *minMod, int *maxMod);
int cvclearStaleEntries(codeBook &c);

class CodeBook{

private:
    //需要用到的变量
    codeBook* cB;
    int nChannels;
    unsigned cbBounds[CHANNELS];
    int minMod[CHANNELS];
    int maxMod[CHANNELS];
    CvSize size;
    int imageLen;

    //Tmp values

public:
    CodeBook(CvSize size);
    ~CodeBook();

    int learn(IplImage* rawImage); //学习，一次学习一帧
    int clear();
    int Diff(IplImage* rawImage,IplImage* &ImaskCodeBook);
    CvSize getSize();
};

#endif // CODEBOOK_H
