#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtDirCleaner.h"

#include "../DirCleaner.h"

class JobTableView;

class QtDirCleaner : public QWidget
{
    Q_OBJECT

public:
    QtDirCleaner(QWidget *parent = nullptr);
    ~QtDirCleaner();

private:
    DirCleaner m_cleaner; 
    JobTableView* m_table;

private slots:
    void onAddClick();
    void onEditClick();
    void onRemoveClick();
    void onExecuteClick();

};
