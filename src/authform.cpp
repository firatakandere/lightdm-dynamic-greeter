#include <QLightDM/UsersModel>
#include <QLineEdit>
#include <QCompleter>
#include <QKeyEvent>

#include "authform.h"
#include "ui_authform.h"
#include "clickablelabel.h"

AuthForm::AuthForm(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::AuthForm),
	m_Greeter(this),
	m_PowerInterface(this),
	m_SessionsModel(this)
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

	setAutoFillBackground(true);
	QPalette palette;
	QColor color = Qt::black;
	color.setAlpha(225);
	palette.setColor(QPalette::Window, color);
	setPalette(palette);

	if (m_Greeter.hideUsersHint() != true)
	{
		QStringList users;
		QLightDM::UsersModel usersModel;
		for(int i = 0; i < usersModel.rowCount(QModelIndex()); ++i)
		{
			users << usersModel.data(usersModel.index(i, 0), QLightDM::UsersModel::NameRole).toString();
		}
		ui->usernameEdit->setCompleter(new QCompleter(users));
		ui->usernameEdit->completer()->setCompletionMode(QCompleter::InlineCompletion);
	}

	// @todo remember user

	QString user = m_Greeter.selectUserHint();
	ui->usernameEdit->setText(user);
	ui->usernameLabel->setText(user);

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
		// @todo update settings
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

void AuthForm::onPrompt(const QString prompt, const QLightDM::Greeter::PromptType prompType)
{
	ui->passwordEdit->clear();
	ui->passwordEdit->setFocus();
}

AuthForm::~AuthForm()
{
	delete ui;
}
