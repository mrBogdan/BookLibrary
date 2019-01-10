#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include <QFileInfoList>
#include <QString>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QTextStream>

class FileHelper
{
private:
    QString dir;
public:
    FileHelper(QString dir);
    QFileInfoList getListDirs();
    QString getDir() const;
    static QString download(const QString& filePath);
    bool static upload(const QString& path, const QString& file);
};

#endif

