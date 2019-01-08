#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include <QString>
#include <QMetaType>
#include <QStringList>

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

Q_DECLARE_METATYPE(BookModel);

#endif // BOOKMODEL_H
