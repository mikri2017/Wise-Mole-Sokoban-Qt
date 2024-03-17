#include "usermgr.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

UserMgr::UserMgr()
{

}

void UserMgr::set_my_db(QSqlDatabase &db)
{
    my_db = db;
}

bool UserMgr::add(QString user, QString pass)
{
    bool db_opened = my_db.open();
    if(!db_opened) {
        err_msg = my_db.lastError().text();
        return false;
    }

    QSqlQuery query("select variable from sys_config");
    while (query.next()) {
       qDebug() << query.value(0).toString() << "\n";
    }

    my_db.close();

    return true;
}

QString UserMgr::auth(QString user, QString pass)
{
    return "token";
}

int UserMgr::auth(QString token)
{
    return 0;
}

bool UserMgr::chg_pass(QString token, QString old_pass, QString pass)
{
    return true;
}

bool UserMgr::remove(QString user)
{
    return true;
}

QString UserMgr::get_last_error()
{
    return err_msg;
}
