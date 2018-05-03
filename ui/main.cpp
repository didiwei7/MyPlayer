#include "mainwindow/mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    app.setApplicationName(QStringLiteral("MyPlayer"));
//    app.setOrganizationName(QStringLiteral("Didiwei"));
//    app.setOrganizationDomain("www.didiwei.org");
//    app.setApplicationDisplayName(QStringLiteral("MyPlayer"));

    MainWindow w;
    w.show();

    return app.exec();
}
