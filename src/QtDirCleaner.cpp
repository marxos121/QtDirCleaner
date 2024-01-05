#include "../include/QtDirCleaner.h"

#include "../include/Columns.h"
#include "../include/JobEditDialog.h"
#include "../include/JobAddDialog.h"
#include "../include/JobBase.h"
#include "../include/JobBlueprint.h"
#include "../include/BlueprintUtilities.h"
#include "../include/LogWindow.h"
#include "../include/LogUtilities.h"

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

    m_model = new QStandardItemModel(this);
    m_table->setModel(m_model);    //should i use "this"?
    m_model->setHorizontalHeaderLabels({
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
        m_model->removeRow(curr.row());
    }

    m_executeAllButton->setDisabled(m_model->rowCount() == 0);
}

void QtDirCleaner::onExecuteSelectedClick()
{
    auto selection = m_table->selectionModel();
    auto curr = selection->currentIndex();
    if (curr.isValid())
    {
        auto blueprint = Utilities::blueprintFromModel(*m_model, curr.row());
        auto job = Utilities::createJob(blueprint);
        if (job) 
        {
            job->execute();
            LogWindow* lw = new LogWindow();
            lw->loadLog(job->getLog());
            lw->show();
        }
    }
}

void QtDirCleaner::onExecuteAllClick()
{
    QtLog totalLog;
    for (int i = 0; i < m_model->rowCount(); ++i)
    {
        auto blueprint = Utilities::blueprintFromModel(*m_model, i);
        auto job = Utilities::createJob(blueprint);
        if (job)
        {
            job->execute();
            Utilities::appendAsContent(totalLog, job->getLog());
        }
    }
    LogWindow* lw = new LogWindow();
    lw->loadLog(totalLog);
    lw->show();
}


void QtDirCleaner::onAddClick()
{
    JobAddDialog dialog(this);
    if (dialog.exec() == QDialog::Rejected)
    {
        return;
    }
    
    m_model->appendRow(dialog.getList());
    m_executeAllButton->setEnabled(true);
}

void QtDirCleaner::onEditClick()
{
    JobEditDialog dialog(this);
    dialog.openForEdit(m_model, m_table->selectionModel()->currentIndex().row());
    dialog.exec();
}

void QtDirCleaner::onCurrentChanged(const QModelIndex& current, const QModelIndex& previous)
{
    m_editButton->setEnabled(current.isValid());
    m_removeButton->setEnabled(current.isValid());
    m_executeSelectedButton->setEnabled(current.isValid());
}