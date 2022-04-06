#include <QRect>
#include <QScreen>
#include <QImage>
#include <QSettings>
#include <QDebug>

#include "mainwindow.h"
#include "wallpaperresize.h"

MainWindow::MainWindow(const QScreen *screen, QWidget *parent)
    : QWidget{parent},
      m_Screen{screen}
{

    setObjectName(QString("MainWindow_%1").arg(m_Screen->name()));
    QRect screenRect = m_Screen->geometry();
    setGeometry(screenRect);
}

void MainWindow::setBackground(const QImage* backgroundImage, const Settings::ResizeMode resizeMode, const QColor& bgColor)
{
    QPalette palette;
    QRect rect = m_Screen->geometry();

    if (backgroundImage->isNull())
    {
        palette.setColor(QPalette::Window, bgColor);
    }
    else
    {
        QBrush brush(WallpaperResize::resize_wallpaper(*backgroundImage, bgColor, rect.width(), rect.height(), resizeMode));
        palette.setBrush(backgroundRole(), brush);
    }

    this->setPalette(palette);
}

void MainWindow::drawAuthForm()
{
    QRect screenRect = m_Screen->geometry();
    m_AuthForm = new AuthForm(this);

    int max_x = screenRect.width() - m_AuthForm->width();
    int max_y = screenRect.height() - m_AuthForm->height();
    int default_x = max_x / 10;
    int default_y = max_y / 2;

    // @todo custom add offsets
    m_AuthForm->move(default_x, default_y);
    m_AuthForm->show();
    m_AuthForm->setFocus();

    // put cursor to the middle of primary screen
    int cursor_x = screenRect.width() / 2 + screenRect.x();
    int cursor_y = screenRect.height() / 2 + screenRect.y();
    QCursor::setPos(cursor_x, cursor_y);
}

void MainWindow::undrawAuthForm()
{
    delete m_AuthForm;
}

MainWindow::~MainWindow()
{
    delete m_AuthForm;
    delete m_Screen;
}
