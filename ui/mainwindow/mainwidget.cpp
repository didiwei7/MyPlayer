#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    setupUi();
    setConnect();
}


void MainWidget::setupUi()
{
    // 【1】 导航栏
    vnavigationbar = new QVNavigationBar(this);
    vnavigationbar->setBackgroundColor   ("#303947");
    vnavigationbar->setPenColorBackground("#E4EBF3");
    vnavigationbar->setPenColorSelected  ("#FFFFFF");
    vnavigationbar->setWidth(120);
    vnavigationbar->setRowHeight(40);
    vnavigationbar->addItem(QStringLiteral("音乐"));
    vnavigationbar->addItem(QStringLiteral("视频"));
    vnavigationbar->addItem(QStringLiteral("图像"));
    vnavigationbar->addItem(QStringLiteral("其他"));

    stackedWidget = new QStackedWidget(this);
    stackedWidget->insertWidget(0, new QLabel(QStringLiteral("音乐")));
    stackedWidget->insertWidget(1, new Video());
    stackedWidget->insertWidget(2, new Photo());
    stackedWidget->insertWidget(3, new QLabel(QStringLiteral("<font size='+1'><b><p align='center'>敌敌畏Demo系列</p></b></font>")));

    // 【2】 布局
    QHBoxLayout *layout_1 = new QHBoxLayout();
    layout_1->setContentsMargins(0, 0, 0, 0);
    layout_1->setSpacing(0);
    layout_1->addWidget(vnavigationbar);
    layout_1->addWidget(stackedWidget);

    setLayout(layout_1);
}


void MainWidget::setConnect()
{
    // 【1】 导航栏
    connect(vnavigationbar, &QVNavigationBar::currentItemChanged,
            stackedWidget,  &QStackedWidget::setCurrentIndex);
}
