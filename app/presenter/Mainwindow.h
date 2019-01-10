#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QMenu>
#include <QMenuBar>
#include <QtAlgorithms>
#include <QJsonDocument>
#include <QStatusBar>
#include <algorithm>
#include <QItemSelectionModel>
#include <QInputDialog>
#include <QAbstractItemModel>
#include "app/models/BookModel.h"
#include "app/utils/FileHelper.h"
#include "app/mapper/BookMapper.h"
#include "app/presenter/AddBookWndow.h"
#include "app/presenter/FindWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<BookModel> getBooks(const QString& filePath);

private:
    QMenu* addBook;
    QMenu* removeBook;
    QMenu* exportBook;
    QMenu* help;

    QWidget* wdg;
    QTableWidget* tableWidget;
    QHBoxLayout* layout;
    QVBoxLayout* actionLayout;
    QVBoxLayout* tableLayout;

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

private slots:
    void addBookSlot();
    void removeBookSlot();
    void exportBooksSlot();
    void findBookSlot();
    void findBookEntry(const QString name);
    void sortBookByYearSlot();
    void sortBookByNameSlot();
    void aboutSlot();
    void updateSingleValue(QTableWidgetItem* item);
    void saveSlot();
    void exitSlot();
    void openSlot();

signals:

public slots:
    void updateEntries();
};

#endif // MAINWINDOW_H
