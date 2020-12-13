#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sqlite3.h"
#include <QDebug>
#include <form.h>

//声明回调函数
typedef int (*selectMessageTableCallback)(void*, int, char**, char**);

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initData();
    void initOpenData();
    void initConnect();
    void selectData();
    void test();
    void selectMessageTable(const QString &strSql, selectMessageTableCallback callback, void *pObj);

signals:
    void singalSelectFinished();

public slots:
    void slotSqlTest();


private:
    Ui::MainWindow *ui;
    Form *m_form;
    sqlite3 *db;
    int a;
};
#endif // MAINWINDOW_H
