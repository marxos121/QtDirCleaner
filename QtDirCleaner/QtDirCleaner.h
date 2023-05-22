#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtDirCleaner.h"

#include "../DirCleaner.h"

class QtDirCleaner : public QMainWindow
{
    Q_OBJECT

public:
    QtDirCleaner(QWidget *parent = nullptr);
    ~QtDirCleaner();

private:
    Ui::QtDirCleanerClass ui;
    DirCleaner m_cleaner;

};
