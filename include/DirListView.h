#pragma once

#include <QListView>

class DirListView : public QListView
{
	Q_OBJECT

public:
	DirListView(QWidget *parent = nullptr);
	~DirListView();

protected slots:
	void closeEditor(QWidget* editor, QAbstractItemDelegate::EndEditHint hint) override;
};
