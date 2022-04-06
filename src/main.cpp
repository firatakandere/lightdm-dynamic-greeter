#include <QApplication>
#include <QHash>
#include <QScreen>

#include "backgroundmanager.h"
#include "settings.h"
#include "screenmanager.h"

// qDebug does not output to console anymore
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    std::string phrase;

    switch (type)
    {
        case QtDebugMsg:
            phrase = "Debug";
            break;
        case QtInfoMsg:
            phrase = "Info";
            break;
        case QtWarningMsg:
            phrase = "Waring";
            break;
        case QtCriticalMsg:
            phrase = "Critical";
            break;
        case QtFatalMsg:
            phrase = "Fatal";
            break;
    }

    fprintf(stderr, "%s: %s (%s:%u, %s)\n", phrase.c_str(), localMsg.constData(), file, context.line, function);
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(customMessageHandler);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    Settings settings;
    auto backgroundManager = new BackgroundManager(settings.getChosenWallpapersPath());
    auto screenManager = new ScreenManager(backgroundManager, settings);

    QObject::connect(&a, &QApplication::screenAdded, screenManager, &ScreenManager::onScreenAdded);
    QObject::connect(&a, &QApplication::screenRemoved, screenManager, &ScreenManager::onScreenRemoved);
    QObject::connect(&a, &QApplication::primaryScreenChanged, screenManager, &ScreenManager::onPrimaryScreenChanged);

    return a.exec();
}
