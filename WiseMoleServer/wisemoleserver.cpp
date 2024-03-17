#include "wisemoleserver.h"
#include <QSettings>
#include <QFile>
#include <QDir>

WiseMoleServer::WiseMoleServer()
{

}

WiseMoleServer::~WiseMoleServer()
{

}

void WiseMoleServer::run()
{
    qDebug() << "Сервер игры Мудрый крот";
    qDebug() << "Версия " << version;

    // Загрузим настройки
    unsigned int load_sett_res = loadSettings();
    if(load_sett_res > 0)
    {
        qWarning() << "Ошибка загрузки файла настроек!";
        if(load_sett_res == 1)
        {
            // Нет файла настроек, генерируем
            qWarning() << "Генерирую шаблон " << settings_path;

            genSettings();
        }

        qWarning() << "Проверьте настройки и перезапустите приложение";
        exit(EXIT_FAILURE);
    }

    srv.route("/", [] () {
        QString info_msg = "<html>"
                "<head>"
                "<meta charset=\"utf-8\"/>"
                "<title>Сервер игры Wise Mole Qt</title>"
                "</head>"
                "<body>"
                "<p>"
                    "Данный сервер хранит уровни к игре, для их получения"
                    " и игры воспользуйтесь клиентом Wise Mole Qt"
                "</p>"
                "</body>"
            "</html>";
        return info_msg;
    });

    srv.route("/reg_user", [] () {
        QString info_msg = "Регистрация пользователя";
        return info_msg;
    });

    srv.route("/auth_user", [] () {
        QString info_msg = "Авторизация пользователя с выдачей токена";
        return info_msg;
    });

    srv.route("/list_levels", [] () {
        QString info_msg = "Список возможных уровней в JSON";
        return info_msg;
    });

    srv.route("/get_level", [] () {
        QString info_msg = "Получить карту уровня в JSON";
        return info_msg;
    });

    srv.route("/save_level", [] () {
        QString info_msg = "Сохранить уровень на сервере в JSON (нужен токен!)";
        return info_msg;
    });

    srv.listen(QHostAddress(host), port);

    qDebug() << "Сервер доступен с IP " << host
             << ", занимает порт " << port;
}

unsigned int WiseMoleServer::loadSettings()
{
    if(QFile::exists(settings_path)) {
        QSettings qsett(settings_path, QSettings::NativeFormat);
        host = qsett.value("host", "0.0.0.0").toString();
        port = qsett.value("port", 0).toInt();

        if(port > 0)
        {
            return 0;
        }
        else
        {
            qCritical() << "Задайте корректный порт подключения в настройках!";
            return 2;
        }
    }

    return 1;
}

void WiseMoleServer::genSettings()
{
    QSettings qsett(settings_path, QSettings::NativeFormat);
    qsett.clear();
    qsett.setValue("host", "0.0.0.0");
    qsett.setValue("port", 0);
}
