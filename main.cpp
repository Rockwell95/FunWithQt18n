#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include <QUrl>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QtSandbox_" + QLocale(locale).name();

#if defined(Q_OS_LINUX)
            // On Linux the translations can be found in /usr/share/worktracker/l10n.
            auto i18nPath = "/../share/worktracker/i18n/";
#elif defined (Q_OS_WIN)
            // On Windows the translations are in the l10n folder in the exe dir.
            auto i18nPath = "/i18n/";
#elif defined (Q_OS_MAC)
            // On OS X the data is somewhere in the bundle.
            auto i18nPath = "/../Resources/i18n/";
#endif
            auto appDir = QApplication::applicationDirPath() + i18nPath;

            qDebug() << appDir;

        if (translator.load(appDir + baseName)) {
            a.installTranslator(&translator);
            break;
        }

    }
    MainWindow w;
    w.show();
    return a.exec();
}
