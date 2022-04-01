#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLightDM/Greeter>

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(size_t screen, QWidget *parent = nullptr);
	[[nodiscard]] bool isPrimaryScreen() const;

public slots:
	void setBackground(const QImage *);

private:
	size_t m_Screen;
};
#endif // MAINWINDOW_H
