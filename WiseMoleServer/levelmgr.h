#ifndef LEVELMGR_H
#define LEVELMGR_H

#include <QString>
#include <QMap>
#include <QtSql/QSqlDatabase>

struct LevelData
{
    int id; // ID уровня, -1, при ошибке
    QString username; // Логин пользователя
    QString name; // Название уровня
    QString data; // Карта уровня
};

class LevelMgr
{
public:
    LevelMgr();
    void set_my_db(QSqlDatabase &db);
    QMap<int, QString> get_name_list();
    LevelData get_level(int lvl_id);
    bool save_level(int user_id, QString name, QString data);
    QString get_last_error();

private:
    QSqlDatabase my_db;
    QString err_msg = "";
};

#endif // LEVELMGR_H
