#ifndef POWERCONTROLS_H
#define POWERCONTROLS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLightDM/Power>

class PowerControls : public QWidget
{
    Q_OBJECT
public:
    explicit PowerControls(QWidget *parent = nullptr);

private:
    QLightDM::PowerInterface m_PowerInterface;
    void addButton(bool condition, const QString& title, bool (QLightDM::PowerInterface::*)());

    QHBoxLayout* mainLayout;
signals:

};

#endif // POWERCONTROLS_H
