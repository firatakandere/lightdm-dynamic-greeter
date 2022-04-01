#ifndef AUTHFORM_H
#define AUTHFORM_H

#include <QWidget>

#include <QLightDM/Greeter>
#include <QLightDM/Power>
#include <QLightDM/SessionsModel>

namespace Ui {
class AuthForm;
}

class AuthForm : public QWidget
{
	Q_OBJECT

public:
	explicit AuthForm(QWidget *parent = nullptr);
	~AuthForm() override;

protected:
	void keyPressEvent(QKeyEvent *event) override;

private slots:
	void switchToUsernameEdit() const;
	void updateUser();
	void authenticationAnswerReady();
	void onPrompt(const QString prompt, const QLightDM::Greeter::PromptType promptType);


private:
	void authenticate();
	QString currentSession() const;

	Ui::AuthForm *ui;
	QLightDM::Greeter m_Greeter;
	QLightDM::PowerInterface m_PowerInterface;
	QLightDM::SessionsModel m_SessionsModel;
};

#endif // AUTHFORM_H
