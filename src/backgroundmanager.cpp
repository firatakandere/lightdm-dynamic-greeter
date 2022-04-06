#include <QDateTime>
#include <QtDebug>
#include <QImageReader>
#include <QImage>

#include "backgroundmanager.h"

BackgroundManager::BackgroundManager(const QString& wallpapersDirectory, QObject *parent)
    : QObject{parent},
      m_WallpapersDirectory{wallpapersDirectory}
{
    timer = new QTimer(this);
    timer->setSingleShot(true);
}

void BackgroundManager::resetTimer()
{
    int timeUntilNext = 60 - QDateTime::currentDateTime().time().minute();
    int microsecondsUntilNext = timeUntilNext * 60 * 1000;
    timer->singleShot(microsecondsUntilNext, [=](){
        updateBackground();
        resetTimer();
    });
    timer->start();
    qDebug() << "Timer has been reset. It'll be called again in" << timeUntilNext << "minutes.";
}

void BackgroundManager::updateBackground()
{
    int hour = QDateTime::currentDateTime().time().hour();

    // Get filepath for image
    QStringList expectedFileNames;
    for (const QString extension : QImageReader::supportedImageFormats())
    {
        expectedFileNames << QString("%1.%2").arg(hour).arg(extension);
    }

    auto matchedFiles = m_WallpapersDirectory.entryInfoList(expectedFileNames, QDir::Files | QDir::Readable);

    if (matchedFiles.empty())
    {
        qWarning() << "No files is matched for background, background won't be updated.";
        return;
    }

    auto image = new QImage(matchedFiles.at(0).absoluteFilePath());

    if (image->isNull())
    {
        qWarning() << "Could not read image file from" << matchedFiles.at(0);
        qWarning() << "Background won't be updated.";
        return;
    }

    emit backgroundUpdated(image);
}

void BackgroundManager::initialize()
{
    if (!m_WallpapersDirectory.exists())
    {
        qWarning() << "Wallpaper directory is not found, wallpapers won't be set. Directory:" << m_WallpapersDirectory;
        return;
    }

    updateBackground();
    resetTimer();
}

BackgroundManager::~BackgroundManager()
{
    delete timer;
}
