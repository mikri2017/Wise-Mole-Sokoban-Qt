#include "levelmgr.h"

LevelMgr::LevelMgr()
{

}

void LevelMgr::set_my_db(QSqlDatabase &db)
{
    my_db = db;
}

QMap<int, QString> LevelMgr::get_name_list()
{
    return QMap<int, QString>();
}

LevelData LevelMgr::get_level(int lvl_id)
{
    LevelData lvl_d;
    lvl_d.id = -1;
    lvl_d.name = "";
    lvl_d.username = "";
    lvl_d.data = "";
    return lvl_d;
}

bool LevelMgr::save_level(int user_id, QString name, QString data)
{
    return true;
}

QString LevelMgr::get_last_error()
{
    return err_msg;
}
