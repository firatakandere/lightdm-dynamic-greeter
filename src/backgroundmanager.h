#ifndef BACKGROUNDMANAGER_H
#define BACKGROUNDMANAGER_H

#include <QTimer>
#include <QObject>
#include <QImage>
#include <QDir>

class BackgroundManager : public QObject
{
    Q_OBJECT
public:
    explicit BackgroundManager(const QString& wallpapersDirectory, QObject *parent = nullptr);
    void initialize();
private:
    QTimer *timer;
    void resetTimer();
    QDir m_WallpapersDirectory;
    void updateBackground();
signals:
    void backgroundUpdated(const QImage*);
};

#endif // BACKGROUNDMANAGER_H
