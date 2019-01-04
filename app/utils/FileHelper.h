#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include <QFileInfoList>
#include <QString>
#include <QDir>
#include <QFile>
#include <QDebug>

class FileHelper
{
private:
    QString dir;
public:
    FileHelper(QString dir);
    QFileInfoList getListDirs();
    QString getDir() const;
    QString download(const QString& filePath);

};

#endif

