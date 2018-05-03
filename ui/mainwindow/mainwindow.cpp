#include "mainwindow.h"

QtCentral::QtCentral(QWidget* parent) : QWidget(parent)
{
    // 【0】
    this->init_widget();
    // 【1】 设置窗口
    this->setObjectName("Central");

    // 【2】 开启空布局
    QHBoxLayout* box = new QHBoxLayout(this);
    box->setContentsMargins(0, 0, 0, 0);

    // 【3】 连接信号槽
    connect(FlexManager::instance(), SIGNAL(flexWidgetCreated(FlexWidget*)),    SLOT(on_flexWidgetCreated(FlexWidget*)));
    connect(FlexManager::instance(), SIGNAL(dockWidgetCreated(DockWidget*)),    SLOT(on_dockWidgetCreated(DockWidget*)));
    connect(FlexManager::instance(), SIGNAL(flexWidgetDestroying(FlexWidget*)), SLOT(on_flexWidgetDestroying(FlexWidget*)));
    connect(FlexManager::instance(), SIGNAL(dockWidgetDestroying(DockWidget*)), SLOT(on_dockWidgetDestroying(DockWidget*)));

    // 【4】 载入QSettings
    QSettings  settings("QtFlex5", "QtGuider");
    QByteArray content = settings.value("Flex").toByteArray();
    QMap<QString, QWidget*> parents;
    parents[objectName()] = this;

    if (content.isEmpty())
    {
        createOne();
    }
    else
    {
        FlexManager::instance()->load(content, parents);
    }
}

void QtCentral::init_widget()
{
    w_mainwidget = new MainWidget();
    w_video      = new Video();
    w_photo      = new Photo();
}

void QtCentral::createOne()
{
    auto content = FlexManager::instance()->createFlexWidget(Flex::HybridView, this, Flex::widgetFlags(), "M");
    layout()->addWidget(content);
}

void QtCentral::on_flexWidgetCreated(FlexWidget* flexWidget)
{
    if (flexWidget->objectName() == "M")
    {
        layout()->addWidget(flexWidget);
    }
    else
    {
        flexWidget->show();
    }
}

void QtCentral::on_dockWidgetCreated(DockWidget *dockWidget)
{
    if (dockWidget->objectName() == QStringLiteral("主界面"))
    {
        if (dockWidget->widget() != w_mainwidget)
        {
            dockWidget->setWidget(w_mainwidget);
        }
    }

    if (dockWidget->objectName() == QStringLiteral("视频"))
    {
        if (dockWidget->widget() != w_video)
        {
            dockWidget->setWidget(w_video);
        }
    }

    if (dockWidget->objectName() == QStringLiteral("图像"))
    {
        if (dockWidget->widget() != w_photo)
        {
            dockWidget->setWidget(w_photo);
        }
    }

//    if (dockWidget->objectName() == QStringLiteral("音乐"))
//    {
//        if (dockWidget->widget() != c_dock_music)
//        {
//            dockWidget->setWidget(c_dock_music);
//        }
//    }
}

void QtCentral::on_dockWidgetDestroying(DockWidget *dockWidget)
{
    if (dockWidget->objectName() == QStringLiteral("主界面"))
    {
        if (dockWidget->widget() == w_mainwidget)
        {
            dockWidget->detachWidget(w_mainwidget);
        }
    }

    if (dockWidget->objectName() == QStringLiteral("视频"))
    {
        if (dockWidget->widget() == w_video)
        {
            dockWidget->detachWidget(w_video);
        }
    }

    if (dockWidget->objectName() == QStringLiteral("图像"))
    {
        if (dockWidget->widget() == w_photo)
        {
            dockWidget->detachWidget(w_photo);
        }
    }

//    if (dockWidget->objectName() == QStringLiteral("音乐"))
//    {
//        if (dockWidget->widget() == c_dock_music)
//        {
//            dockWidget->detachWidget(c_dock_music);
//        }
//    }
}

void QtCentral::on_flexWidgetDestroying(FlexWidget*)
{
}




MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi();
    setConnect();
    setExtras();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("您不多留一会么?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    if (ret == QMessageBox::Yes)
    {
        event->accept();

        // 【1】 写配置文件
        writeSettings();

        // 【2】 写注册表
        QByteArray content = FlexManager::instance()->save();
        QSettings settings("QtFlex5", "QtGuider");
        settings.setValue("Flex", content);
        FlexManager::instance()->close();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::setupUi()
{
    // 【0】 初始化Menu, Action
    setActions();

    // 【1】 载入QFlex样式.
    qApp->setProperty("window", QVariant::fromValue<QObject*>(this));

    // 【2】 载入中心窗口
    this->setCentralWidget(new QtCentral(this));

    // 【3】 读配置文件
    readSettings();

    // 【4】 设置窗口属性
    setWindowIcon(QIcon(":/res/img/player_taskbar.png"));
}

void MainWindow::setConnect()
{
    connect(action_view_mainwidget, &QAction::triggered, this, &MainWindow::on_view_mainwidget);
    connect(action_view_video,      &QAction::triggered, this, &MainWindow::on_view_video);
    connect(action_view_photo,      &QAction::triggered, this, &MainWindow::on_view_photo);
    // connect(action_view_music,   &QAction::triggered, this, &ui_mainwindow::on_view_motor_point);
}


void MainWindow::writeSettings()
{
    QSettings setting("../config/settings.ini", QSettings::IniFormat);

    // 【1】 窗口大小, 位置
    setting.beginGroup("MainWindow");
    setting.setValue("x", x());
    setting.setValue("y", y());
    setting.setValue("width", width());
    setting.setValue("height", height());
    setting.setValue("size", size());
    setting.setValue("pos", pos());
    setting.endGroup();

}

void MainWindow::readSettings()
{
    // 【1】 判断是否存在改配置文件
    QFile file("../config/settings.ini");
    if (!file.exists())
    {
        this->setGeometry(QApplication::desktop()->availableGeometry().adjusted(100, 100, -100, -100));
    }
    else
    {
        QSettings setting("../config/settings.ini", QSettings::IniFormat);

        // 【2】 窗口大小, 位置
        resize(setting.value("MainWindow/size").toSize());
        move(setting.value("MainWindow/pos").toPoint());
    }
}


void MainWindow::setExtras()
{
    setDWM();
    setTaskbar();
    setThumbnailToolBar();
    setJumpList();
}

void MainWindow::setDWM()
{
    // Win10下 失效
    if (QtWin::isCompositionEnabled())                           // 返回DWM组合状态
    {
        QtWin::extendFrameIntoClientArea(this, -1, -1, -1, -1);   // 玻璃效果
        // QtWin::enableBlurBehindWindow(this);
        setAttribute(Qt::WA_TranslucentBackground, true);         // 半透明背景
        setAttribute(Qt::WA_NoSystemBackground, false);           // 禁用无背景
        // setStyleSheet("MainWindow { background: transparent; }");
    }
    else
    {
        QtWin::resetExtendedFrame(this);
        setAttribute(Qt::WA_TranslucentBackground, false);

    }
}

void MainWindow::setTaskbar()
{
    taskbarBtn = new QWinTaskbarButton(this);
    taskbarBtn->setWindow(this->windowHandle());
    taskbarBtn->setOverlayIcon(QIcon(":/res/img/player_taskbar.png"));

    taskbarProgress = taskbarBtn->progress();
    taskbarProgress->setVisible(true);
    taskbarProgress->setValue(50);
}

void MainWindow::setThumbnailToolBar()
{
    thumbnailToolBar = new QWinThumbnailToolBar(this);
    thumbnailToolBar->setWindow(this->windowHandle());

    thumbnailBtn_previous = new QWinThumbnailToolButton(thumbnailToolBar);
    thumbnailBtn_previous->setToolTip(QStringLiteral("上一曲"));
    thumbnailBtn_previous->setIcon(QIcon(":/res/img/player_previous.png"));
    thumbnailBtn_previous->setDismissOnClick(true);

    thumbnailBtn_playPause = new QWinThumbnailToolButton(thumbnailToolBar);
    thumbnailBtn_playPause->setToolTip(QStringLiteral("播放"));
    thumbnailBtn_playPause->setIcon(QIcon(":/res/img/player_play.png"));
    thumbnailBtn_playPause->setDismissOnClick(true);

    thumbnailBtn_next = new QWinThumbnailToolButton(thumbnailToolBar);
    thumbnailBtn_next->setToolTip(QStringLiteral("下一曲"));
    thumbnailBtn_next->setIcon(QIcon(":/res/img/player_next.png"));
    thumbnailBtn_next->setDismissOnClick(true);

    thumbnailToolBar->addButton(thumbnailBtn_previous);
    thumbnailToolBar->addButton(thumbnailBtn_playPause);
    thumbnailToolBar->addButton(thumbnailBtn_next);

}

void MainWindow::setJumpList()
{
    // 【1】 定义启动路径
    QString m_executablePath_VSCode = "file:///C:/Program Files/Microsoft VS Code/Code.exe";
    QString m_executablePath_CloudMusic = "file:///C:/Program Files (x86)/Netease/CloudMusic/cloudmusic.exe";
    QString m_executablePath_WeChat = "file:///C:/Program Files (x86)/Tencent/WeChat/WeChat.exe";
    QString m_executablePath_YoudaoNote = "file:///C:/Program Files (x86)/Youdao/YoudaoNote/YoudaoNote.exe";

    QString m_executablePath_QtQuick = "file:///D:/CodeManage/Qt/QtQuick/";
    QString m_executablePath_CodeManage = "file:///D:/CodeManage/";

    // 【2】 定义 QWinJumpListItem
    QWinJumpListItem *link_VSCode = new QWinJumpListItem(QWinJumpListItem::Link);
    link_VSCode->setTitle("VS Code");
    link_VSCode->setDescription(QStringLiteral("启动 VS Code"));
    link_VSCode->setFilePath(m_executablePath_VSCode);

    QWinJumpListItem *link_CloudMusic = new QWinJumpListItem(QWinJumpListItem::Link);
    link_CloudMusic->setTitle(QStringLiteral("网易云音乐"));
    link_CloudMusic->setDescription(QStringLiteral("启动 网易云音乐"));
    link_CloudMusic->setFilePath(m_executablePath_CloudMusic);

    QWinJumpListItem *link_WeChat = new QWinJumpListItem(QWinJumpListItem::Link);
    link_WeChat->setTitle(QStringLiteral("微信"));
    link_WeChat->setDescription(QStringLiteral("启动 微信"));
    link_WeChat->setFilePath(m_executablePath_WeChat);

    QWinJumpListItem *link_YoudaoNote = new QWinJumpListItem(QWinJumpListItem::Link);
    link_YoudaoNote->setTitle(QStringLiteral("有道云笔记"));
    link_YoudaoNote->setDescription(QStringLiteral("启动 有道云笔记"));
    link_YoudaoNote->setFilePath(m_executablePath_YoudaoNote);

    QWinJumpListItem *link_myComputer = new QWinJumpListItem(QWinJumpListItem::Link);
    link_myComputer->setTitle(QStringLiteral("我的电脑"));
    link_myComputer->setDescription(QStringLiteral("打开 我的电脑"));

    QWinJumpListItem *link_CodeManage = new QWinJumpListItem(QWinJumpListItem::Link);
    link_CodeManage->setTitle(QStringLiteral("CodeManage"));
    link_CodeManage->setDescription(QStringLiteral("打开 CodeManage 文件夹"));
    link_CodeManage->setFilePath(m_executablePath_CodeManage);

    QWinJumpListItem *link_QtQuick = new QWinJumpListItem(QWinJumpListItem::Link);
    link_QtQuick->setTitle(QStringLiteral("QtQuick"));
    link_QtQuick->setDescription(QStringLiteral("打开 QtQuick 文件夹"));
    link_QtQuick->setFilePath(m_executablePath_QtQuick);


    QWinJumpListItem *newProject = new QWinJumpListItem(QWinJumpListItem::Link);
    newProject->setTitle(tr("Create new project"));
    newProject->setFilePath(QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
    newProject->setArguments(QStringList("--new-project"));

    // 【3】 初始化 QWinJumpListCategory, 并添加 QWinJumpListItem
    jumplistCategory_startUp = new QWinJumpListCategory();
    jumplistCategory_startUp->setTitle(QStringLiteral("启动"));
    jumplistCategory_startUp->setVisible(true);
    // 添加 QWinJumpListItem
    jumplistCategory_startUp->addItem(link_VSCode);
    jumplistCategory_startUp->addItem(link_CloudMusic);
    jumplistCategory_startUp->addItem(link_WeChat);
    jumplistCategory_startUp->addItem(link_YoudaoNote);

    jumplistCategory_folder = new QWinJumpListCategory();
    jumplistCategory_folder->setTitle(QStringLiteral("目录"));
    jumplistCategory_folder->setVisible(true);
    // 添加 QWinJumpListItem
    jumplistCategory_folder->addItem(link_myComputer);
    jumplistCategory_folder->addItem(link_CodeManage);
    jumplistCategory_folder->addItem(link_QtQuick);

    jumplistCategory_playlist = new QWinJumpListCategory();
    jumplistCategory_playlist->setTitle(QStringLiteral("最近播放"));
    jumplistCategory_playlist->setVisible(true);

    // 【4】 添加 QWinJumpListCategory 到 QWinJumpList 中
    jumplist = new QWinJumpList(this);

    jumplist->addCategory(jumplistCategory_startUp);
    jumplist->addCategory(jumplistCategory_folder);
    jumplist->addCategory(jumplistCategory_playlist);


}


void MainWindow::setActions()
{
    action_file_new      = new QAction(QStringLiteral("&New"),  this);
    action_file_open     = new QAction(QStringLiteral("&Open"), this);
    action_file_save     = new QAction(QStringLiteral("&Save"), this);
    action_file_save_all = new QAction(QStringLiteral("&SaveAll"), this);
    action_file_exit     = new QAction(QStringLiteral("&Exit"), this);

    action_view_mainwidget = new QAction(QStringLiteral("主界面"), this);
    action_view_video      = new QAction(QStringLiteral("视频"), this);
    action_view_music      = new QAction(QStringLiteral("音乐"), this);
    action_view_photo      = new QAction(QStringLiteral("图像"), this);

    QList<QAction*> list_action_file;
    QList<QAction*> list_action_view;

    list_action_file << action_file_new << action_file_open << action_file_save
                     << action_file_save_all << action_file_exit;
    list_action_view << action_view_mainwidget
                     << action_view_video << action_view_music << action_view_photo;

    QMenu *menu_file = new QMenu("&File");
    QMenu *menu_view = new QMenu("&View");
    menu_file->addActions(list_action_file);
    menu_view->addActions(list_action_view);

    this->menuBar()->addMenu(menu_file);
    this->menuBar()->addMenu(menu_view);
}

void MainWindow::on_view_mainwidget()
{
    QString dockWidgetName = QStringLiteral("主界面");
    DockWidget* widget = nullptr;

    if ((widget = FlexManager::instance()->dockWidget(dockWidgetName)) != nullptr)
    {
        widget->activate();
    }
    else
    {
        if (!FlexManager::instance()->restore(dockWidgetName))
        {
            FlexWidget* flexWidget = FlexManager::instance()->createFlexWidget(Flex::ToolView, Flex::parent(Flex::ToolView), Flex::windowFlags());
            DockWidget* dockWidget = FlexManager::instance()->createDockWidget(Flex::ToolView, flexWidget, Flex::widgetFlags(), dockWidgetName);

            dockWidget->setViewMode(Flex::ToolView);
            dockWidget->setWindowTitle(dockWidgetName);

            flexWidget->addDockWidget(dockWidget);
            flexWidget->show();

            flexWidget->move(geometry().center() - flexWidget->rect().center());
        }
    }
}

void MainWindow::on_view_video()
{
    QString dockWidgetName = QStringLiteral("视频");
    DockWidget* widget = nullptr;

    if ((widget = FlexManager::instance()->dockWidget(dockWidgetName)) != nullptr)
    {
        widget->activate();
    }
    else
    {
        if (!FlexManager::instance()->restore(dockWidgetName))
        {
            FlexWidget* flexWidget = FlexManager::instance()->createFlexWidget(Flex::ToolView, Flex::parent(Flex::ToolView), Flex::windowFlags());
            DockWidget* dockWidget = FlexManager::instance()->createDockWidget(Flex::ToolView, flexWidget, Flex::widgetFlags(), dockWidgetName);

            dockWidget->setViewMode(Flex::ToolView);
            dockWidget->setWindowTitle(dockWidgetName);

            flexWidget->addDockWidget(dockWidget);
            flexWidget->show();
            flexWidget->move(geometry().center() - flexWidget->rect().center());
        }
    }
}

void MainWindow::on_view_photo()
{
    QString dockWidgetName = QStringLiteral("图像");
    DockWidget* widget = nullptr;

    if ((widget = FlexManager::instance()->dockWidget(dockWidgetName)) != nullptr)
    {
        widget->activate();
    }
    else
    {
        if (!FlexManager::instance()->restore(dockWidgetName))
        {
            FlexWidget* flexWidget = FlexManager::instance()->createFlexWidget(Flex::ToolView, Flex::parent(Flex::ToolView), Flex::windowFlags());
            DockWidget* dockWidget = FlexManager::instance()->createDockWidget(Flex::ToolView, flexWidget, Flex::widgetFlags(), dockWidgetName);

            dockWidget->setViewMode(Flex::ToolView);
            dockWidget->setWindowTitle(dockWidgetName);

            flexWidget->addDockWidget(dockWidget);
            flexWidget->show();
            flexWidget->move(geometry().center() - flexWidget->rect().center());
        }
    }
}
