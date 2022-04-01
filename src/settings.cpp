#include <QDir>
#include <QDebug>

#include "settings.h"

Settings::Settings()
{
	settings = new QSettings(CONFIG_FILE, QSettings::IniFormat, this);
}

QString Settings::getCollectionDirectory() const
{
	if (!settings->contains("greeter/collection_path"))
	{
		qWarning() << "collection_path setting is missing in configuration file, fallback to default value";
	}
	return settings->value("greeter/collection_path", QString("/usr/share/lightdm-dynamic-greeter/wallpapers")).toString();
}

QString Settings::getChosenWallpapersPath() const
{
	if (!settings->contains("greeter/wallpaper"))
	{
		qWarning() << "wallpaper setting is missing in configuration file, fallback to default value";
	}
	QString chosenWallpaper = settings->value("greeter/wallpaper", QString("lakeside")).toString();
	return QDir::cleanPath(getCollectionDirectory() + QDir::separator() + chosenWallpaper);
}
