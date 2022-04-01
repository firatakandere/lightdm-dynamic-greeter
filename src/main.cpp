#include <QApplication>

#include "mainwindow.h"
#include "backgroundmanager.h"
#include "settings.h"

int main(int argc, char *argv[])
{
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication a(argc, argv);

	Settings settings;

	BackgroundManager backgroundManager(settings.getChosenWallpapersPath());
	for (int i = 0; i < a.screens().count(); ++i)
	{
		auto mainWindow = new MainWindow(i);
		mainWindow->show();
		if (mainWindow->isPrimaryScreen())
		{
			mainWindow->setFocus();
			mainWindow->activateWindow();
		}
		QObject::connect(&backgroundManager, &BackgroundManager::backgroundUpdated, mainWindow, &MainWindow::setBackground);
	}

	backgroundManager.initialize();

	return a.exec();
}
