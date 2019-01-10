QT = core gui
QT += widgets

SOURCES += \
    main.cpp \
    app/utils/FileHelper.cpp \
    app/presenter/MainWindow.cpp \
    app/mapper/BookMapper.cpp \
    app/models/BookModel.cpp \
    app/presenter/AddBookWndow.cpp \
    app/presenter/FindWindow.cpp

HEADERS += \
    app/utils/FileHelper.h \
    app/presenter/Mainwindow.h \
    app/models/BookModel.h \
    app/mapper/BookMapper.h \
    app/presenter/AddBookWndow.h \
    app/presenter/FindWindow.h
