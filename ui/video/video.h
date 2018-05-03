#ifndef VIDEO_H
#define VIDEO_H

#include <QtWidgets>
#include <QWidget>

#include <QtConcurrent>
#include <QFile>
#include <QString>
#include <QDebug>

#include "qnavigationbar.h"
#include "QtAVWidgets/QtAVWidgets.h"
#include "QtAV/QtAV.h"
#include "QtAV/AVPlayer.h"

 using namespace  QtAV;

class Video : public QWidget
{
    Q_OBJECT
public:
    explicit Video(QWidget *parent = 0);

signals:

public slots:

private:
    void setupUi();
    void setPlayer();
    void setConnect();

private:
    void navitionbarChanged(const int &currentIndex);
    void nopen();
    void nsave();

private:
    void open(QString path);
    void addHistory(QString url);

private:
    QVNavigationBar *vnavigationbar;
    QGraphicsView   *wplayer;
    QListView       *wplaylist;

private:
    AVPlayer             *player;
    GraphicsItemRenderer *videoItem;

};

#endif // VIDEO_H
