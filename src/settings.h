#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

#define CONFIG_FILE "/etc/lightdm/lightdm-dynamic-greeter.conf"
#define BACKGROUND_IMAGE_KEY "greeter-background-image"

class Settings : public QSettings
{
public:
	explicit Settings();
	[[nodiscard]] QString getChosenWallpapersPath() const;
private:
	QSettings* settings;
	[[nodiscard]] QString getCollectionDirectory() const;
};

#endif // SETTINGS_H
