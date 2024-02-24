#ifndef WISEMOLESERVER_H
#define WISEMOLESERVER_H

#include <QCoreApplication>

class WiseMoleServer
{
public:
    WiseMoleServer();
    ~WiseMoleServer();
    void run();

private:
    const QString version = "0.1";
    QString host = "0.0.0.0";
    int port = 0;
    QString settings_path = "settings.ini";
    QString levels_path = "levels";
    QList<QString> l_levels = {};

    unsigned int loadSettings();
    void genSettings();
};

#endif // WISEMOLESERVER_H
