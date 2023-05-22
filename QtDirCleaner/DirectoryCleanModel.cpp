#include "DirectoryCleanModel.h"

#include "../JobBase.h"
#include "../JobMove.h"

DirectoryCleanModel::DirectoryCleanModel()
{
    setHorizontalHeaderItem(0, new QStandardItem("Job Type"));
    setHorizontalHeaderItem(1, new QStandardItem("Extensions"));
    setHorizontalHeaderItem(2, new QStandardItem("Target Directories"));
    setHorizontalHeaderItem(3, new QStandardItem("Output Directory"));
}


void DirectoryCleanModel::addObject(const JobBase* obj)
{
    //1st col: JobType
    QString jobType = obj->getType() == JobType::Move ? "move" : "remove";
    QList<QStandardItem*> rowItems;
    rowItems.append(new QStandardItem(jobType));


    //2nd col: ext
    QString allExt;
    for(auto& str : obj->getTargetExtensions())
    {
        allExt += str + L"; ";
    }
    allExt.chop(2);
    rowItems.append(new QStandardItem(allExt));

    //3rd col: target dirs
    QString allTargetDirs;
    for(auto& path : obj->getTargetDirectories())
    {
        allTargetDirs += path.wstring() + L"; ";
    }
    allTargetDirs.chop(2);
    rowItems.append(new QStandardItem(allTargetDirs));

    //3rd col: output dir
    QString outputDir = QString::fromStdWString(L"");
    if(jobType == "move")
    {
        outputDir = QString::fromStdWString(static_cast<const JobMove*>(obj)->getDestinationPath().wstring());
    }
    rowItems.append(new QStandardItem(outputDir));

    appendRow(rowItems);
}

void DirectoryCleanModel::removeObject(int row)
{
    removeRow(row);
}
