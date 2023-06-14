#pragma once

#include "../JobBlueprint.h"

#include <QDialog>
#include <QIcon>

//class PlusMinusList;
class QLineEdit;
class QComboBox;
class DirLineEdit;
class DirListView;
class QVBoxLayout;

class JobDialog : public QDialog
{
	Q_OBJECT

public:
	JobDialog(QWidget * parent = nullptr);
	~JobDialog();

private slots:
	void toggleDestinationEnabled(const QString& str);
	virtual void onConfirmClicked() = 0;

	void onSelectionChanged(QPushButton* buttonMinus, const QModelIndex& current, const QModelIndex& previous);
	void onPlusClicked(DirListView*& view);
	void onMinusClicked(DirListView*& view);

protected:
	void mousePressEvent(QMouseEvent* event) override;

	QComboBox* m_type;
	QLineEdit* m_extensions;
	DirLineEdit* m_destination;
	DirListView* m_targetDirs;
	DirListView* m_exemptFiles;

private:
	QIcon m_plusIcon;
	QIcon m_minusIcon;
	QVBoxLayout* createDirList(const QString& label, DirListView*& view);
};
