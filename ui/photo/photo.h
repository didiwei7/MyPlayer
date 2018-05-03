#ifndef PHOTO_H
#define PHOTO_H

#include <QtWidgets>
#include <QWidget>

#include <QtConcurrent>
#include <QFile>
#include <QString>
#include <QDebug>

#include "qnavigationbar.h"
#include "qmyslider.h"

#include "opencv2/opencv.hpp"

using namespace cv;

class Photo : public QWidget
{
    Q_OBJECT
public:
    explicit Photo(QWidget *parent = 0);


private:
    void setupUi();
    void setConnect();

private:
    void setEdgeDetection();
    void updateEdgeDetection();
    void on_openFile();
    void show_cvImg_to_label(Mat img);

private:
    QVNavigationBar *vnavigationbar;
    QStackedWidget  *stackedWidget;
    QLabel          *label_pic;

private:
    QWidget   *w_EdgeDetection;
    QMySlider *slider_burl;
    QMySlider *slider_canny_threshold1;
    QMySlider *slider_canny_threshold2;
    QCheckBox *btn_canny;
    QPushButton *btn_openfile;
    Mat img_src;
    QImage img_show_src;
};

#endif // PHOTO_H
