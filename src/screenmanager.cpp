#include "screenmanager.h"

#include <QApplication>

ScreenManager::ScreenManager(BackgroundManager *backgroundManager, Settings& settings, QObject *parent)
    : QObject{parent},
      screenWindowMap(),
      m_BackgroundManager{backgroundManager},
      resizeMode{settings.getResizeMode()},
      backgroundColor{settings.getBackgroundColor()}
{
    for (auto screen : QApplication::screens())
    {
        addScreen(screen);
    }

    connect(m_BackgroundManager, &BackgroundManager::backgroundUpdated, this, &ScreenManager::onBackgroundUpdated);

    m_BackgroundManager->initialize();
}

void ScreenManager::onScreenAdded(QScreen *screen)
{
    addScreen(screen);
    m_BackgroundManager->updateBackground();
}


void ScreenManager::onScreenRemoved(QScreen *screen)
{
    if (!screenWindowMap.contains(screen))
        return;

    auto mainWindow = screenWindowMap.take(screen);
    delete mainWindow;
}

void ScreenManager::onPrimaryScreenChanged(QScreen *screen)
{
    if (screen == currentPrimaryScreen)
        return;

    if (screenWindowMap.contains(currentPrimaryScreen))
    {
        screenWindowMap.value(currentPrimaryScreen)->undrawPrimaryScreenElements();
    }

    if (!screenWindowMap.contains(screen))
    {
        addScreen(screen);
    }

    screenWindowMap.value(screen)->drawPrimaryScreenElements();
    currentPrimaryScreen = screen;
}

void ScreenManager::addScreen(QScreen *screen)
{
    auto mainWindow = new MainWindow(screen);
    screenWindowMap.insert(screen, mainWindow);

    if (screen == QApplication::primaryScreen())
    {
        mainWindow->setFocus();
        mainWindow->activateWindow();
        mainWindow->drawPrimaryScreenElements();

        currentPrimaryScreen = screen;
    }

    connect(this, &ScreenManager::backgroundUpdated, mainWindow, &MainWindow::setBackground);

    mainWindow->show();
}

void ScreenManager::onBackgroundUpdated(const QImage* image)
{
    emit backgroundUpdated(image, resizeMode, backgroundColor);
}
