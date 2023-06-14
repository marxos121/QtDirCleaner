#pragma once

#include "JobDialog.h"

template <typename T> class QList;
class QStandardItem;

class JobAddDialog  : public JobDialog
{
	Q_OBJECT

public:
	JobAddDialog(QWidget *parent);
	~JobAddDialog();

	const QList<QStandardItem*>& getList();

private:	
	QList<QStandardItem*> m_list;
	void createList();

private slots:
	virtual void onConfirmClicked() override;
};
