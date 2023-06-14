#pragma once

#include "JobDialog.h"

enum CleanModelColumns;
class QStandardItemModel;
class QStandardItem;

class JobEditDialog  : public JobDialog
{
	Q_OBJECT;

public:
	JobEditDialog(QWidget *parent);
	~JobEditDialog();
	void openForEdit(QStandardItemModel* l_model, int l_row);
	
private slots:
	virtual void onConfirmClicked() override;

private:
	std::uint8_t m_editFlags;

	QStandardItemModel* m_model;
	int m_row;

	void onDataChanged(CleanModelColumns flags);
};


