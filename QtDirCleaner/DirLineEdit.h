#pragma once

#include <QLineEdit>
#include <QFileDialog>

class DirLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	DirLineEdit(QFileDialog::FileMode mode = QFileDialog::FileMode::Directory, QWidget *parent = nullptr);
	~DirLineEdit();

	void setFileMode(QFileDialog::FileMode mode);
	QFileDialog::FileMode getFileMode() const;

	void setDialogTitle(const QString& l_dialogTitle);
	const QString& getDialogTitle() const;

private slots:
	void onButtonClicked();

private:
	QFileDialog::FileMode m_fileMode;
	QString m_dialogTitle;
};
