#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QObject>
#include <QColor>

#define CONFIG_FILE "/etc/lightdm/lightdm-dynamic-greeter.conf"

class Settings : QSettings
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);
    [[nodiscard]] QString getChosenWallpapersPath() const;

    enum class ResizeMode {
        SCALE,
        CENTER,
        ZOOM,
        ZOOM_FILL
    };
    Q_ENUM(ResizeMode);

    [[nodiscard]] ResizeMode getResizeMode() const;

    [[nodiscard]] QColor getBackgroundColor() const;

private:
    [[nodiscard]] QString getCollectionDirectory() const;
};

#endif // SETTINGS_H
