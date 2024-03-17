#include "usermgr.h"

UserMgr::UserMgr()
{

}

bool UserMgr::add(QString user, QString pass)
{
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
