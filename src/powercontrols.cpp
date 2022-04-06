#include <QHBoxLayout>
#include <QPushButton>
#include <QAction>

#include "powercontrols.h"

PowerControls::PowerControls(QWidget *parent)
    : QWidget{parent},
      m_PowerInterface(this),
      mainLayout{new QHBoxLayout(this)}
{
    addButton(m_PowerInterface.canSuspend(), QString("Suspend"), &QLightDM::PowerInterface::suspend);
    addButton(m_PowerInterface.canHibernate(), QString("Hibername"), &QLightDM::PowerInterface::hibernate);
    addButton(m_PowerInterface.canRestart(), QString("Restart"), &QLightDM::PowerInterface::restart);
    addButton(m_PowerInterface.canShutdown(), QString("Shutdown"), &QLightDM::PowerInterface::shutdown);

    setLayout(mainLayout);
}

void PowerControls::addButton(bool condition, const QString& title, bool (QLightDM::PowerInterface::*slot)())
{
    if (!condition)
        return;

    auto button = new QPushButton(title, this);
    connect(button, &QPushButton::clicked, &m_PowerInterface, slot);
    mainLayout->addWidget(button);
}
