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
