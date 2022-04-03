#include <QLightDM/UsersModel>
#include <QLineEdit>
#include <QCompleter>
#include <QKeyEvent>
#include <QPainter>
#include <QGraphicsOpacityEffect>

#include "authform.h"
#include "ui_authform.h"
#include "clickablelabel.h"

AuthForm::AuthForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthForm),
    m_Greeter(this),
    m_PowerInterface(this),
    m_SessionsModel(this),
    m_Cache(this)
{
    if (!m_Greeter.connectSync())
    {
        close();
    }

    ui->setupUi(this);

    ui->usernameEdit->setPlaceholderText("Username");
    ui->passwordEdit->setPlaceholderText("Password");

    ui->usernameEdit->hide();
    ui->passwordEdit->setEchoMode(QLineEdit::Password);

    connect(ui->usernameLabel, &ClickableLabel::clicked, this, &AuthForm::switchToUsernameEdit);
    connect(ui->usernameEdit, &QLineEdit::textEdited, ui->usernameLabel, &ClickableLabel::setText);
    connect(ui->usernameEdit, &QLineEdit::editingFinished, this, &AuthForm::updateUser);
    connect(&m_Greeter, &QLightDM::Greeter::showPrompt, this, &AuthForm::onPrompt);
    connect(&m_Greeter, &QLightDM::Greeter::authenticationComplete, this, &AuthForm::authenticationAnswerReady);

    setAutoFillBackground(false);

    auto effect = new QGraphicsOpacityEffect(this);
    effect->setOpacity(0.8);
    setGraphicsEffect(effect);

    QString user;
    QStringList users;

    if (!m_Greeter.hideUsersHint())
    {
        QLightDM::UsersModel usersModel;
        for(int i = 0; i < usersModel.rowCount(QModelIndex()); ++i)
        {
            users << usersModel.data(usersModel.index(i, 0), QLightDM::UsersModel::NameRole).toString();
        }

        ui->usernameEdit->setCompleter(new QCompleter(users));
        ui->usernameEdit->completer()->setCompletionMode(QCompleter::InlineCompletion);
    }

    user = m_Cache.getLastUser(m_Greeter.selectUserHint());

    // If there's only 1 user and user hints are enabled
    // Just use it as user
    if (users.count() == 1 && user.isEmpty())
    {
        user = users.first();
    }

    ui->usernameEdit->setText(user);
    ui->usernameLabel->setText(user);

    if (user.isEmpty())
    {
        switchToUsernameEdit();
    }

    updateUser();
}

void AuthForm::switchToUsernameEdit() const
{
    ui->usernameLabel->hide();
    ui->usernameEdit->show();
}

void AuthForm::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        authenticate();
        return;
    }

    QWidget::keyPressEvent(event);
}

void AuthForm::updateUser()
{
    if (m_Greeter.inAuthentication())
    {
        m_Greeter.cancelAuthentication();
    }
    if (ui->usernameLabel->text().isEmpty() == false)
    {
        ui->usernameLabel->show();
        ui->usernameEdit->hide();

        m_Greeter.authenticate(ui->usernameLabel->text());
        ui->passwordEdit->setFocus();
    }
}

void AuthForm::authenticationAnswerReady()
{
    if (m_Greeter.isAuthenticated())
    {
        m_Cache.setLastUser(ui->usernameLabel->text());
        m_Greeter.startSessionSync();
    }
    else
    {
        ui->passwordEdit->clear();
        ui->passwordEdit->setFocus();
    }
}

void AuthForm::authenticate()
{
    m_Greeter.respond(ui->passwordEdit->text().trimmed());
}

void AuthForm::onPrompt(const QString prompt, const QLightDM::Greeter::PromptType promptType)
{
    ui->passwordEdit->clear();
    ui->passwordEdit->setFocus();
}

void AuthForm::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(Qt::black));
    painter.setPen(Qt::transparent);

    QRect rect = this->rect();
    rect.setWidth(rect.width()-1);
    rect.setHeight(rect.height()-1);
    painter.drawRoundedRect(rect, 15, 15);

    QWidget::paintEvent(event);
}

AuthForm::~AuthForm()
{
    delete ui;
}
