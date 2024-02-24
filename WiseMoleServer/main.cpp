#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include "wisemoleserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    WiseMoleServer wms;

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "WiseMoleServer_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    wms.run();

    return a.exec();
}
