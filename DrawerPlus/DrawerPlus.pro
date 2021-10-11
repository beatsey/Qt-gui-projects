QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
        graphicsWidget.cpp \
        main.cpp \
        mainwindow.cpp \
        mygridwidget.cpp

HEADERS += \
        graphicsWidget.h \
        mainwindow.h \
        mygridwidget.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
