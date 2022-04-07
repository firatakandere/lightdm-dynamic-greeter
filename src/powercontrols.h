#ifndef POWERCONTROLS_H
#define POWERCONTROLS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLightDM/Power>

class PowerControls : public QWidget
{
    Q_OBJECT
public:
    explicit PowerControls(QWidget *parent = nullptr);
private:
    QLightDM::PowerInterface m_PowerInterface;
    void addButton(bool condition, const QString& title, bool (QLightDM::PowerInterface::*)());
    QVBoxLayout* mainLayout;
};

#endif // POWERCONTROLS_H
