#include "wisemoleserver.h"
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonArray>

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

    srv.route("/reg_user", QHttpServerRequest::Method::Post, [this] (const QHttpServerRequest &req) {
        // Расшифровка полученных параметров запроса
        QUrlQuery uq = QUrlQuery(req.body());

        QJsonObject j_resp;
        j_resp.insert("res", "ok");

        if(uq.hasQueryItem("login") && uq.hasQueryItem("password")) {
            bool res = usr_mgr.add(
                uq.queryItemValue("login"),
                uq.queryItemValue("password")
            );

            if(res == false) {
                j_resp.insert("res", "err");
                j_resp.insert("msg", usr_mgr.get_last_error());
            }
        } else {
            j_resp.insert("res", "err");

            QString err_msg = "Отcутствуют необходимые параметры!";
            j_resp.insert("msg", err_msg);
        }

        return j_resp;
    });

    srv.route("/auth_user", QHttpServerRequest::Method::Post, [this] (const QHttpServerRequest &req) {
        // Расшифровка полученных параметров запроса
        QUrlQuery uq = QUrlQuery(req.body());

        QJsonObject j_resp;
        j_resp.insert("res", "ok");

        if(uq.hasQueryItem("login") && uq.hasQueryItem("password")) {
            QString token = usr_mgr.auth(
                uq.queryItemValue("login"),
                uq.queryItemValue("password")
            );

            if(token == "") {
                j_resp.insert("res", "err");
                j_resp.insert("msg", usr_mgr.get_last_error());
            }

            j_resp.insert("token", token);
        } else {
            QString err_msg = "Отcутствуют необходимые параметры!";
            j_resp.insert("msg", err_msg);
        }

        return j_resp;
    });

    srv.route("/chg_user_pass", QHttpServerRequest::Method::Post, [this] (const QHttpServerRequest &req) {
        // Расшифровка полученных параметров запроса
        QUrlQuery uq = QUrlQuery(req.body());

        QJsonObject j_resp;
        j_resp.insert("res", "ok");

        if(uq.hasQueryItem("token") && uq.hasQueryItem("old_password") && uq.hasQueryItem("password")) {
            bool res = usr_mgr.chg_pass(
                uq.queryItemValue("token"),
                uq.queryItemValue("old_password"),
                uq.queryItemValue("password")
            );

            if(res == false) {
                j_resp.insert("res", "err");
                j_resp.insert("msg", usr_mgr.get_last_error());
            }
        } else {
            QString err_msg = "Отcутствуют необходимые параметры!";
            j_resp.insert("msg", err_msg);
        }

        return j_resp;
    });

    srv.route("/list_levels", QHttpServerRequest::Method::Get, [this] () {
        QJsonObject j_resp;
        j_resp.insert("res", "ok");

        QMap<int, QString> lvl_list = lvl_mgr.get_name_list();
        QJsonObject j_lvl_list;
        for (auto [key, val] : lvl_list.asKeyValueRange()) {
            j_lvl_list.insert(QString::number(key), val);
        }

        j_resp.insert("items", j_lvl_list);
        return j_resp;
    });

    srv.route("/get_level", QHttpServerRequest::Method::Get, [this] (const QHttpServerRequest &req) {
        // Расшифровка полученных парамеров запроса
        QUrlQuery uq = QUrlQuery(req.body());

        QJsonObject j_resp;
        j_resp.insert("res", "ok");

        if(uq.hasQueryItem("lvl_id")) {
            LevelData lvl = lvl_mgr.get_level(uq.queryItemValue("lvl_id").toInt());

            j_resp.insert("lvl_id", lvl.id);
            j_resp.insert("lvl_user", lvl.username);
            j_resp.insert("lvl_name", lvl.name);
            j_resp.insert("lvl_data", lvl.data);
        } else {
            QString err_msg = "Отcутствуют необходимые параметры!";
            j_resp.insert("msg", err_msg);
        }

        return j_resp;
    });

    srv.route("/save_level", QHttpServerRequest::Method::Post, [this] (const QHttpServerRequest &req) {
        // Расшифровка полученных парамеров запроса
        QUrlQuery uq = QUrlQuery(req.body());

        QJsonObject j_resp;
        j_resp.insert("res", "ok");

        if(uq.hasQueryItem("token") && uq.hasQueryItem("lvl_name") && uq.hasQueryItem("lvl_data")) {
            int user_id= usr_mgr.auth(uq.queryItemValue("token"));
            if(user_id == 0) {
                j_resp.insert("res", "err");
                j_resp.insert("msg", usr_mgr.get_last_error());
            } else {
                // Авторизация по токену успешна, сохраняем уровень
                bool res = lvl_mgr.save_level(user_id, uq.queryItemValue("lvl_name"), uq.queryItemValue("lvl_data"));
                if(res == false) {
                    j_resp.insert("res", "err");
                    j_resp.insert("msg", lvl_mgr.get_last_error());
                }
            }
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
