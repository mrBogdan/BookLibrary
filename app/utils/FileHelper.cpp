#include "app/utils/FileHelper.h"

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

    if(!QFile::exists(path))
    {
        qDebug() << "File does not exists";
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream stream(&file);
            stream << "{\"books\": [{}]}" << endl;
            file.close();
        }
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open " << path;
        exit(1);
    }

    QString json = "";

    json = file.readAll();
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
