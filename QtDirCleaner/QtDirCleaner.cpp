#include "Columns.h"
#include "QtDirCleaner.h"
#include "JobEditDialog.h"
#include "JobAddDialog.h"
#include "../JobBase.h"

#include <qheaderview.h>
#include <QBoxLayout>
#include <QPushButton>
#include <qtableview.h>
#include <qstandarditemmodel.h>

QtDirCleaner::QtDirCleaner(QWidget *parent)
    : QWidget(parent), m_table(new QTableView(this))
{
    setWindowIcon(QIcon("./assets/icon.ico"));
    setWindowTitle("DirCleaner");
    resize(1000, 700);

    auto model = new QStandardItemModel(this);
    m_table->setModel(model);    //should i use "this"?
    model->setHorizontalHeaderLabels({
        columnHeaders(CleanModelColumns::Type),
        columnHeaders(CleanModelColumns::Extensions),
        columnHeaders(CleanModelColumns::TargetDirs),
        columnHeaders(CleanModelColumns::Exempt),
        columnHeaders(CleanModelColumns::Destination) 
    });
    auto hd = m_table->horizontalHeader();
    hd->setSectionResizeMode(QHeaderView::Stretch);
    hd->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    hd->setSectionResizeMode(1, QHeaderView::Fixed);
    hd->resizeSection(1, 100);

    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);


    auto mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_table);
    auto buttonsLayout = new QVBoxLayout();
    auto addButton = new QPushButton("Add", this);
    m_editButton = new QPushButton("Edit", this);
    m_editButton->setEnabled(false);
    m_removeButton = new QPushButton("Remove", this);
    m_removeButton->setEnabled(false);
    m_executeSelectedButton = new QPushButton("Execute\nselected", this);
    m_executeSelectedButton->setEnabled(false);
    m_executeAllButton = new QPushButton("Execute all", this);
    m_executeAllButton->setEnabled(false);
    auto lineA = new QFrame(this);
    lineA->setFrameShape(QFrame::HLine);
    lineA->setFrameShadow(QFrame::Sunken);
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(m_editButton);
    buttonsLayout->addWidget(m_removeButton);
    buttonsLayout->addSpacing(5);
    buttonsLayout->addWidget(lineA);
    buttonsLayout->addSpacing(5);
    buttonsLayout->addWidget(m_executeSelectedButton);
    buttonsLayout->addWidget(m_executeAllButton);
    buttonsLayout->addStretch(1);
    mainLayout->addLayout(buttonsLayout);

    connect(m_table->selectionModel(), &QItemSelectionModel::currentChanged, this, &QtDirCleaner::onCurrentChanged);
    connect(addButton, &QPushButton::clicked, this, &QtDirCleaner::onAddClick);
    connect(m_editButton, &QPushButton::clicked, this, &QtDirCleaner::onEditClick);
    connect(m_removeButton, &QPushButton::clicked, this, &QtDirCleaner::onRemoveClick);
    connect(m_executeSelectedButton, &QPushButton::clicked, this, &QtDirCleaner::onExecuteSelectedClick);
    connect(m_executeAllButton, &QPushButton::clicked, this, &QtDirCleaner::onExecuteAllClick);
}

QtDirCleaner::~QtDirCleaner()
{
}

void QtDirCleaner::onRemoveClick()
{
    auto selection = m_table->selectionModel();
    auto curr = selection->currentIndex();
    if (curr.isValid())
    {
        m_table->model()->removeRow(curr.row());
    }

    m_executeAllButton->setDisabled(m_table->model()->rowCount() == 0);
}

void QtDirCleaner::onExecuteSelectedClick()
{
    auto selection = m_table->selectionModel();
    auto curr = selection->currentIndex();
    auto model = static_cast<QStandardItemModel*>(m_table->model());
    if (curr.isValid())
    {
        auto blueprint = blueprintFromModel(*model, curr.row());
        auto job = createJob(blueprint);
        if (job) 
        {
            job->execute();
        }
    }
}

void QtDirCleaner::onExecuteAllClick()
{
    auto model = static_cast<QStandardItemModel*>(m_table->model());
    for (int i = 0; i < model->rowCount(); ++i)
    {
        auto blueprint = blueprintFromModel(*model, i);
        auto job = createJob(blueprint);
        if (job)
        {
            job->execute();
        }
    }
}


void QtDirCleaner::onAddClick()
{
    JobAddDialog dialog(this);
    if (dialog.exec() == QDialog::Rejected)
    {
        return;
    }

    static_cast<QStandardItemModel*>(m_table->model())->appendRow(dialog.getList());
    m_executeAllButton->setEnabled(true);
}

void QtDirCleaner::onEditClick()
{
    JobEditDialog dialog(this);
    dialog.openForEdit(static_cast<QStandardItemModel*>(m_table->model()),
        m_table->selectionModel()->currentIndex().row());
    dialog.exec();
}

void QtDirCleaner::onCurrentChanged(const QModelIndex& current, const QModelIndex& previous)
{
    m_editButton->setEnabled(current.isValid());
    m_removeButton->setEnabled(current.isValid());
    m_executeSelectedButton->setEnabled(current.isValid());
}