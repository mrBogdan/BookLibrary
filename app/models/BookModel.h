#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include <QString>
#include <QMetaType>
#include <QStringList>
#include <QVector>
#include <QJsonObject>
#include <QDebug>

class BookModel {
public:
    int     id;
    QString name;
    QString author;
    int     year;
    QString description;
    int     pageCount;
    QString link;

    const static QStringList names;

    void write(QJsonObject& json);
    void read(const QJsonObject& json);
};

#endif // BOOKMODEL_H
