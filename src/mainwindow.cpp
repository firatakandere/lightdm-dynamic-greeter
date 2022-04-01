#include <QGuiApplication>
#include <QRect>
#include <QScreen>
#include <QImage>
#include <QSettings>
#include <QDebug>

#include "mainwindow.h"
#include "settings.h"
#include "authform.h"

MainWindow::MainWindow(size_t screen, QWidget *parent)
	: QWidget{parent},
	  m_Screen{screen}
{

	setObjectName(QString("MainWindow_%1").arg(m_Screen));

	QRect screenRect = QGuiApplication::screens().at(screen)->geometry();
	setGeometry(screenRect);

	if (isPrimaryScreen())
	{
		auto authForm = new AuthForm(this);

		int max_x = screenRect.width() - authForm->width();
		int max_y = screenRect.height() - authForm->height();
		int default_x = max_x / 10;
		int default_y = max_y / 2;

		// @todo custom add offsets
		authForm->move(default_x, default_y);
		authForm->show();
		authForm->setFocus();

		// put cursor to the middle of primary screen
		int cursor_x = screenRect.width() / 2 + screenRect.x();
		int cursor_y = screenRect.height() / 2 + screenRect.y();
		QCursor::setPos(cursor_x, cursor_y);
	}
}

bool MainWindow::isPrimaryScreen() const
{
	return QGuiApplication::screens().at(m_Screen) == QGuiApplication::primaryScreen();
}

void MainWindow::setBackground(const QImage* backgroundImage)
{
	QPalette palette;
	QRect rect = QGuiApplication::screens().at(m_Screen)->geometry();

	if (backgroundImage->isNull())
	{
		palette.setColor(QPalette::Window, Qt::black);
	}
	else
	{
		QBrush brush(backgroundImage->scaled(rect.width(), rect.height()));
		palette.setBrush(backgroundRole(), brush);
	}

	this->setPalette(palette);
}
