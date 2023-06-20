#include "../include/JobDialog.h"
#include "../include/DirLineEdit.h"
#include "../include/DirListDelegate.h"
#include "../include/DirListView.h"

#include <qtoolbutton.h>
#include <qlistview.h>
#include <qcombobox.h>
#include <QMouseEvent>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qitemselectionmodel.h>
#include <qstringlistmodel.h>

JobDialog::JobDialog(QWidget *parent)
	: QDialog(parent), 
	m_type(new QComboBox(this)),
	m_extensions(new QLineEdit(this)), 
	m_destination(new DirLineEdit(QFileDialog::FileMode::Directory, this)),
	m_targetDirs(new DirListView(this)),
	m_exemptFiles(new DirListView(this)),
	m_plusIcon("assets/plus.png"),
	m_minusIcon("assets/minus.png")

{
	setMinimumWidth(700);
	m_targetDirs->setObjectName("targets");
	m_exemptFiles->setObjectName("exempts");

	m_type->addItems({ "Move", "Remove" });
	m_type->setToolTip("Move - transfer matching files from target directories to selected destination.\n"
		"Remove - remove matching files from target directories.");
	m_extensions->setToolTip("Space-separated target extensions. Use '.*' to target all filetypes.");
	m_destination->setDialogTitle("Select destination folder");
	m_destination->setToolTip("Directory to move matching files to when selected job type is 'Move'");

	auto targetsLeft = createDirList("Target directories: ", m_targetDirs);
	auto exemptLeft = createDirList("Exempt files: ", m_exemptFiles);
	static_cast<DirectoryListDelegate*>
		(m_exemptFiles->itemDelegate())->setFileMode(QFileDialog::FileMode::AnyFile);

	auto cancelBtn = new QPushButton("Cancel", this);
	cancelBtn->setFixedSize(70, 20);
	auto confirmBtn = new QPushButton("Confirm", this);
	confirmBtn->setFixedSize(70, 20);
	auto controlsLayout = new QHBoxLayout();
	controlsLayout->addStretch(1);
	controlsLayout->addWidget(cancelBtn);
	controlsLayout->addWidget(confirmBtn);

	auto typeLayout = new QHBoxLayout();
	typeLayout->addWidget(m_type);
	typeLayout->addStretch(1);

	auto layout = new QGridLayout(this);
	layout->setColumnStretch(1, 1);
	layout->addWidget(new QLabel("Type: "), 0, 0);
	layout->addLayout(typeLayout, 0, 1);
	layout->addWidget(new QLabel("Extensions: "), 1, 0);
	layout->addWidget(m_extensions, 1, 1);
	layout->addWidget(new QLabel("Destination directory: "), 2, 0);
	layout->addWidget(m_destination, 2, 1);
	layout->addLayout(targetsLeft, 3, 0);
	layout->addWidget(m_targetDirs, 3, 1);
	layout->addLayout(exemptLeft, 6, 0);
	layout->addWidget(m_exemptFiles, 6, 1);
	layout->addLayout(controlsLayout, 9, 1);
	layout->setSpacing(8);
	layout->setContentsMargins(8, 8, 8, 8);

	connect(confirmBtn, &QPushButton::clicked, this, &JobDialog::onConfirmClicked);
	connect(cancelBtn, &QPushButton::clicked, this, &QWidget::close);
	connect(m_type, &QComboBox::currentTextChanged, this, &JobDialog::toggleDestinationEnabled);
}

JobDialog::~JobDialog()
{
}

void JobDialog::toggleDestinationEnabled(const QString& str)
{
	m_destination->setEnabled(str == "Move");
}

void JobDialog::mousePressEvent(QMouseEvent* event)
{
	if (!m_targetDirs->geometry().contains(event->pos()))
	{  
		m_targetDirs->selectionModel()->
			setCurrentIndex(QModelIndex(), QItemSelectionModel::ClearAndSelect);
	}
	if (!m_exemptFiles->geometry().contains(event->pos()))
	{
		m_exemptFiles->selectionModel()->
			setCurrentIndex(QModelIndex(), QItemSelectionModel::ClearAndSelect);
	}

	QWidget::mousePressEvent(event);
}


// ==================================
// ===== List-related functions =====
// ==================================

QVBoxLayout* JobDialog::createDirList(const QString& label, DirListView*& view)
{
	//Prepare QListView
	view->setModel(new QStringListModel(this));
	view->setItemDelegate(new DirectoryListDelegate(this));
	view->setSelectionModel(new QItemSelectionModel(view->model()));

	//Prepare buttons + and -
	auto buttonPlus = new QPushButton(this);
	buttonPlus->setIcon(m_plusIcon);
	buttonPlus->setFixedSize(18, 18);
	buttonPlus->setObjectName("plus");
	auto buttonMinus = new QPushButton(this);
	buttonMinus->setIcon(m_minusIcon);
	buttonMinus->setFixedSize(18, 18);
	buttonMinus->setObjectName("minus");
	buttonMinus->setDisabled(true);

	connect(view->selectionModel(), &QItemSelectionModel::currentChanged, this,
		[this, buttonMinus](const QModelIndex& current, const QModelIndex& previous) 
		{
			onSelectionChanged(buttonMinus, current, previous);
		});

	connect(buttonPlus, &QPushButton::clicked, this, [this, &view]() { onPlusClicked(view); });
	connect(buttonMinus, &QPushButton::clicked, this, [this, &view]() { onMinusClicked(view); });

	//Create buttons' layout, then the layout of the whole left-hand side;
	//Leave out QListView to align it with the rest of the interface using grid
	auto loButtons = new QHBoxLayout();
	loButtons->addStretch(1);
	loButtons->addWidget(buttonPlus);
	loButtons->addWidget(buttonMinus);
	loButtons->addStretch(1);
	auto retLayout = new QVBoxLayout();
	retLayout->addStretch(1);
	retLayout->addWidget(new QLabel(label, this));
	retLayout->addLayout(loButtons);
	retLayout->addStretch(1);
	return retLayout;
}


void JobDialog::onSelectionChanged(QPushButton* buttonMinus, const QModelIndex& current, const QModelIndex& previous)
{
	buttonMinus->setDisabled(!current.isValid());
}

void JobDialog::onPlusClicked(DirListView*& view)
{
	QFileDialog dialog(this);
	dialog.setDirectory(QDir::rootPath());
	auto filemode = view->objectName() == "targets" ?
		QFileDialog::FileMode::Directory : QFileDialog::FileMode::ExistingFiles;
	dialog.setFileMode(filemode);
	if (!dialog.exec())
	{
		return;
	}

	auto model = static_cast<QStringListModel*>(view->model());
	model->setStringList(model->stringList() + dialog.selectedFiles());
}

void JobDialog::onMinusClicked(DirListView*& view)
{
	auto selectionModel = view->selectionModel();
	auto row = selectionModel->currentIndex().row();
	view->model()->removeRow(row);
}
