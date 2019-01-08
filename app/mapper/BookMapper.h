#ifndef BOOKMAPPER_H
#define BOOKMAPPER_H

#include <QJsonObject>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QString>
#include <QDebug>
#include <QVector>
#include "app/models/BookModel.h"

class BookMapper
{
public:
   QJsonObject getBooksFromString(const QString &json);
   BookModel  doObject(const QJsonValue& v);
   QVector<BookModel> doObjects(const QString& json);
   QJsonArray toJson(const QVector<BookModel>& vec);
};

#endif // BOOKMAPPER_H
