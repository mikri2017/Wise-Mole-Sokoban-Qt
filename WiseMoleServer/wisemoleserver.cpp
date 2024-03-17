#include "wisemoleserver.h"
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QJsonObject>

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

    srv.route("/reg_user", QHttpServerRequest::Method::Post, [] (const QHttpServerRequest &req) {
        // Расшифровка полученных параметров запроса
        QUrlQuery uq = QUrlQuery(req.body());

        QJsonObject j_resp;
        j_resp.insert("res", "ok");

        if(uq.hasQueryItem("login") && uq.hasQueryItem("password")) {
            QString info_msg = "Запрошена регистрация пользователя " + uq.queryItemValue("login") \
                + " с паролем " + uq.queryItemValue("password");
            j_resp.insert("msg", info_msg);
        } else {
            QString err_msg = "Отcутствуют необходимые параметры!";
            j_resp.insert("msg", err_msg);
        }

        return j_resp;
    });

    srv.route("/auth_user", QHttpServerRequest::Method::Post, [] (const QHttpServerRequest &req) {
        // Расшифровка полученных параметров запроса
        QUrlQuery uq = QUrlQuery(req.body());

        QJsonObject j_resp;
        j_resp.insert("res", "ok");

        if(uq.hasQueryItem("login") && uq.hasQueryItem("password")) {
            QString info_msg = "Запрошена авторизация пользователя " + uq.queryItemValue("login") \
                + " с паролем " + uq.queryItemValue("password");

            j_resp.insert("msg", info_msg);
        } else {
            QString err_msg = "Отcутствуют необходимые параметры!";
            j_resp.insert("msg", err_msg);
        }

        return j_resp;
    });

    srv.route("/list_levels", QHttpServerRequest::Method::Get, [] () {
        QJsonObject j_resp;
        j_resp.insert("res", "ok");
        j_resp.insert("msg", "Список возможных уровней в JSON");
        return j_resp;
    });

    srv.route("/get_level", QHttpServerRequest::Method::Get, [] (const QHttpServerRequest &req) {
        // Расшифровка полученных парамеров запроса
        QUrlQuery uq = QUrlQuery(req.body());

        QJsonObject j_resp;
        j_resp.insert("res", "ok");

        if(uq.hasQueryItem("lvl_id")) {
            QString info_msg = "Выгрузка уровня ID" + uq.queryItemValue("lvl_id");
            j_resp.insert("msg", info_msg);
        } else {
            QString err_msg = "Отcутствуют необходимые параметры!";
            j_resp.insert("msg", err_msg);
        }

        return j_resp;
    });

    srv.route("/save_level", QHttpServerRequest::Method::Post, [] (const QHttpServerRequest &req) {
        // Расшифровка полученных парамеров запроса
        QUrlQuery uq = QUrlQuery(req.body());

        QJsonObject j_resp;
        j_resp.insert("res", "ok");

        if(uq.hasQueryItem("token") && uq.hasQueryItem("lvl_name") && uq.hasQueryItem("lvl_data")) {
            QString info_msg = "Передача на сервер уровня " + uq.queryItemValue("lvl_name") \
                + " по токену пользователя " + uq.queryItemValue("token");
            j_resp.insert("msg", info_msg);
        } else {
            QString err_msg = "Отcутствуют необходимые параметры!";
            j_resp.insert("msg", err_msg);
        }

        return j_resp;
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
