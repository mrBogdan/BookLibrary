#include <QApplication>
#include "app/presenter/Mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow wdg(app.applicationDirPath());

    wdg.show();

    return app.exec();
}
