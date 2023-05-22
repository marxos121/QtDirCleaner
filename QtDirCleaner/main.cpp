#include "QtDirCleaner.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtDirCleaner w;
    w.show();
    return a.exec();
}
