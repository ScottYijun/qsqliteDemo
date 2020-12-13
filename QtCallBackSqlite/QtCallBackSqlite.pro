#-------------------------------------------------
#
# Project created by QtCreator 2018-07-16T23:33:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

win32:{
    #windows 32位
    contains(QT_ARCH, i386) {
        CONFIG(debug, debug|release){
            TARGET = QtSqlcipherDemo
            DESTDIR = ../bin32
            LIBS += -L$$PWD/../bin32 -llibsqlite3  -llibeay32 -lssleay32
            #LIBS += -L$$PWD/../bin32 -lsqlcipher
        }else{
             TARGET = QtSqlcipherDemo
             DESTDIR = ../bin32
             #LIBS += -L$$PWD/../bin32 -lsqlcipher
             LIBS += -L$$PWD/../bin32 -llibsqlite3  -llibeay32 -lssleay32
        }
        message("32-bit " $${DESTDIR})

    }
}
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += SQLITE_HAS_CODEC     #这句非常重要

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    form.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    HeaderDefine.h \
    form.h \
    mainwindow.h

FORMS += \
    form.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
