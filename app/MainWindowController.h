#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QtWidgets>
#include <QVBoxLayout>
#include <QListWidget>
#include "app/ui/MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow ui;

private slots:


public:
    explicit MainWindow(QMainWindow* parent = 0);
    virtual ~MainWindow();

public slots:
    void updateEnties();

signals:
};

#endif
