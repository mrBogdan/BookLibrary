#ifndef FINDWINDOW_H
#define FINDWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

class FindWindow : public QMainWindow
{
    Q_OBJECT
private:
    QVBoxLayout* vLayout;
    QHBoxLayout* hLayout;
    QPushButton* find;

    QLineEdit* nameLe;
    QLabel*    labelName;
public:
    explicit FindWindow(QWidget *parent = nullptr);

signals:
    void findSignal(const QString name);
public slots:
    void findSlot();
};

#endif // FINDWINDOW_H
