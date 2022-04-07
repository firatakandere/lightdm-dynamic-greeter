#include <QRect>
#include <QScreen>
#include <QImage>
#include <QSettings>
#include <QDebug>
#include <QPushButton>
#include <QIcon>

#include "mainwindow.h"
#include "wallpaperresize.h"
#include "powercontrols.h"

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

void MainWindow::drawPowerControls()
{
    m_PowerControls = new PowerControls(this);
    QRect screenRect = m_Screen->geometry();

    auto powerButton = new QPushButton(this);
    powerButton->setIcon(QIcon(":/icons/power.svg"));
    powerButton->setIconSize(QSize(65, 65));
    powerButton->setStyleSheet("background-color: transparent; border: 0px");
    powerButton->adjustSize();

    int power_x = screenRect.width() - powerButton->width();
    int power_y = screenRect.height() - powerButton->height();

    powerButton->move(power_x, power_y);

    m_PowerControls->adjustSize();
    int controls_x = screenRect.width() - m_PowerControls->width();
    int controls_y = power_y - m_PowerControls->height();


    m_PowerControls->move(controls_x, controls_y);

    connect(powerButton, &QPushButton::clicked, m_PowerControls, &QWidget::show);
}

void MainWindow::undrawPowerControls()
{
    delete m_PowerControls;
}

void MainWindow::drawPrimaryScreenElements()
{
    drawAuthForm();
    drawPowerControls();
}

void MainWindow::undrawPrimaryScreenElements()
{
    undrawAuthForm();
    undrawPowerControls();
}

MainWindow::~MainWindow()
{
    delete m_AuthForm;
    delete m_PowerControls;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (!m_PowerControls->underMouse())
    {
        m_PowerControls->hide();
    }

    QWidget::mousePressEvent(event);
}
