#ifndef WISEMOLESERVER_H
#define WISEMOLESERVER_H

#include <QCoreApplication>
#include <QtNetwork/QTcpServer>
#include <QtHttpServer/QHttpServer>
#include <QtSql/QSqlDatabase>
#include "usermgr.h"
#include "levelmgr.h"

class WiseMoleServer
{
public:
    WiseMoleServer();
    ~WiseMoleServer();
    void run();

private:
    const QString version = "0.1";

    // Путь к файлу настроек
    QString settings_path = "settings.ini";

    // Настройки работы сервера
    QString host = "0.0.0.0";
    int port = 0;

    // Настройки подключения к БД
    QSqlDatabase my_db;
    QString db_host = "", db_user = "", db_pass = "", db_base = "";
    QString user_salt = "";

    QHttpServer srv;
    UserMgr usr_mgr;
    LevelMgr lvl_mgr;

    unsigned int loadSettings();
    void genSettings();
};

#endif // WISEMOLESERVER_H
