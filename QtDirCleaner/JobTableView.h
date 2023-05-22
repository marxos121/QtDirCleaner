#pragma once

#include "DirectoryCleanModel.h"

#include <QTableView>

class JobTableView  : public QTableView
{
	Q_OBJECT

public:
	JobTableView(QWidget *parent);
	~JobTableView();

	void addObject(const JobBase* obj);
	void removeObject(int row);
private:
	DirectoryCleanModel* m_model;
};
