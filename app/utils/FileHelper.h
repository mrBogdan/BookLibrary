#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QFileInfoList>

class FileHelper
{
public:
    static QFileInfoList getListDirs(const QString& dirname);
    static QString       download(const QString& filePath);
    static bool          upload(const QString& path, const QString& file);

    static QString initialData;
};

#endif

