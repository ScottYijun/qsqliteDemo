#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sqlite3.h"
#include <QTextEdit>
#include <QLabel>
#include <QFrame>
#include <QDebug>

//https://www.cnblogs.com/nanfei/p/11891467.html
int callback(void *pSender, int argc, char **argv, char **azColName)
{
    MainWindow *temp = static_cast<MainWindow *>(pSender);
    qDebug() << "CSqliteOperation  callback=====argc======" << argc;
    temp->test();
    for (int i = 0; i < argc; i++)
    {
        QString strColName = QString(azColName[i]);
        QString strValue = QString(argv[i]);
        qDebug()<< "(列名)" << strColName << "(值):" << strValue << "\t";

        //if(i + 1 == argc)
        //    m_pInstance->getSelectResult(argc, strValue, strColName);

    }
    return 0;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_form(nullptr)
    , db(nullptr)
{
    ui->setupUi(this);
    initData();
    initOpenData();
    initConnect();
    //selectData();
}

MainWindow::~MainWindow()
{
    if(db)
    {
        sqlite3_close(db);
    }
    delete ui;
}


void MainWindow::initData()
{
    m_form = new Form(this, this);
    ui->verticalLayout->addWidget(m_form);
//    qDebug() << "sizeof(QTextEdit)=======" << sizeof(QTextEdit);
//    qDebug() << "sizeof(QLabel)=======" << sizeof(QLabel);
//    qDebug() << "sizeof(QFrame)=======" << sizeof(QFrame);
    /*打开或创建的数据库实例句柄*/

    /*数据库文件的路径及文件名*/
    //const char* path = "./imchat.db";//D:\pc_im\bin32\release\data
    const char* path = "D:/project/qt/bin32/user.db";
    /*根据文件路径打开数据库连接。如果数据库不存在，则创建。数据库文件的路径必须以C字符串传入*/
    int result = sqlite3_open_v2(path, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);

    if (result == SQLITE_OK)
        qDebug() << "open or create database success===================";
    else
        qDebug() << "open or create database failed===================";

    sqlite3_close(db);

}

void MainWindow::initOpenData()
{
    //const char* path = "./imchat.db";
    //const char* pwd = "111111";
    const char* path = "D:/project/qt/bin32/user.db";
    const char* pwd = "333333";
    int result = -1;
    result = sqlite3_open(path, &db);

    if (result == SQLITE_OK)
        qDebug() << "open database success===================";
    else
        qDebug() << "open database failed===================";

    result = sqlite3_key(db, pwd, strnlen(pwd, 1000));
    qDebug() << "MainWindow::initOpenData() result===================" << result;
}

void MainWindow::initConnect()
{
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::slotSqlTest);
}

void MainWindow::selectData()
{
    char* errmsg;
    //查询总数
    int result = -1;
    //result = sqlite3_exec(db, "SELECT count(id) FROM t1;", callback, nullptr, &errmsg);
    //result = sqlite3_exec(db, "SELECT * FROM t1;", callback, this, &errmsg);
    result = sqlite3_exec(db, "SELECT * FROM account;", callback, this, &errmsg);
    //所有的结果要等回调完成后，才什么执行下面的操作
    if (result == SQLITE_OK)
        qDebug() << "select success===================";
    else
        qDebug() << "select failed===================" << sqlite3_errmsg(db);
    qDebug() << "opration finished===================";
}

void MainWindow::selectMessageTable(const QString &strSql, selectMessageTableCallback callback, void *pObj)
{
    qDebug() << "MainWindow::selectMessageTable=====strSql======" << strSql << "===line==" << __LINE__;
    char* errmsg;
    //查询总数
    int result = -1;
    char sql[1024] = {0};
    strcpy_s(sql, strSql.toUtf8().data());
    result = sqlite3_exec(db, sql, callback, pObj, &errmsg);
    //所有的结果要等回调完成后，才什么执行下面的操作
    if (result == SQLITE_OK)
        qDebug() << "select success===================";
    else
        qDebug() << "select failed===================" << sqlite3_errmsg(db);
}

