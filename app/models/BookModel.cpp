#include "BookModel.h"

const QStringList BookModel::names  = {
    "id",
    "name",
    "author",
    "year",
    "description",
    "page count",
    "link"
};

void showBooks(QVector<BookModel> vec)
{
    for (auto v : vec)
    {
        qDebug() << "ID >>> " << v.id << endl;
        qDebug() << "Name >>> " << v.name << endl;
        qDebug() << "Author >>> " << v.author << endl;
        qDebug() << "Year >>> " << v.year << endl;
        qDebug() << "Descr >>> " << v.description << endl;
        qDebug() << "Page c >>> " << v.pageCount << endl;
        qDebug() << "link >>> " << v.link << endl;
    }
}
