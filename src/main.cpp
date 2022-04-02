#include <QApplication>

#include "mainwindow.h"
#include "backgroundmanager.h"
#include "settings.h"

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

	BackgroundManager backgroundManager(settings.getChosenWallpapersPath());
	Settings::ResizeMode resizeMode = settings.getResizeMode();

	for (auto screen : a.screens())
	{
		auto mainWindow = new MainWindow(screen);
		if (screen == a.primaryScreen())
		{
			mainWindow->setFocus();
			mainWindow->activateWindow();
			mainWindow->show(true);
		}
		else
		{
			mainWindow->show(false);
		}
		QObject::connect(&backgroundManager, &BackgroundManager::backgroundUpdated, [mainWindow, resizeMode](const QImage* image){
			mainWindow->setBackground(image, resizeMode);
		});
	}

	backgroundManager.initialize();
	return a.exec();
}
