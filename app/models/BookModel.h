#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include <QString>
#include <QMetaType>
#include <QStringList>
#include <QVector>
#include <QDebug>

struct BookModel {
    int     id;
    QString name;
    QString author;
    int     year;
    QString description;
    int     pageCount;
    QString link;

    const static QStringList names;
};

void showBooks(QVector<BookModel> vec);


#endif // BOOKMODEL_H
