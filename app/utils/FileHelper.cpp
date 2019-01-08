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
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream stream(&file);
            stream << "{\"books\": [{}]}" << endl;
            file.close();
        }
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open " << file_path;
        exit(1);
    }

    QString json_string = "";

    json_string = file.readAll();
    file.close();

    return json_string;
}

void FileHelper::upload(const QString& path, const QString& data)
{
    QFile file(path);

    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << data << endl;
        file.close();
    }
}
