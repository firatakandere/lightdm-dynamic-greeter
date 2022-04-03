#include <QDir>
#include <QDebug>

#include "cache.h"

Cache::Cache(QObject *parent)
    : QSettings(CACHE_FILE, QSettings::IniFormat, parent)
{
    QDir cacheDir;
    if (cacheDir.mkpath(CACHE_PATH))
    {
        qWarning() << "Could not create cache directory" << CACHE_PATH;
    }
}

QString Cache::getLastUser(const QString& defaultValue) const
{
    return value("last_user", defaultValue).toString();
}

void Cache::setLastUser(const QString& username)
{
    setValue("last_user", username);
    sync();
}
