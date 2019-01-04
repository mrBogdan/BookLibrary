QT = core gui
QT += widgets

SOURCES += \
    main.cpp \
    app/MainWindowController.cpp \
    app/utils/FileHelper.cpp \
    app/data/mapper/BookMapper.cpp \
    app/ui/AddBookWindow.cpp \
    app/ui/MainWindow.cpp

HEADERS += \
    app/MainWindowController.h \
    app/utils/FileHelper.h \
    app/data/models/BookModel.h \
    app/data/mapper/BookMapper.h \
    app/ui/AddBookWindow.h \
    app/ui/MainWindow.h
