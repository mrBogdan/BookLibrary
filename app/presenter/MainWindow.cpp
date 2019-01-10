#include "Mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->fileName = QFileDialog::getOpenFileName(this, "Open file", QDir::home().dirName(), tr("Json (*.json)"));
    this->showMaximized();

    booksVector = getBooks(fileName);
    rowCount    = booksVector.size();
    columnCount = 6;

    layout       = new QHBoxLayout;
    actionLayout = new QVBoxLayout;
    tableLayout  = new QVBoxLayout;

    findBtn       = new QPushButton(tr("Find by name"));
    save          = new QPushButton(tr("Save"));
    save->setEnabled(false);

    actionLayout->addWidget(findBtn);
    actionLayout->addWidget(save);
    actionLayout->setAlignment(Qt::AlignTop);

    setTableWidget();

    tableLayout->addWidget(tableWidget);

    layout->addLayout(actionLayout);
    layout->addLayout(tableLayout);

    setCentralWidget(new QWidget);
    setStatusBar(new QStatusBar);
    centralWidget()->setLayout(layout);
    createMenus();

    connect(tableWidget, &QTableWidget::itemChanged, this, &MainWindow::updateSingleValue);
    connect(save, &QPushButton::clicked, this, &MainWindow::saveSlot);
    connect(findBtn, &QPushButton::clicked, this, &MainWindow::findBookSlot);
}

void MainWindow::MainWindow::createMenus()
{
    addBook           = menuBar()->addMenu(tr("&File"));
    QAction* openFile = addBook->addAction(tr("&Open file"));
    QAction* add      = addBook->addAction(tr("&Add new book"));
    addBook->addSeparator();
    QAction* exitA    = addBook->addAction(tr("&Exit"));

    connect(openFile, &QAction::triggered, this, &MainWindow::openSlot);
    connect(exitA, &QAction::triggered, this, &MainWindow::exitSlot);
    connect(add, &QAction::triggered, this, &MainWindow::addBookSlot);

    removeBook      = menuBar()->addMenu(tr("&Edit"));
    QAction* remove = removeBook->addAction(tr("Remove book"));
    connect(remove, &QAction::triggered, this, &MainWindow::removeBookSlot);

    exportBook                = menuBar()->addMenu(tr("&Export book"));
    QAction* exportBookAction = exportBook->addAction(tr("&Export"));
    connect(exportBookAction, &QAction::triggered, this, &MainWindow::exportBooksSlot);

    help           = menuBar()->addMenu(tr("&Help"));
    QAction* about = help->addAction(tr("&About"));
    connect(about, &QAction::triggered, this, &MainWindow::aboutSlot);
}

void MainWindow::setTableWidget()
{
    tableWidget = new QTableWidget(rowCount, columnCount, this);
    tableWidget->setUpdatesEnabled(true);
    tableWidget->horizontalHeader()->sortIndicatorOrder();
    tableWidget->setHorizontalHeaderLabels(BookModel::names);
    setValues();
}

void MainWindow::addBookSlot()
{
   addWnd = new AddBookWindow(booksVector, this);
   addWnd->show();
   connect(addWnd, SIGNAL(added()), this, SLOT(updateEntries()));
}

void MainWindow::removeBookSlot()
{
    bool ok      = false;
    QString name = QInputDialog::getText(this,
                                         tr("Remove by name"),
                                         tr("Name: "),
                                         QLineEdit::Normal,
                                         QDir::home().dirName(),
                                         &ok
                   );
    if (ok)
    {
        int row = findTableRow(name);

        if (row >= 0)
        {
            tableWidget->removeRow(row);
            booksVector.remove(row);
            save->setEnabled(true);
            statusBar()->showMessage("Removed");
        }
        else
        {
            statusBar()->showMessage("Not found");
        }
    }
}

int MainWindow::findTableRow(const QString& name)
{
    int row   = -1;
    int rows  = tableWidget->rowCount();
    for(int i = 0; i < rows; ++i)
    {
        if(tableWidget->item(i, 0)->text() == name)
        {
            row = i;
            break;
        }
    }

    return row;
}

void MainWindow::findBookSlot()
{
   findWnd = new FindWindow(this);
   connect(findWnd, &FindWindow::findSignal, this, &MainWindow::findBookEntry);
   findWnd->show();
}

void MainWindow::findBookEntry(const QString& name)
{
    QList<QTableWidgetItem*> items = tableWidget->findItems(name, Qt::MatchExactly);

    for (const auto& item : items)
    {
        QModelIndex i = tableWidget->model()->index(item->row(), item->column(), QModelIndex());

        tableWidget->selectionModel()->select(i, QItemSelectionModel::Select);
    }

    if (items.size() == 0)
    {
        statusBar()->showMessage("Not found!");
    } else {
        statusBar()->showMessage("Done");
    }
}

void MainWindow::exitSlot()
{
    QApplication::exit();
}

void MainWindow::exportBooksSlot()
{
    BookMapper mapper;

    QJsonDocument doc(mapper.doJson(booksVector));

    QString data(doc.toJson());

    saveSlot();

    QString savingPlace = QFileDialog::getSaveFileName(this,tr("Export file"), "", tr("Json (*.json)"));

    if (FileHelper::upload(savingPlace, data))
    {
        statusBar()->showMessage("Exported");
    } else {
        statusBar()->showMessage("Error, try again!");
    }
}

void MainWindow::aboutSlot()
{
    QMessageBox about;
    about.setText("Created by Bogdan Babitskiy 2018/2019\nGNU LGPL");
    about.exec();
}

QVector<BookModel> MainWindow::getBooks(const QString& filePath)
{
    QVector<BookModel> books;
    QString fullPath = QDir::toNativeSeparators(filePath);
    QString file     = "";

    BookMapper mapper;

    file  = FileHelper::download(filePath);
    books = mapper.doObjects(file);

    return books;
}

void MainWindow::setValues()
{
    tableWidget->setSortingEnabled(false);
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
    tableWidget->setSortingEnabled(true);
}

void MainWindow::updateSingleValue(QTableWidgetItem* item)
{
    const int row = item->row();
    const int col = item->column();

    updateBookValue(row, col, item);

    save->setEnabled(true);
}

void MainWindow::updateBookValue(const int row, const int col, QTableWidgetItem* item)
{
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
}

 void MainWindow::saveSlot()
{
     save->setEnabled(false);
     BookMapper mapper;
     QJsonDocument doc(mapper.doJson(booksVector));

     if (FileHelper::upload(fileName, QString(doc.toJson())))
         statusBar()->showMessage("Saved");
     else {
         statusBar()->showMessage("Not saved!");
     }
}

void MainWindow::updateEntries()
{
    rowCount = booksVector.size();
    tableWidget->clearContents();
    tableWidget->insertRow(rowCount - 1);
    setValues();
    saveSlot();
}

void MainWindow::openSlot()
{
    this->fileName = QFileDialog::getOpenFileName(nullptr, tr("Open file"), "File path", tr("Json (*.json)"));

    tableWidget->clearContents();
    tableWidget->setRowCount(0);

    if (booksVector.size() > 0)
    {
        booksVector.clear();
    }
    booksVector = getBooks(fileName);

    rowCount = booksVector.size();
    tableWidget->setRowCount(rowCount);

    setValues();
}

