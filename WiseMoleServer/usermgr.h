#ifndef USERMGR_H
#define USERMGR_H

#include <QCoreApplication>
#include <QString>

class UserMgr
{
public:
    UserMgr();
    bool add(QString user, QString pass);
    QString auth(QString user, QString pass);
    int auth(QString token);
    bool chg_pass(QString token, QString old_pass, QString pass);
    bool remove(QString user);
    QString get_last_error();

private:
    QString err_msg = "";
};

#endif // USERMGR_H
