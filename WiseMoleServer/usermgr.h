#ifndef USERMGR_H
#define USERMGR_H

#include <QCoreApplication>
#include <QString>
#include <QtSql/QSqlDatabase>

class UserMgr
{
public:
    UserMgr();
    void set_my_db(QSqlDatabase &db);
    bool add(QString user, QString pass);
    QString auth(QString user, QString pass);
    int auth(QString token);
    bool chg_pass(QString token, QString old_pass, QString pass);
    bool remove(QString user);
    QString get_last_error();

private:
    QSqlDatabase my_db;
    QString err_msg = "";
};

#endif // USERMGR_H
