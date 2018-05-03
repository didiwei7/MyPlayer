#include "video.h"

//#include <SDL.h>
// #undef main
#include <Windows.h>

Video::Video(QWidget *parent) : QWidget(parent)
{
    // setPlayer();
    setupUi();
    setConnect();
}

void Video::setupUi()
{
    // 【1】 导航栏
    vnavigationbar = new QVNavigationBar(this);
    vnavigationbar->setSelectColor("#FFC0CB");
    vnavigationbar->setRowHeight(30);
    vnavigationbar->setWidth(80);
    vnavigationbar->addItem(QStringLiteral("打开"));
    vnavigationbar->addItem(QStringLiteral("保存"));

    wplayer = new QGraphicsView(this);
    wplayer->setMouseTracking(true);
    wplayer->setAcceptDrops(true);
    wplayer->setStyleSheet(QStringLiteral("border:none; background:black;"));
    wplayer->setLineWidth(0);
    wplayer->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    wplayer->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    wplayer->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
    wplayer->setDragMode(QGraphicsView::NoDrag);

    player = new AVPlayer(this);
    videoItem = new GraphicsItemRenderer();
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addItem(videoItem);
    wplayer->setScene(scene);
    player->setRenderer(videoItem);

    wplaylist = new QListView(this);

    // 【2】 布局
    QHBoxLayout *layout_1   = new QHBoxLayout();
    layout_1->setContentsMargins(0, 0, 0, 0);
    layout_1->setSpacing(0);

    layout_1->addWidget(wplayer);
    layout_1->addWidget(wplaylist);
    layout_1->addWidget(vnavigationbar);

    this->setLayout(layout_1);
}

void Video::setPlayer()
{


}

void Video::setConnect()
{
    connect(vnavigationbar, &QVNavigationBar::currentItemChanged,
            this,           &Video::navitionbarChanged);
}



void Video::navitionbarChanged(const int &currentIndex)
{
    // 用if速度更快
    if (0 == currentIndex) // 打开
    {
        nopen();
    }
    else if (1 == currentIndex) // 保存
    {
        nsave();
    }
    else
    {
        return;
    }
}

void Video::nopen()
{
    const QStringList movieSysPaths = QStandardPaths::standardLocations(QStandardPaths::MoviesLocation);
    QString moviePath = QFileDialog::getOpenFileName(NULL, QStringLiteral("Open File"),
                            movieSysPaths.isEmpty() ? QDir::homePath() : movieSysPaths.first(),
                            QStringLiteral("Movie files (*.rmvb *.rm *.avi *.flv) ;; All files (*.*)"));
    if(moviePath.isEmpty())
    {
        return;
    }
    else
    {
        player->play(moviePath);
    }
}


void Video::nsave()
{
    qDebug() << "Save triggered";
}



void Video::open(QString path)
{
//    player->play(path);
//    addHistory(path);
//    CP->ui->pushButtonPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
//    setWindowTitle(QFileInfo(path).fileName());
//    ui->tableWidget->hide();
}

void Video::addHistory(QString url)
{
//    QAction *action = new QAction(url, this);
//    action->setData(url);
//    ui->menu_history->addAction(action);
//    connect(action,SIGNAL(triggered(bool)),this,SLOT(openHistory(bool)));
}
