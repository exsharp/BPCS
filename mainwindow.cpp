#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include "util.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // connect(&theTimer, &QTimer::timeout, this, &MainWindow::updateImage);
    connect(&theTimer, SIGNAL(timeout()), this, SLOT(updateImage()));

    capture = cvCreateFileCapture("../BusPassagerCountingSystem/clip.mp4");
    if (!capture){
        qDebug()<<"Can't createFileCapture"<<endl;

    }
    theTimer.start(33);
    imageLabel = new QLabel(this);
    ui->verticalLayout->addWidget(imageLabel);

    iplImage = NULL;
    qImage = new QImage;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    qDebug()<<"printEvent";
    imageLabel->setPixmap(QPixmap::fromImage(*qImage));
    imageLabel->resize((*qImage).size());
    imageLabel->show();
}

void MainWindow::updateImage()
{
    qDebug()<<"updateImage";
    iplImage = cvQueryFrame(capture);
    qDebug()<<iplImage->width<<"  "<<iplImage->height<<endl;
    if (iplImage){
        qImage = IplImageToQImage(iplImage);
        this->update();
    }
}
