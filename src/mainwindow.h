#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QScreen>
#include <QLightDM/Greeter>
#include <QColor>

#include "settings.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QScreen *screen, QWidget *parent = nullptr);
    void show(bool isPrimaryScreen);

public slots:
    void setBackground(const QImage *,const Settings::ResizeMode, const QColor& bgColor);

private:
    QScreen* m_Screen;
};
#endif // MAINWINDOW_H
