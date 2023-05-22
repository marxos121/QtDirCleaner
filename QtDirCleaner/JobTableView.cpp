#include "JobTableView.h"

#include <QHeaderView>

JobTableView::JobTableView(QWidget *parent)
	: QTableView(parent), m_model(nullptr)
{
	m_model = new DirectoryCleanModel;
	setModel(m_model);

	auto hd = horizontalHeader();
	hd->setSectionResizeMode(QHeaderView::Stretch);
	hd->setSectionResizeMode(0, QHeaderView::ResizeToContents); 
	hd->setSectionResizeMode(1, QHeaderView::Fixed);
	hd->resizeSection(1, 150); 


	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setSelectionBehavior(QAbstractItemView::SelectRows);
}

JobTableView::~JobTableView()
{
	delete m_model;
}

void JobTableView::addObject(const JobBase * obj)
{
	m_model->addObject(obj);
}

void JobTableView::removeObject(int row)
{
	m_model->removeObject(row);
}
