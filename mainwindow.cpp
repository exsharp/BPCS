#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QPainter>
#include <QString>

#include "controler.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // connect(&theTimer, &QTimer::timeout, this, &MainWindow::updateImage);
    connect(&theTimer, SIGNAL(timeout()), this, SLOT(updateImage()));


#ifdef Q_OS_WIN32
    string capture = "D:/WorkSpace/BPCS/clip2.mp4";
#elif defined(Q_OS_LINUX)
    //string capture = "../BusPassagerCountingSystem/clip2.mp4";

#endif
    string capture = "/home/clip2.mp4";
    ctrler = new Controler(capture);
    iplImage = ctrler->GetRawFrameAddr();
    ctrler->Learn();

    theTimer.start(33);
    imageLabel = new QLabel(this);
    ui->verticalLayout->addWidget(imageLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QImage image1 = QImage((uchar*)(iplImage->imageData), iplImage->width, iplImage->height, QImage::Format_RGB888);
    painter.drawImage(QPoint(20,20), image1);

    int a = ctrler->GetPassagerNumber();
    QString aa = QString::number(a,10);

    ui->label->setText(aa);
}

void MainWindow::updateImage()
{
    ctrler->QueryRawFrame();
    ctrler->Trace();
    cvCvtColor(iplImage,iplImage,CV_BGR2RGB);
    this->update();
}
