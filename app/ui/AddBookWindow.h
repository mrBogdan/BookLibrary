#ifndef ADD_BOOK_WINDOW_H
#define ADD_BOOK_WINDOW_H

#include <QMainWindow>

namespace Ui {
    class AddBookWindow : public QMainWindow
    {
         Q_OBJECT
    private:
    public:
        AddBookWindow(QWidget* parent = 0);
    };
}

#endif
