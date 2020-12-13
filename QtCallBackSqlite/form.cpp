#include "form.h"
#include "ui_form.h"
#include <QDebug>
#include "mainwindow.h"

int selectCallback(void *pSender, int argc, char **argv, char **azColName)
{
    Form *pObj = static_cast<Form *>(pSender);

    AccountInfo info;
    info.strUid = argv[1];
    info.strPhone = argv[2];
    info.strPwd = argv[3];
    info.loginState = QString(argv[4]).toInt();
    info.recordPwd = QString(argv[5]).toInt();
    info.autoLogin = QString(argv[6]).toInt();
    info.lastLogin = QString(argv[7]).toLongLong();

    pObj->addAccountInfo(info);

    qDebug() << "selectCallback=====argc======" << argc;
    for (int i = 0; i < argc; i++)
    {
        QString strColName = QString(azColName[i]);
        QString strValue = QString(argv[i]);
        qDebug()<< QStringLiteral("(ÁÐÃû)") << strColName << QStringLiteral("(Öµ):") << strValue << "\t";
    }
    return 0;
}


Form::Form(MainWindow *mainWindow, QWidget *parent)
    :QWidget(parent)
    ,ui(new Ui::Form)
    ,m_pMainWindod(mainWindow)
{
    ui->setupUi(this);
    initData();
}

Form::~Form()
{
    delete ui;
}

void Form::initData()
{
    m_pCodec = QTextCodec::codecForName( "gb2312" );
    //codec = QTextCodec::codecForName( "utf-8" );
    connect(ui->pushButton_select, &QPushButton::clicked, this, &Form::slotSelectAccount);
    connect(ui->pushButton_total, &QPushButton::clicked, this, &Form::slotTotalAccount);
}

void Form::addAccountInfo(AccountInfo info)
{
    m_vecAccountInfo.append(info);
}


void Form::slotSelectAccount()
{
    qDebug() << "Form::slotSelectAccount=================================";
    QString strSql = "SELECT * FROM account;";
    m_pMainWindod->selectMessageTable(strSql, selectCallback, this);
}

void Form::slotTotalAccount()
{
    qDebug() << "Form::slotTotalAccount==================m_vecAccountInfo.size===============" << m_vecAccountInfo.size();
}
