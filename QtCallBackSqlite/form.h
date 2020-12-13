#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QTextCodec>
#include <QVector>
#include "HeaderDefine.h"

namespace Ui {
class Form;
}

class MainWindow;

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(MainWindow *mainWindod, QWidget *parent = nullptr);
    ~Form();
    void initData();
    void addAccountInfo(AccountInfo info);

public slots:
    void slotSelectAccount();
    void slotTotalAccount();

private:
    Ui::Form *ui;
    MainWindow *m_pMainWindod;
    QTextCodec *m_pCodec;
    QVector<AccountInfo> m_vecAccountInfo;
};

#endif // FORM_H
