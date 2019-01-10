#include "FindWindow.h"

FindWindow::FindWindow(QWidget *parent)
    : QMainWindow(parent)
{
    vLayout = new QVBoxLayout(this);
    hLayout = new QHBoxLayout;

    nameLe    = new QLineEdit;
    labelName = new QLabel(tr("Enter the name you are looking for: "));
    find      = new QPushButton(tr("Find"));

    hLayout->addWidget(labelName);
    hLayout->addWidget(nameLe);

    vLayout->addLayout(hLayout);
    vLayout->addWidget(find);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(vLayout);

    connect(find, &QPushButton::clicked, this, &FindWindow::findSlot);
}

void FindWindow::findSlot()
{
    emit findSignal(nameLe->text());
    nameLe->clear();
    close();
}
