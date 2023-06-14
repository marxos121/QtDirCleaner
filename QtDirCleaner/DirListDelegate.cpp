#include "DirListDelegate.h"
#include "DirLineEdit.h"

DirectoryListDelegate::DirectoryListDelegate(QObject *parent)
	: QStyledItemDelegate(parent), m_fileMode(QFileDialog::FileMode::Directory)
{ }

DirectoryListDelegate::~DirectoryListDelegate()
{ }

void DirectoryListDelegate::setFileMode(QFileDialog::FileMode mode)
{
	m_fileMode = mode;
}

QFileDialog::FileMode DirectoryListDelegate::getFileMode() const
{
	return m_fileMode;
}

QWidget* DirectoryListDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	auto editor = new DirLineEdit(m_fileMode, parent);
	return editor;
}

void DirectoryListDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	static_cast<DirLineEdit*>(editor)->setText(index.data().toString());
}

void DirectoryListDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	model->setData(index, static_cast<DirLineEdit*>(editor)->text());
}
