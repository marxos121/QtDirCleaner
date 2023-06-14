#pragma once

#include <QStyledItemDelegate>
#include <QFileDialog>

class DirectoryListDelegate  : public QStyledItemDelegate
{
	Q_OBJECT

public:
	DirectoryListDelegate(QObject *parent);
	~DirectoryListDelegate();

	void setFileMode(QFileDialog::FileMode mode);
	QFileDialog::FileMode getFileMode() const;

	QWidget* createEditor(QWidget* parent, 
		const QStyleOptionViewItem& option, 
		const QModelIndex& index) const override;
	void setEditorData(QWidget* editor, const QModelIndex& index) const override;
	void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;


private:
	QFileDialog::FileMode m_fileMode;
};
