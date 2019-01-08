#include "Mainwindow.h"

MainWindow::MainWindow(const QString& path, QWidget *parent) : QMainWindow(parent)
{
    this->path = path;
    this->showMaximized();

    booksVector = getBooks();
    rowCount = booksVector.size();
    columnCount = 7;

    wdg = new QWidget;

    layout       = new QHBoxLayout;
    actionLayout = new QVBoxLayout;
    tableLayout  = new QVBoxLayout;

    sortByNameBtn = new QPushButton(tr("Sort by name"));
    sortByYearBtn = new QPushButton(tr("Sort by year"));
    findBtn       = new QPushButton(tr("Find by name"));

    actionLayout->addWidget(findBtn);
    actionLayout->addWidget(sortByNameBtn);
    actionLayout->addWidget(sortByYearBtn);

    tableWidget = new QTableWidget(rowCount, columnCount, this);
    tableWidget->setHorizontalHeaderLabels(BookModel::names);

    for (auto v : booksVector)
    {
        qDebug() << v.name << " ";
    }

    setValues();
    tableLayout->addWidget(tableWidget);

    layout->addLayout(actionLayout);
    layout->addLayout(tableLayout);

    wdg->setLayout(layout);

    setCentralWidget(wdg);

    createMenus();
}

MainWindow::~MainWindow() {}

void MainWindow::MainWindow::createMenus()
{
    addBook = menuBar()->addMenu(tr("&File"));
    QAction* add = addBook->addAction("Add new book");
    connect(add, &QAction::triggered, this, &MainWindow::addBookSlot);

    removeBook = menuBar()->addMenu(tr("&Edit"));
    QAction* remove = removeBook->addAction(tr("Remove book"));
    connect(remove, &QAction::triggered, this, &MainWindow::removeBookSlot);

    exportBook = menuBar()->addMenu(tr("&Export book"));
    QAction* exportBookAction = exportBook->addAction(tr("&Export"));
    connect(exportBookAction, &QAction::triggered, this, &MainWindow::exportBooksSlot);

    help = menuBar()->addMenu(tr("&Help"));
    QAction* about = help->addAction(tr("&About"));
    connect(about, &QAction::triggered, this, &MainWindow::aboutSlot);
}

void MainWindow::addBookSlot()
{
    QMessageBox m;
    m.setText("Add");
    m.exec();
}

void MainWindow::removeBookSlot() {}
void MainWindow::findBookSlot() {}
void MainWindow::sortBookSlot() {}
void MainWindow::exportBooksSlot()
{
    BookMapper mapper;
    QJsonDocument doc;
    doc.setArray(mapper.toJson(booksVector));
    QString data(doc.toJson());

    FileHelper::upload(path + "/entries", data);
}

void MainWindow::aboutSlot()
{
    QMessageBox about;
    about.setText("Created by Bogdan Babitskiy");
    about.exec();
}

QVector<BookModel> MainWindow::getBooks()
{
    QVector<BookModel> books;
    QString fullPath = QDir::toNativeSeparators(this->path + "/entries");
    QString file = "";
    FileHelper fileHelper(fullPath);
    QString fullFilePath = QDir::toNativeSeparators(fullPath + "/books.json");

    BookMapper mapper;


    if (!QFile::exists(fullPath))
    {
        qDebug() << "Not exists: >>>>>>>>>>>> " << fullPath;
        QDir().mkdir(fullPath);
        QFile booksFile(fullFilePath);
        if (booksFile.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&booksFile);
            stream << "{\"books\": [{}]}" << endl;
            booksFile.close();
        }
    }

    file = fileHelper.download(fullFilePath);
    books = mapper.doObjects(file);

    return books;
}

void MainWindow::setValues()
{
    for (int i = 0; i < rowCount; ++ i)
    {

            QTableWidgetItem *id = new QTableWidgetItem;
            id->setText(QString::number(booksVector[i].id));
            tableWidget->setItem(i, 0, id);


            QTableWidgetItem *name = new QTableWidgetItem;
            name->setText(booksVector[i].name);
            tableWidget->setItem(i, 1, name);

            QTableWidgetItem *author = new QTableWidgetItem;
            author->setText(booksVector[i].author);
            tableWidget->setItem(i, 2, author);

            QTableWidgetItem *year = new QTableWidgetItem;
            year->setText(QString::number(booksVector[i].year));
            tableWidget->setItem(i, 3, year);

            QTableWidgetItem *description = new QTableWidgetItem;
            description->setText(booksVector[i].description);
            tableWidget->setItem(i, 4, description);

            QTableWidgetItem *pageCount = new QTableWidgetItem;
            pageCount->setText(QString::number(booksVector[i].pageCount));
            tableWidget->setItem(i, 5, pageCount);

            QTableWidgetItem *link = new QTableWidgetItem;
            link->setText(booksVector[i].link);
            tableWidget->setItem(i, 6, link);
    }
}

