#ifndef BOOK_MODEL_H
#define BOOK_MODEL_H

#include <QString>

struct BookModel
{
    unsigned int id;
    QString      name;
    QString      author;
    unsigned int year;
    QString      description;
    unsigned int pageCount;
    QString      link;
};

#endif
