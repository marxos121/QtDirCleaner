#include "Columns.h"

#include "JobEditDialog.h"
#include "DirLineEdit.h"
#include "DirListView.h"

#include <qstandarditemmodel.h>
#include <qcombobox.h>
#include <qstringlistmodel.h>

JobEditDialog::JobEditDialog(QWidget* parent)
	: JobDialog(parent),
	m_editFlags(0), m_model(nullptr), m_row(-1)
{
	setWindowTitle("Edit");
}

JobEditDialog::~JobEditDialog()
{}

void JobEditDialog::openForEdit(QStandardItemModel* model, int row)
{
	if (!model || !model->index(row, CleanModelColumns::Type).isValid()) {
		return;
	}

	m_model = model;
	m_row = row;


	if (m_model->data(m_model->index(row, CleanModelColumns::Type)).toString() == "Move")
	{
		m_type->setCurrentIndex(0);
		m_destination->setEnabled(true);
		m_destination->setText(m_model->data(m_model->index(row, CleanModelColumns::Destination)).toString());
	}
	else
	{
		m_type->setCurrentIndex(1);
		m_destination->setEnabled(false);
	}

	QString temp;
	for (const auto& ext : m_model->data(m_model->index(row, CleanModelColumns::Extensions)).toString().split(';'))
	{
		temp += ext;
	}
	m_extensions->setText(temp);

	static_cast<QStringListModel*>(m_targetDirs->model())->
		setStringList(m_model->data(m_model->index(row, CleanModelColumns::TargetDirs))
			.toString().split("; "));

	static_cast<QStringListModel*>(m_exemptFiles->model())->
		setStringList(m_model->data(m_model->index(row, CleanModelColumns::Exempt)).
			toString().split("; "));

	connect(m_type, &QComboBox::currentIndexChanged, this, [this]() { onDataChanged(CleanModelColumns::Type); });
	connect(m_extensions, &QLineEdit::textChanged, this, [this]() { onDataChanged(CleanModelColumns::Extensions); });
	connect(m_targetDirs->model(), &QAbstractItemModel::dataChanged, this, [this]() { onDataChanged(CleanModelColumns::TargetDirs); });
	connect(m_targetDirs->model(), &QAbstractItemModel::rowsInserted, this, [this]() { onDataChanged(CleanModelColumns::TargetDirs); });
	connect(m_targetDirs->model(), &QAbstractItemModel::rowsRemoved, this, [this]() { onDataChanged(CleanModelColumns::TargetDirs); });
	connect(m_exemptFiles->model(), &QAbstractItemModel::dataChanged, this, [this]() { onDataChanged(CleanModelColumns::Exempt); });
	connect(m_exemptFiles->model(), &QAbstractItemModel::rowsInserted, this, [this]() { onDataChanged(CleanModelColumns::Exempt); });
	connect(m_exemptFiles->model(), &QAbstractItemModel::rowsRemoved, this, [this]() { onDataChanged(CleanModelColumns::Exempt); });
	connect(m_destination, &QLineEdit::textChanged, this, [this]() { onDataChanged(CleanModelColumns::Destination); });
}

void JobEditDialog::onDataChanged(CleanModelColumns flag)
{
	m_editFlags |= 1 << flag;
}


void JobEditDialog::onConfirmClicked()
{
	if (!m_model || m_row == -1)
	{
		return;
	}

	if (m_editFlags & 1)
	{
		m_model->setData(m_model->index(m_row, CleanModelColumns::Type),
			m_type->currentData().toString());
	}

	if (m_editFlags & 1 << CleanModelColumns::Destination)
	{
		auto data = m_type->currentText();
		QString text = m_type->currentText() == "Move" ? m_destination->text() : "";

		m_model->setData(m_model->index(m_row, CleanModelColumns::Destination),
			text);
	}

	auto makeString = [](const QStringListModel& model) -> QString {
		QString ret;
		for (int i = 0; i < model.rowCount(); ++i)
		{
			ret += model.index(i).data().toString() + "; ";
		}
		ret.chop(2);
		return ret;
	};

	if (m_editFlags & 1 << CleanModelColumns::Extensions)
	{
		m_model->setData(m_model->index(m_row, CleanModelColumns::Extensions),
			m_extensions->text());
	}

	if (m_editFlags & 1 << CleanModelColumns::TargetDirs)
	{
		m_model->setData(m_model->index(m_row, CleanModelColumns::TargetDirs),
			makeString(static_cast<QStringListModel>(m_targetDirs->model())));
	}

	if (m_editFlags & 1 << CleanModelColumns::Exempt)
	{
		m_model->setData(m_model->index(m_row, CleanModelColumns::Exempt),
			makeString(static_cast<QStringListModel>(m_targetDirs->model())));
	}
	
	QDialog::accept();
}