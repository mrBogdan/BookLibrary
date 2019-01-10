#include <QApplication>
#include <QObject>
#include "app/presenter/Mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow wdg;

    wdg.show();
    return app.exec();
}
