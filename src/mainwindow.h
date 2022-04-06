#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QScreen>
#include <QLightDM/Greeter>
#include <QColor>

#include "settings.h"
#include "authform.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(const QScreen *screen, QWidget *parent = nullptr);
    ~MainWindow() override;
    void drawAuthForm();
    void undrawAuthForm();

public slots:
    void setBackground(const QImage *,const Settings::ResizeMode, const QColor& bgColor);

private:
    const QScreen* m_Screen;
    AuthForm* m_AuthForm;
};
#endif // MAINWINDOW_H
