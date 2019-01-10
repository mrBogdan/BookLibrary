#ifndef ADDBOOKWNDOW_H
#define ADDBOOKWNDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QVector>
#include <QVBoxLayout>
#include <QFormLayout>
#include "app/models/BookModel.h"

class AddBookWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AddBookWindow(QVector<BookModel>& vec, QWidget *parent = nullptr);

private:
     QVBoxLayout* vLayout;
     QFormLayout* layout;

     QPushButton* add;
     QLineEdit*   name;
     QLineEdit*   author;
     QLineEdit*   year;
     QLineEdit*   description;
     QLineEdit*   pageCount;
     QLineEdit*   link;

     QVector<BookModel>& ref;
     void clearLineEdits();

signals:
    void added();

public slots:
     void addSlot();
};

#endif // ADDBOOKWNDOW_H
