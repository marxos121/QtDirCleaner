#include "../include/DirLineEdit.h"
#include <qtoolbutton.h>
#include <qboxlayout.h>
#include <qapplication.h>
#include <qstyle.h>
#include <qfiledialog.h>

DirLineEdit::DirLineEdit(QFileDialog::FileMode mode, QWidget *parent)
	: QLineEdit(parent), m_fileMode(mode)
{
	setReadOnly(true);
	QString style = "QToolButton { border: none; } QToolButton:hover { border-left: solid black 1px; background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #3399FF, stop:1 white); } ";
	auto button = new QToolButton(this);
	button->setStyleSheet(style);
	button->setFixedSize(18, 18);
	button->setIcon(QApplication::style()->standardIcon(QStyle::SP_DirOpenIcon));
	button->setCursor(Qt::ArrowCursor);
	button->setObjectName("button");
	auto lo = new QHBoxLayout(this);
	lo->addStretch(1);
	lo->addWidget(button);
	lo->setContentsMargins(0, 0, 2, 0);

	connect(button, &QToolButton::clicked, this, &DirLineEdit::onButtonClicked);
}

DirLineEdit::~DirLineEdit()
{}

void DirLineEdit::setFileMode(QFileDialog::FileMode mode)
{
	m_fileMode = mode;
}

QFileDialog::FileMode DirLineEdit::getFileMode() const
{
	return m_fileMode;
}

void DirLineEdit::setDialogTitle(const QString& l_dialogTitle)
{
	m_dialogTitle = l_dialogTitle;
}

const QString& DirLineEdit::getDialogTitle() const
{
	return m_dialogTitle;
}

void DirLineEdit::onButtonClicked()
{
	QFileDialog dlg(this);
	dlg.setDirectory(QDir::rootPath());
	if (!text().isEmpty())
	{
		QDir dir(text());
		if (dir.exists())
		{
			if (QFileInfo(text()).isFile())
			{
				dir.cdUp();
			}
			dlg.setDirectory(dir.absolutePath());
		}
	}

	dlg.setObjectName("dialog"); 
	dlg.setFileMode(m_fileMode);
	if (!m_dialogTitle.isEmpty())
	{
		dlg.setWindowTitle(m_dialogTitle);;
	}

	if (!dlg.exec()) {
		return;
	}

	QString directory = dlg.selectedFiles()[0];
	setText(directory);
	setCursor(Qt::IBeamCursor);
}