void MainWindow::test()
{
    qDebug() << "opration test===================";
}

//https://blog.csdn.net/fangye945a/article/details/86484547
void MainWindow::slotSqlTest()
{
    qDebug() << "slotSqlTest =============selectData======";
    //const char* path = "D:/project/qt/bin32/user.db";
    QString accountDir = "D:/project/qt/bin32/user.db";//length = 12

    //strlen不包括最后的结束符
    char dbPath[1024] = {0};
    strcpy_s(dbPath, accountDir.toUtf8().data());

    int result = 0; //返回值
    int nrow = 0;       //查询到数据的行数
    int ncolumn = 0;   //查询到数据的列数
    char **azResult;   //二维数组存放结果
    char *zErrMsg = nullptr; //错误信息
    char sql[1024] = {0};//sql语句
    QString sqlSelect = "SELECT * FROM account;";
    strcpy_s(sql, sqlSelect.toUtf8().data());

    //step 1: 打开数据库连接对象

    //step 2: sql语句对象。
    sqlite3_stmt *pStmt;
    result = sqlite3_prepare_v2(db, sql, static_cast<int>(strlen(sql)), &pStmt, nullptr);
    if (result != SQLITE_OK)
    {
        qDebug() << "sqlite3_prepare_v2 error:==================" << sqlite3_errmsg(db) << __LINE__;
        return;
    }

    result = sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg ); //查询数据库
    if( result != SQLITE_OK )
    {
        qDebug() << "sqlite3_prepare_v2 error:==================" << sqlite3_errmsg(db) << __LINE__;
        return;
    }

    qDebug() << "nrow =====" << nrow << " =====ncolumn=============" << ncolumn << __LINE__;

    if( nrow !=0 && ncolumn != 0 )     //有查询结果,不包含表头所占行数
    {
        int i=0,j=0;
        for(i=0; i<= nrow; i++)           //打印查询结果
        {
            if(i==0) //第0行为数据表头
            {
                qDebug("%s\t %s\t %s\t %s\t %s\t %s\t %s\t %s\t",
                       azResult[i+0], azResult[i+1], azResult[i+2], azResult[i+3], azResult[i+4]
                        , azResult[i+5], azResult[i+6], azResult[i+7]);

            }
            else
            {
                qDebug("%s\t %s\t %s\t %s\t %s\t %s\t %s\t %s\t",
                       azResult[i*nrow+0], azResult[i*nrow+1], azResult[i*nrow+2], azResult[i*nrow+3], azResult[i*nrow+4]
                        , azResult[i*nrow+5], azResult[i*nrow+6], azResult[i*nrow+7]);
            }

             qDebug() << "\n";
        }

    }
    sqlite3_free_table(azResult);     //释放掉 azResult的内存空间

    sqlite3_finalize(pStmt);     //销毁一个SQL语句对象

    //step 3: 关闭数据库连接对象
    //sqlite3_close(pdb);

    //selectData();
}

//插入数据
//QString strSql = QString("INSERT INTO account(uid,pwd,loginState,recordPwd,autoLogin,lastLogin)VALUES('%1', '%2', 1, %3, %4, 1);")
//.arg(m_accountInfo.strUid).arg(m_accountInfo.strPwd).arg(m_accountInfo.recordPwd).arg(m_accountInfo.autoLogin);

//更新数据
//QString strSql = QString("UPDATE account SET recordPwd = %1, autoLogin = %2 WHERE uid = '%3';")
//.arg(m_accountInfo.recordPwd).arg(m_accountInfo.autoLogin).arg(m_accountInfo.strUid);

//创建表
//const char *sqlchar = "CREATE TABLE IF NOT EXISTS account(id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, uid TEXT NOT NULL,
//phone TEXT, pwd TEXT, loginState int, recordPwd int, autoLogin int, lastLogin int64);";

//删除数据
//QString sqlDelete = QString("DELETE FROM account WHERE uid=%1;").arg(m_nUid);
