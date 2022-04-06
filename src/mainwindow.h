#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QScreen>
#include <QLightDM/Greeter>
#include <QColor>

#include "settings.h"
#include "authform.h"
#include "powercontrols.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(const QScreen *screen, QWidget *parent = nullptr);
    ~MainWindow() override;
    void drawPrimaryScreenElements();
    void undrawPrimaryScreenElements();

public slots:
    void setBackground(const QImage *,const Settings::ResizeMode, const QColor& bgColor);

private:
    void drawAuthForm();
    void undrawAuthForm();

    void drawPowerControls();
    void undrawPowerControls();

    const QScreen* m_Screen;
    AuthForm* m_AuthForm;
    PowerControls* m_PowerControls;
};
#endif // MAINWINDOW_H
