#include "JobAddDialog.h"
#include "DirLineEdit.h"
#include "DirListView.h"

#include <QStandardItem>
#include <qcombobox.h>
#include <qstringlistmodel.h>


JobAddDialog::JobAddDialog(QWidget *parent)
	: JobDialog(parent)
{
	setWindowTitle("Add");
}

JobAddDialog::~JobAddDialog()
{}

const QList<QStandardItem*>& JobAddDialog::getList()
{
	return m_list;
}

void JobAddDialog::createList()
{
	QString temp = m_type->currentText();
	m_list.append(new QStandardItem(temp));
	temp.clear();

	for (const auto& ext : m_extensions->text().split(' '))
	{
		temp += ext + "; ";
	}
	temp.chop(2);
	m_list.append(new QStandardItem(temp));
	temp.clear();

	for (int i = 0; i < m_targetDirs->model()->rowCount(); ++i)
	{
		temp += m_targetDirs->model()->data(m_targetDirs->model()->index(i, 0)).toString() + "; ";
	}
	temp.chop(2);
	m_list.append(new QStandardItem(temp));
	temp.clear();


	for (int i = 0; i < m_exemptFiles->model()->rowCount(); ++i)
	{
		temp += m_exemptFiles->model()->data(m_exemptFiles->model()->index(i, 0)).toString() + "; ";
	}
	temp.chop(2);
	m_list.append(new QStandardItem(temp));

	if (m_type->currentText() == "Move")
	{
		m_list.append(new QStandardItem(m_destination->text()));
	}
}

void JobAddDialog::onConfirmClicked()
{
	if (m_extensions->text().isEmpty()
		|| m_targetDirs->model()->rowCount() == 0
		|| (m_type->currentText() == "Move" && m_destination->text().isEmpty()))
	{
		return;
	}

	createList();
	QDialog::accept();
}
