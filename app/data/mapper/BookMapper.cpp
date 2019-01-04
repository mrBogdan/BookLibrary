#include "app/data/mapper/BookMapper.h"

BookModel BookMapper::doObject(const QString &json)
{
    BookModel bookModel;

    QByteArray json_bytes = json.toLocal8Bit();
    auto json_doc = QJsonDocument::fromJson(json_bytes);

    if(json_doc.isNull())
    {
        qDebug() << json_bytes;
        qDebug() << "Failed to create JSON doc.";
        exit(1);
    }
    if(!json_doc.isObject())
    {
        qDebug() << "JSON is not an object.";
        exit(2);
    }

    QJsonObject json_obj = json_doc.object();

    if(json_obj.isEmpty())
    {
        qDebug() << "JSON object is empty.";
        exit(3);
    }

    QVariantMap json_map = json_obj.toVariantMap();

    qDebug() << json_map["name"].toString();
    qDebug() << json_map["str"].toInt();
    qDebug() << json_map["enemy"].toString();

    return bookModel;
}
