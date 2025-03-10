QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Array.cpp \
    BarList.cpp \
    RecordList.cpp \
    SortInfo.cpp \
    Sorts.cpp \
    main.cpp \
    mainwindow.cpp \
    tools.cpp

HEADERS += \
    Array.h \
    BarList.h \
    RecordList.h \
    SortInfo.h \
    Sorts.h \
    mainwindow.h \
    tools.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourceSortVisualizer.qrc
