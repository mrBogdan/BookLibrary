#include "app/utils/FileHelper.h"

FileHelper::FileHelper(QString dir)
{
    this->dir = dir;
}

QFileInfoList FileHelper::getListDirs()
{
    QDir dir(this->dir);
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name);

    QFileInfoList list = dir.entryInfoList();

    return list;
}

QString FileHelper::getDir() const
{
    return dir;
}

QString FileHelper::download(const QString& filePath)
{
    QString file_path = QDir::toNativeSeparators(filePath);
    QFile file(file_path);

    if(!QFile::exists(file_path))
    {
        qDebug() << "File does not exists";
        exit(404);
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open " << file_path;
        exit(404);
    }

    QString json_string;
    json_string = file.readAll();
    file.close();
}
