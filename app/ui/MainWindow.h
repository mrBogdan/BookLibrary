#ifndef MAINWINDOWVIEW_H
#define MAINWINDOWVIEW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow : public QMainWindow
    {
        Q_OBJECT
        private:
            void draw();
            void connects();
            void extendMenuBar();

        private slots:
            void action();

        public:
            explicit MainWindow(QMainWindow* parent = 0);
            virtual ~MainWindow();

            QMenuBar      *menuBar;
            QListWidget   *listWidget;
            QMenu         *fileMenuItem_New;
            QAction       *fileMenuAction_New;
            QVBoxLayout   *layout;

            void setupUi(QMainWindow* parent);

        public slots:
            void updateEnties();

        signals:
    };
}





#endif // MAINWINDOWVIEW_H
