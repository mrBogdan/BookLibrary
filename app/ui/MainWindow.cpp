#include "MainWindow.h"

Ui::MainWindow::MainWindow(QMainWindow* parent)
    : QMainWindow(parent)
{

    extendMenuBar();
    draw();
    connects();
}

Ui::MainWindow::~MainWindow() {}

void Ui::MainWindow::action()
{
    QMessageBox m;
    m.setText("Action");
    m.exec();
}

void Ui::MainWindow::draw()
{
    this->showMaximized();
    listWidget = new QListWidget(this);
    listWidget->addItem("Test item one \n\tTest special");

    setCentralWidget(listWidget);

}

void Ui::MainWindow::connects()
{
    connect(fileMenuAction_New, &QAction::triggered, this, &MainWindow::action);
}

void Ui::MainWindow::extendMenuBar()
{
    menuBar = new QMenuBar;

    fileMenuItem_New = new QMenu("File");
    fileMenuAction_New = new QAction("New", this);

    fileMenuItem_New->addAction(fileMenuAction_New);

    menuBar->addMenu(fileMenuItem_New);
    this->setMenuBar(menuBar);
}

void Ui::MainWindow::updateEnties() {}
