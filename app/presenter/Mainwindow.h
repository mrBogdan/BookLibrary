#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QMenu>
#include <QMenuBar>
#include "app/models/BookModel.h"
#include "app/utils/FileHelper.h"
#include "app/mapper/BookMapper.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(const QString& path, QWidget *parent = nullptr);
    ~MainWindow();
    QVector<BookModel> getBooks();

private:
    QString path;

    QMenu* addBook;
    QMenu* removeBook;
    QMenu* exportBook;
    QMenu* help;

    QTableWidget* tableWidget;
    QWidget* wdg;
    QHBoxLayout* layout;
    QVBoxLayout* actionLayout;
    QVBoxLayout* tableLayout;

    QVector<BookModel> booksVector;

    QPushButton* findBtn;
    QPushButton* sortByYearBtn;
    QPushButton* sortByNameBtn;

    int rowCount;
    int columnCount;

    void createMenus();
    void setValues();

private slots:
    void addBookSlot();
    void removeBookSlot();
    void exportBooksSlot();
    void findBookSlot();
    void sortBookSlot();
    void aboutSlot();

signals:

public slots:

};

#endif // MAINWINDOW_H
