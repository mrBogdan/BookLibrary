#include "Mainwindow.h"

MainWindow::MainWindow(const QString& path, QWidget *parent) : QMainWindow(parent)
{
    this->path = path;
    this->dirName = "entries";
    this->fileName = "books.json";
    this->showMaximized();

    booksVector = getBooks();
    rowCount = booksVector.size();
    columnCount = 6;

    wdg = new QWidget;

    layout       = new QHBoxLayout;
    actionLayout = new QVBoxLayout;
    tableLayout  = new QVBoxLayout;

    sortByNameBtn = new QPushButton(tr("Sort by name"));
    sortByYearBtn = new QPushButton(tr("Sort by year"));
    findBtn       = new QPushButton(tr("Find by name"));
    save          = new QPushButton(tr("Save"));
    save->setEnabled(false);

    actionLayout->addWidget(findBtn);
    actionLayout->addWidget(sortByNameBtn);
    actionLayout->addWidget(sortByYearBtn);
    actionLayout->addWidget(save);

    setTableWidget();


    tableLayout->addWidget(tableWidget);

    layout->addLayout(actionLayout);
    layout->addLayout(tableLayout);

    wdg->setLayout(layout);


    setCentralWidget(wdg);

    createMenus();

    connect(tableWidget, &QTableWidget::itemChanged, this, &MainWindow::updateSingleValue);
    connect(save, &QPushButton::clicked, this, &MainWindow::saveSlot);
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

void MainWindow::setTableWidget()
{
    tableWidget = new QTableWidget(rowCount, columnCount, this);
    tableWidget->setUpdatesEnabled(true);
    tableWidget->setHorizontalHeaderLabels(BookModel::names);
    setValues();
}

void MainWindow::addBookSlot()
{
   addWnd = new AddBookWindow(booksVector, this);
   addWnd->show();
   connect(addWnd, SIGNAL(added()), this, SLOT(updateEntries()));
}

void MainWindow::removeBookSlot() {}
void MainWindow::findBookSlot() {}
void MainWindow::sortBookSlot() {}
void MainWindow::exportBooksSlot()
{
    BookMapper mapper;
    QJsonDocument doc(mapper.doJson(booksVector));
    QString data(doc.toJson());

    FileHelper::upload(path + "/"+ dirName +"/" + fileName, data);
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
    QString fullPath = QDir::toNativeSeparators(this->path + "/" + dirName);
    QString file = "";
    FileHelper fileHelper(fullPath);
    QString fullFilePath = QDir::toNativeSeparators(fullPath + "/" + fileName);

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
        else {
            qDebug() << "HERE";
        }
    }

    file = fileHelper.download(fullFilePath);
    books = mapper.doObjects(file);

    return books;
}

void MainWindow::setValues()
{
    qDebug() << ">>>>>>>>>" << booksVector[rowCount - 1].name;

    for (int i = 0; i < rowCount; ++ i)
    {
        QTableWidgetItem *name = new QTableWidgetItem;
        name->setText(booksVector[i].name);
        tableWidget->setItem(i, 0, name);

        QTableWidgetItem *author = new QTableWidgetItem;
        author->setText(booksVector[i].author);
        tableWidget->setItem(i, 1, author);

        QTableWidgetItem *year = new QTableWidgetItem;
        year->setText(QString::number(booksVector[i].year));
        tableWidget->setItem(i, 2, year);

        QTableWidgetItem *description = new QTableWidgetItem;
        description->setText(booksVector[i].description);
        tableWidget->setItem(i, 3, description);

        QTableWidgetItem *pageCount = new QTableWidgetItem;
        pageCount->setText(QString::number(booksVector[i].pageCount));
        tableWidget->setItem(i, 4, pageCount);

        QTableWidgetItem *link = new QTableWidgetItem;
        link->setText(booksVector[i].link);
        tableWidget->setItem(i, 5, link);
    }
}

void MainWindow::updateSingleValue(QTableWidgetItem* item)
{
    const int row = item->row();
    const int col = item->column();

    switch (col) {
        case 0: {
            booksVector[row].name = item->text();
            break;
        }

        case 1: {
            booksVector[row].author = item->text();
            break;
        }

        case 2: {
            booksVector[row].year = item->text().toInt();
            break;
        }

        case 3: {
            booksVector[row].description = item->text();
            break;
        }

        case 4: {
            booksVector[row].pageCount = item->text().toInt();
            break;
        }

        case 5: {
            booksVector[row].link = item->text();
            break;
        }
    }

    save->setEnabled(true);
}

 void MainWindow::saveSlot()
{
     save->setEnabled(false);
     BookMapper mapper;
     QJsonDocument doc(mapper.doJson(booksVector));
     QString filePath = path + "/" + dirName + "/" + fileName;

     FileHelper::upload(filePath, QString(doc.toJson()));
}

void MainWindow::updateEntries()
{
    rowCount = booksVector.size();
    tableWidget->clearContents();
    tableWidget->insertRow(rowCount - 1);
    setValues();
    saveSlot();
}

