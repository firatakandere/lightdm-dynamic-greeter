#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <QObject>
#include <QHash>
#include <QScreen>

#include "mainwindow.h"
#include "backgroundmanager.h"
#include "settings.h"

class ScreenManager : public QObject
{
    Q_OBJECT
public:
    explicit ScreenManager(BackgroundManager *backgroundManager, Settings& settings, QObject *parent = nullptr);

public slots:
    void onScreenAdded(QScreen *screen);
    void onScreenRemoved(QScreen *screen);
    void onPrimaryScreenChanged(QScreen *screen);
    void onBackgroundUpdated(const QImage *image);

signals:
    void backgroundUpdated(const QImage* image, Settings::ResizeMode resizeMode, QColor &backgroundColor);

private:
    void addScreen(QScreen *screen);
    QScreen* currentPrimaryScreen;
    QHash<QScreen*, MainWindow*> screenWindowMap;
    BackgroundManager* m_BackgroundManager;

    Settings::ResizeMode resizeMode;
    QColor backgroundColor;

signals:

};

#endif // SCREENMANAGER_H
