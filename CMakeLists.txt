cmake_minimum_required(VERSION 3.5)

project(lightdm-dynamic-greeter VERSION 0.1 LANGUAGES CXX)

add_subdirectory(src)

install(TARGETS lightdm-dynamic-greeter RUNTIME DESTINATION bin)
install(FILES lightdm-dynamic-greeter.desktop DESTINATION /usr/share/xgreeters)
install(FILES lightdm-dynamic-greeter.conf DESTINATION /etc/lightdm/)
install(DIRECTORY wallpapers DESTINATION /usr/share/lightdm-dynamic-greeter/)
