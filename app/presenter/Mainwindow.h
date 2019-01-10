#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QMenu>
#include <QVector>
#include <algorithm>
#include <QMenuBar>
#include <QtWidgets>
#include <QBoxLayout>
#include <QStatusBar>
#include <QMainWindow>
#include <QTextStream>
#include <QInputDialog>
#include <QtAlgorithms>
#include <QJsonDocument>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include "app/models/BookModel.h"
#include "app/utils/FileHelper.h"
#include "app/mapper/BookMapper.h"
#include "app/presenter/AddBookWindow.h"
#include "app/presenter/FindWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    QVector<BookModel> getBooks(const QString& filePath);

private:
    QMenu* addBook;
    QMenu* removeBook;
    QMenu* exportBook;
    QMenu* help;

    QWidget*      wdg;
    QTableWidget* tableWidget;
    QHBoxLayout*  layout;
    QVBoxLayout*  actionLayout;
    QVBoxLayout*  tableLayout;

    QVector<BookModel> booksVector;

    QPushButton* findBtn;
    QPushButton* sortByYearBtn;
    QPushButton* sortByNameBtn;
    QPushButton* save;

    QString fileName;

    FindWindow* findWnd;
    AddBookWindow* addWnd;

    int rowCount;
    int columnCount;

    void createMenus();
    void setValues();
    void setTableWidget();
    void updateBookValue(const int row, const int col, QTableWidgetItem* item);
    int  findTableRow(const QString& name);

private slots:
    void saveSlot();
    void exitSlot();
    void openSlot();
    void aboutSlot();
    void addBookSlot();
    void findBookSlot();
    void findBookEntry(const QString& name);
    void removeBookSlot();
    void exportBooksSlot();
    void updateSingleValue(QTableWidgetItem* item);
    void sortBookByYearSlot();
    void sortBookByNameSlot();

signals:

public slots:
    void updateEntries();
};

#endif // MAINWINDOW_H
