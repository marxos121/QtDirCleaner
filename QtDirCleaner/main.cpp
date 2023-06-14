#include "QtDirCleaner.h"
#include <QtWidgets/QApplication>
#include <qstyle.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtDirCleaner w;
    w.show();
    return a.exec();
}
