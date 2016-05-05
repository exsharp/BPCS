#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>

#include "controler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateImage();

private:
    QTimer theTimer;
    QLabel *imageLabel;
    IplImage *iplImage;

    Ui::MainWindow *ui;

    Controler *ctrler;


protected:
    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H
