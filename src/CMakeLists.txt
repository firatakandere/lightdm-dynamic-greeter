set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include(FindPkgConfig)
pkg_check_modules(LIGHTDM_QT liblightdm-qt5-3)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${LIGHTDM_QT_INCLUDE_DIRS})

set(PROJECT_SOURCES
        main.cpp
	mainwindow.cpp
	mainwindow.h
	settings.cpp
	settings.h
	authform.cpp
	authform.h
	authform.ui
	clickablelabel.cpp
	clickablelabel.h
	backgroundmanager.cpp
	backgroundmanager.h
	wallpaperresize.h
)

add_executable(lightdm-dynamic-greeter ${PROJECT_SOURCES})

target_link_libraries(lightdm-dynamic-greeter PRIVATE lightdm-qt5-3 Qt${QT_VERSION_MAJOR}::Widgets)
