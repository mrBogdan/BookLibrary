#ifndef BOOK_MAPPER_H
#define BOOK_MAPPER_H

#include "app/data/models/BookModel.h"
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonDocument>
#include <QDebug>

class BookMapper
{
public:
   BookModel doObject(const QString& json);

};

#endif
