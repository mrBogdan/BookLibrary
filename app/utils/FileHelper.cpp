#include "app/utils/FileHelper.h"

QString FileHelper::initialData = "{\"books\": [{}]}";

QFileInfoList FileHelper::getListDirs(const QString& dirName)
{
    QDir dir(dirName);
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name);

    QFileInfoList list = dir.entryInfoList();

    return list;
}

QString FileHelper::download(const QString& filePath)
{
    QString path = QDir::toNativeSeparators(filePath);
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open " << path;
        exit(1);
    }

    QString json = "";

    json = file.readAll();

    if (json.isEmpty())
    {
        FileHelper::upload(path, FileHelper::initialData);
        json = FileHelper::download(path);
    }

    file.close();

    return json;
}

bool FileHelper::upload(const QString& path, const QString& data)
{
    QFile file(path);

    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << data << endl;
        file.close();
        return true;
    }

    return false;
}
