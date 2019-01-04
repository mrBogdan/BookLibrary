#include <QApplication>
#include "app/MainWindowController.h"
#include "app/utils/FileHelper.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow wdg;


    FileHelper fileHelper(app.applicationDirPath() + "/entries");
    QFileInfoList list = fileHelper.getListDirs();

    wdg.show();

    return app.exec();
}
