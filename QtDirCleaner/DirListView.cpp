#include "DirListView.h"
#include <qfiledialog.h>

DirListView::DirListView(QWidget *parent)
	: QListView(parent)
{
}

DirListView::~DirListView()
{}


void DirListView::closeEditor(QWidget* editor, QAbstractItemDelegate::EndEditHint hint)
{
	//Close the LineEdit only if its child file dialog is not active
	if (!editor->findChild<QFileDialog*>("dialog"))
	{
		QListView::closeEditor(editor, hint);
	}
}