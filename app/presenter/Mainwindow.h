#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QMenu>
#include <QMenuBar>
#include <QJsonDocument>
#include "app/models/BookModel.h"
#include "app/utils/FileHelper.h"
#include "app/mapper/BookMapper.h"
#include "app/presenter/AddBookWndow.h"


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
    QPushButton* save;

    QString fileName;
    QString dirName;


    AddBookWindow* addWnd;

    int rowCount;
    int columnCount;

    void createMenus();
    void setValues();
    void setTableWidget();

private slots:
    void addBookSlot();
    void removeBookSlot();
    void exportBooksSlot();
    void findBookSlot();
    void sortBookSlot();
    void aboutSlot();
    void updateSingleValue(QTableWidgetItem* item);
    void saveSlot();

signals:

public slots:
    void updateEntries();

};

#endif // MAINWINDOW_H
