#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtWinExtras>
#include <QtWin>

#include <QtConcurrent>
#include <QFile>
#include <QString>
#include <QDebug>

#include "mainwidget.h"

#include "QtDockGuider.h"
#include "QtDockWidget.h"
#include "QtDockSide.h"
#include "QtDockSite.h"
#include "QtFlexHelper.h"
#include "QtFlexManager.h"
#include "QtFlexStyle.h"
#include "QtFlexWidget.h"

// 载入QFlex
//#include "../QFlex/QtDockGuider.h"
//#include "../QFlex/QtDockWidget.h"
//#include "../QFlex/QtDockSide.h"
//#include "../QFlex/QtDockSite.h"
//#include "../QFlex/QtFlexHelper.h"
//#include "../QFlex/QtFlexManager.h"
//#include "../QFlex/QtFlexStyle.h"
//#include "../QFlex/QtFlexWidget.h"

class QtGuiderImpl;
class FlexWidget;
class DockWidget;

class QtCentral : public QWidget
{
    Q_OBJECT
public:
    QtCentral(QWidget* parent);

public:
    void init_widget();
    void createOne();

private slots:
    void on_dockWidgetCreated(DockWidget *);
    void on_dockWidgetDestroying(DockWidget *);

    void on_flexWidgetCreated(FlexWidget *);
    void on_flexWidgetDestroying(FlexWidget *);

private:
    MainWidget *w_mainwidget;
    Photo      *w_photo;
    Video      *w_video;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

protected: // 重载关闭事件
    void closeEvent(QCloseEvent *event);

private:   // 读写配置
    void writeSettings();
    void readSettings();

private:   // 初始化
    void setupUi();
    void setConnect();


private:   // Action
    void setActions();
    void on_view_mainwidget();
    void on_view_video();
    void on_view_photo();

private:
    QAction        *action_file_new;
    QAction        *action_file_open;
    QAction        *action_file_save;
    QAction        *action_file_save_all;
    QAction        *action_file_exit;

    QAction        *action_view_mainwidget;
    QAction        *action_view_video;
    QAction        *action_view_photo;
    QAction        *action_view_music;

private:   // 基于Windows的附加属性
    void setExtras();

    void setDWM();
    void setTaskbar();
    void setThumbnailToolBar();
    void setJumpList();

    QWinTaskbarButton       *taskbarBtn;
    QWinTaskbarProgress     *taskbarProgress;
    QWinThumbnailToolBar    *thumbnailToolBar;
    QWinThumbnailToolButton *thumbnailBtn_playPause;
    QWinThumbnailToolButton *thumbnailBtn_previous;
    QWinThumbnailToolButton *thumbnailBtn_next;
    QWinJumpList         *jumplist;
    QWinJumpListCategory *jumplistCategory_playlist;
    QWinJumpListCategory *jumplistCategory_startUp;
    QWinJumpListCategory *jumplistCategory_folder;
};

#endif // MAINWINDOW_H
