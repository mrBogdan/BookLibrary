#include "BookModel.h"

const QStringList BookModel::names  = {
    "name",
    "author",
    "year",
    "description",
    "page count",
    "link"
};

void BookModel::write(QJsonObject& json)
{
    json["id"] = id;
    json["name"] = name;
    json["author"] = author;
    json["description"] = description;
    json["year"] = year;
    json["pageCount"] = pageCount;
    json["link"] = link;
}

void BookModel::read(const QJsonObject& json)
{
    id = json.value("id").toInt();
    name = json.value("name").toString();
    author = json.value("author").toString();
    year = json.value("year").toInt();
    description = json.value("description").toString();
    pageCount = json.value("pageCount").toInt();
    link = json.value("link").toString();
}


void BookModel::print(QVector<BookModel> vec)
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
