#ifndef DIRECTORYCLEANMODEL_H
#define DIRECTORYCLEANMODEL_H

#include <QStandardItemModel>

class JobBase;

class DirectoryCleanModel : public QStandardItemModel
{
public:
    DirectoryCleanModel();

    void addObject(const JobBase* obj);
    void removeObject(int row);
};

#endif // DIRECTORYCLEANMODEL_H
