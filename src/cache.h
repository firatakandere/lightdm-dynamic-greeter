#ifndef CACHE_H
#define CACHE_H

#include <QSettings>

#define CACHE_PATH "/var/lib/lightdm/lightdm-dynamic-greeter"
#define CACHE_FILE CACHE_PATH "/cache.conf"

class Cache : QSettings
{
    Q_OBJECT
public:
    explicit Cache(QObject *parent = nullptr);
    [[nodiscard]] QString getLastUser(const QString& defaultValue) const;
    void setLastUser(const QString&);
};

#endif // CACHE_H
