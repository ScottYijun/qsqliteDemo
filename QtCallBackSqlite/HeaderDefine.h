#ifndef HEADERDEFINE_H
#define HEADERDEFINE_H

#include <QString>
#include <QMetaType>
#include <QDateTime>


extern QString strExePath;

#define PrintTime (QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"))

#define g_pMainControl CMainControl::getInstance()

#define USEOBJECT(x) if(x == nullptr) return;


const qint64 g_millisecond = 24 * 60 * 60 * 1000;   //1ÃÏªªÀ„≥…∫¡√Î
const qint64 g_second = 24 * 60 * 60;               //1ÃÏªªÀ„≥…√Î


typedef struct STAccountData
{
    QString strUid{""};
    QString strPhone{""};
    QString strPwd{""};
    int loginState{0};
    int recordPwd{0};
    int autoLogin{0};
    qint64 lastLogin{0};
}AccountInfo;


Q_DECLARE_METATYPE(AccountInfo)
#endif // HEADERDEFINE_H
