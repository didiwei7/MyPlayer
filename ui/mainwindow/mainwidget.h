#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtWidgets>

#include "../photo/photo.h"
#include "../video/video.h"
#include "qnavigationbar.h"



class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);


private:
    void setupUi();
    void setConnect();

private:
    Photo *w_photo;
    Video *w_video;

private:
    QWidget         *centwidget;
    QVNavigationBar *vnavigationbar;
    QStackedWidget  *stackedWidget;
};

#endif // MAINWIDGET_H
