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

BookModel BookMapper::doObject(const QJsonValue& v)
{
    BookModel bookModel;

    bookModel.id = v.toObject().value("id").toInt();
    bookModel.name = v.toObject().value("name").toString();
    bookModel.author = v.toObject().value("author").toString();
    bookModel.year = v.toObject().value("year").toInt();
    bookModel.description = v.toObject().value("author").toString();
    bookModel.pageCount = v.toObject().value("pageCount").toInt();
    bookModel.link = v.toObject().value("link").toString();

    return bookModel;
}

QVector<BookModel> BookMapper::doObjects(const QString& json)
{
    QJsonObject obj = getBooksFromString(json);

    QJsonValue value = obj.value("books");

    QJsonArray array = value.toArray();

    QVector<BookModel> books;

    foreach (const QJsonValue& v, array)
    {
        books.push_back(this->doObject(v));
    }

    return books;
}

QJsonArray BookMapper::toJson(const QVector<BookModel>& vec)
{
    QJsonArray result;
    std::copy (vec.begin(), vec.end(), std::back_inserter(result));
    return result;
}
