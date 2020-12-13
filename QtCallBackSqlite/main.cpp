#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QTextCodec>
#include <string.h>
#include "sqlite3.h"

#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    MainWindow w;

    qint64 ntime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    qDebug() << "current time=============" << ntime;

    w.show();
    return a.exec();
}
