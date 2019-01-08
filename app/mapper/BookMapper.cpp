#include "BookMapper.h"

QJsonObject BookMapper::getBooksFromString(const QString &json)
{
    QByteArray json_bytes = json.toLocal8Bit();
    QJsonDocument json_doc = QJsonDocument::fromJson(json_bytes);

    if(json_doc.isNull())
    {
        qDebug() << json_bytes;
        qDebug() << "Failed to create JSON doc.";
        exit(1);
    }
    if(!json_doc.isObject())
    {
        qDebug() << "JSON is not an object.";
        exit(1);
    }

    QJsonObject json_obj = json_doc.object();

    return json_obj;
}

BookModel BookMapper::doObject(const QJsonObject& v)
{
    BookModel book;

    book.read(v);

    return book;
}

QJsonObject BookMapper::doJson(const QVector<BookModel>& vec)
{
    QJsonArray booksArray;

    for (BookModel val : vec)
    {
        QJsonObject book;
        val.write(book);

        booksArray.append(book);
    }

    QJsonObject json;
    json["books"] = booksArray;

    return json;
}

QVector<BookModel> BookMapper::doObjects(const QString& json)
{
    QJsonObject obj = getBooksFromString(json);

    QJsonArray array = obj["books"].toArray();

    QVector<BookModel> books;

    for (int i = 0; i < array.size(); ++ i)
    {
        books.push_back(this->doObject(array[i].toObject()));
    }

    return books;
}

