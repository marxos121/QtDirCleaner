#include "../include/LogWindow.h"
#include "../include/QtLog.h"
#include "../include/LogUtilities.h"

#include <qfile.h>
#include <qfiledialog.h>
#include <qboxlayout.h>
#include <qstyle.h>
#include <qapplication.h>
#include <qpushbutton.h>
#include <qplaintextedit.h>

LogWindow::LogWindow(QWidget *parent)
	: QWidget(parent)
{
	QPushButton* saveButton = new QPushButton(this);
	saveButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton));
	saveButton->setMinimumSize({ 50, 50 });
	QPushButton* closeButton = new QPushButton(this);
	closeButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_DockWidgetCloseButton));
	closeButton->setMinimumSize({ 50, 50 });

	m_logView = new QPlainTextEdit(this);
	m_logView->setReadOnly(true);

	QHBoxLayout* buttons = new QHBoxLayout();
	buttons->addWidget(saveButton);
	buttons->addWidget(closeButton);
	buttons->addStretch(1);

	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->addLayout(buttons);
	mainLayout->addWidget(m_logView);

	setLayout(mainLayout);


	connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
	connect(saveButton, &QPushButton::clicked, this, &LogWindow::onSaveClicked);
}

LogWindow::~LogWindow()
{}

void LogWindow::loadLog(const QtLog& l_log)
{
	m_logView->setPlainText(Utilities::getFullLog(l_log));
}

void LogWindow::onSaveClicked() const
{
	auto filename = QFileDialog::getSaveFileName();
	QFile file(filename);
	if (file.open(QIODeviceBase::WriteOnly))
	{
		file.write(m_logView->toPlainText().toLocal8Bit());
	}
}