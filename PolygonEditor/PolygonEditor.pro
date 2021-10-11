QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
        editdialog.cpp \
        figure.cpp \
        graphicsWidget.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        editdialog.h \
        figure.h \
        graphicsWidget.h \
        mainwindow.h

FORMS += \
        editdialog.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
