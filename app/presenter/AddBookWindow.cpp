#include "AddBookWindow.h"

AddBookWindow::AddBookWindow(QVector<BookModel>& vec, QWidget *parent)
    : QMainWindow(parent),
      ref(vec)
{
    vLayout = new QVBoxLayout(this);
    layout  = new QFormLayout;

    add = new QPushButton("Add");

    name        = new QLineEdit;
    author      = new QLineEdit;
    year        = new QLineEdit;
    description = new QLineEdit;
    pageCount   = new QLineEdit;
    link        = new QLineEdit;

    layout->addRow(new QLabel(tr("Name: ")), name);
    layout->addRow(new QLabel(tr("Author: ")), author);
    layout->addRow(new QLabel(tr("Year of issue: ")), year);
    layout->addRow(new QLabel(tr("Description: ")), description);
    layout->addRow(new QLabel(tr("Page count: ")), pageCount);
    layout->addRow(new QLabel(tr("Link: ")), link);

    vLayout->addLayout(layout);
    vLayout->addWidget(add);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(vLayout);

    connect(add, &QPushButton::clicked, this, &AddBookWindow::addSlot);
}

void AddBookWindow::addSlot()
{
    BookModel mdl;

    mdl.id          = (ref.size() - 1);
    mdl.name        = name->text();
    mdl.author      = author->text();
    mdl.year        = year->text().toInt();
    mdl.description = description->text();
    mdl.pageCount   = pageCount->text().toInt();
    mdl.link        = link->text();

    ref.push_back(mdl);

    clearLineEdits();
    emit added();
}

void AddBookWindow::clearLineEdits()
{
    name->clear();
    author->clear();
    year->clear();
    description->clear();
    pageCount->clear();
    link->clear();
}
