#pragma once

#include <QWidget>

class QtLog;
class QPlainTextEdit;

class LogWindow : public QWidget
{
	Q_OBJECT

public:
	LogWindow(QWidget *parent = nullptr);
	~LogWindow();

	void loadLog(const QtLog& log);

private slots:
	void onSaveClicked() const;

private:
	QPlainTextEdit* m_logView;
};
