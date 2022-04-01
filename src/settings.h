#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

#define CONFIG_FILE "/etc/lightdm/lightdm-dynamic-greeter.conf"

class Settings : public QSettings
{
public:
	explicit Settings();
	[[nodiscard]] QString getChosenWallpapersPath() const;

	enum class ResizeMode {
		SCALE,
		CENTER,
		ZOOM,
		ZOOM_FILL
	};
	Q_ENUM(ResizeMode);

	[[nodiscard]] ResizeMode getResizeMode() const;

private:
	QSettings* settings;
	[[nodiscard]] QString getCollectionDirectory() const;
};

#endif // SETTINGS_H
