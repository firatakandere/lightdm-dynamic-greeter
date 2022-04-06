#include <QDir>
#include <QDebug>
#include <QMetaEnum>

#include "settings.h"

#define CONFIG_FILE "/etc/lightdm/lightdm-dynamic-greeter.conf"

Settings::Settings(QObject *parent)
    : QSettings(CONFIG_FILE, QSettings::IniFormat, parent)
{
}

QString Settings::getCollectionDirectory() const
{
    if (!contains("greeter/collection_path"))
    {
        qWarning() << "collection_path setting is missing in configuration file, fallback to default value";
    }
    return value("greeter/collection_path", QString("/usr/share/lightdm-dynamic-greeter/wallpapers")).toString();
}

QString Settings::getChosenWallpapersPath() const
{
    if (!contains("greeter/wallpaper"))
    {
        qWarning() << "wallpaper setting is missing in configuration file, fallback to default value";
    }
    QString chosenWallpaper = value("greeter/wallpaper", QString("lakeside")).toString();
    return QDir::cleanPath(getCollectionDirectory() + QDir::separator() + chosenWallpaper);
}

Settings::ResizeMode Settings::getResizeMode() const
{
    auto defaultValue = Settings::ResizeMode::SCALE;
    if (!contains("greeter/resize_mode"))
    {
        qWarning() << "resize_mode setting is missing in configuration file, fallback to default value";

        return defaultValue;
    }

    auto stringValue = value("greeter/resize_mode").toString().toUpper();
    auto enumMeta = QMetaEnum::fromType<Settings::ResizeMode>();
    bool ok;

    auto resizingMode = static_cast<Settings::ResizeMode>(enumMeta.keyToValue(qPrintable(stringValue), &ok));

    if (!ok)
    {
        qWarning() << "Could not parse value" << stringValue << "for resizing, fallback to default value.";
        return defaultValue;
    }

    return resizingMode;
}

QColor Settings::getBackgroundColor() const
{
    if(!contains("greeter/background_color"))
    {
        qWarning() << "background_color is missing in configuration file, fallback to default value";
    }

    return value("greeter/background_color", "#FFFFFF").toString();
}
