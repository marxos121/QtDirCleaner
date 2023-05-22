#include "QtDirCleaner.h"
#include "DirectoryCleanModel.h"
#include <QTableView>
#include "JobTableView.h"

#include <QBoxLayout>
#include <QPushButton>

QtDirCleaner::QtDirCleaner(QWidget *parent)
    : QWidget(parent)
{;
    resize(1000, 700);
    auto mainLayout = new QHBoxLayout(this);

    //Table showing all jobs
    m_table = new JobTableView(this);
    m_cleaner.readInJobs("../jobs.jobs");
    for (auto job : m_cleaner.getQueuedJobs())
    {
        m_table->addObject(job);
    }
    mainLayout->addWidget(m_table);

    auto buttonsLayout = new QVBoxLayout(this);
    auto addButton = new QPushButton("Add", this);
    auto editButton = new QPushButton("Edit", this);
    auto removeButton = new QPushButton("Remove", this);
    auto executeButton = new QPushButton("Execute", this);
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(editButton);
    buttonsLayout->addWidget(removeButton);
    buttonsLayout->addSpacing(30);
    buttonsLayout->addWidget(executeButton);
    buttonsLayout->addStretch(1);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    connect(addButton, &QPushButton::clicked, this, &QtDirCleaner::onAddClick);
}

QtDirCleaner::~QtDirCleaner()
{}

void QtDirCleaner::onEditClick()
{
}

void QtDirCleaner::onRemoveClick()
{
}

void QtDirCleaner::onExecuteClick()
{
}


void QtDirCleaner::onAddClick()
{
}