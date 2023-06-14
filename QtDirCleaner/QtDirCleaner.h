#pragma once

#include <QtWidgets/QWidget>

class QTableView;
class QPushButton;

class QtDirCleaner : public QWidget
{
    Q_OBJECT

public:
    QtDirCleaner(QWidget *parent = nullptr);
    ~QtDirCleaner();

private:
    QTableView* m_table;
    QPushButton* m_editButton; 
    QPushButton* m_removeButton;
    QPushButton* m_executeSelectedButton;
    QPushButton* m_executeAllButton;

private slots:
    void onAddClick();
    void onEditClick();
    void onRemoveClick();
    void onExecuteSelectedClick();
    void onExecuteAllClick();
    void onCurrentChanged(const QModelIndex& current, const QModelIndex& previous);
};
