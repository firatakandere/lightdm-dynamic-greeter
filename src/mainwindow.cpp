#include <QRect>
#include <QScreen>
#include <QImage>
#include <QSettings>
#include <QDebug>

#include "mainwindow.h"
#include "authform.h"
#include "wallpaperresize.h"

MainWindow::MainWindow(QScreen *screen, QWidget *parent)
    : QWidget{parent},
      m_Screen{screen}
{

    setObjectName(QString("MainWindow_%1").arg(m_Screen->name()));
}

void MainWindow::setBackground(const QImage* backgroundImage, Settings::ResizeMode resizeMode)
{
    QPalette palette;
    QRect rect = m_Screen->geometry();

    if (backgroundImage->isNull())
    {
        palette.setColor(QPalette::Window, Qt::black);
    }
    else
    {
        QBrush brush(WallpaperResize::resize_wallpaper(*backgroundImage, rect.width(), rect.height(), resizeMode));
        palette.setBrush(backgroundRole(), brush);
    }

    this->setPalette(palette);
}

void MainWindow::show(bool isPrimaryScreen)
{
    QRect screenRect = m_Screen->geometry();
    setGeometry(screenRect);

    if (isPrimaryScreen)
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

    QWidget::show();
}
