A QT-based LightDM Greeter that changes background based on time.

### Current Functionality

- Login with username & password (click on username to type username).
- Background (wallpaper) changes dynamically based on time.
- Wallpaper resizing modes (scaled, zoomed, zoom_filled, centered).
- Remembers last logged in username.
- Supports multipe screens.

### Missing Functionality
- Session selection
- Setting background color (for zoomed and centered)
- Guest account
- Power controls
- Settings UI
- Monitor/screen change detection
- Custom offsets for auth form.

### Build & Installation

#### Dependencies
- Qt5 development environment, QtWidgets module is needed (Qt6 will probably work as well).
- CMake
- LightDM
- [liblightdm-qt](https://github.com/canonical/lightdm/tree/main/liblightdm-qt) (build only)

#### Build

```
cmake .
make
sudo make install
```

#### How to Add Wallpapers
Wallpapers are stored under `/usr/share/lightdm-dynamic-greeter/wallpapers` path. Each wallpaper collection should be stored in individual folder.
Desired wallpaper's folder name should be used to set `wallpaper` parameter in configuration file.

##### File Structure
- Each wallpaper folder should include 24 files.
- Each file should be named with an integer from 0 to 23 (no zero-padding), where the number represents the hour-clock that the file is displayed.
- If there are not 24 files, symbolic lcinks from other files can be used to save space instead of duplicating files.


##### Supported Formats

| Format | MIME type                | Description                      |
| ------ | ------------------------ | -------------------------------- |
| BMP    | image/bmp                | Windows Bitmap                   |
| GIF    | image/gif                | Graphic Interchange Format       |
| JPG    | image/jpeg               | Joint Photographic Experts Group |
| PNG    | image/png                | Portable Network Graphics        |
| PBM    | image/x-portable-bitmap  | Portable Bitmap                  |
| PGM    | image/x-portable-graymap | Portable Graymap                 |
| PPM    | image/x-portable-pixmap  | Portable Pixmap                  |
| XBM    | image/x-xbitmap          | X11 Bitmap                       |
| XPM    | image/x-xpixmap          | X11 Pixmap                       |
| SVG    | image/svg+xml            | Scalable Vector Graphics         |

#### Enabling in LightDM
Open `/etc/lightdm/lightdm.conf` file and under `Seat` configuration, find the line with `greeter-session` and update it like this:
```
greeter-session=lightdm-dynamic-greeter
```

#### Configuration
Configuration file is `/etc/lightdm/lightdm-dynamic-greeter.conf` and contains the necessary documentation.

### Shamelessly stolen bits
- Wallpaper resizing algoritms are taken from [https://github.com/l3ib/nitrogen](https://github.com/l3ib/nitrogen)
- How libqtlightdm works is taken from [https://github.com/surlykke/qt-lightdm-greeter](https://github.com/surlykke/qt-lightdm-greeter)

### Why does not it include any wallpapers?

There are considerable amount of artwork online that can be used for this project, but I am not comfortable to use them without permission from artists.
