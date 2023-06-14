#pragma once
#include "JobMove.h"
#include "JobRemove.h"

#include <vector>
#include <qstringlist.h>
#include <memory>
#include <optional>

class QStandardItemModel;
class QStandardItem;


struct JobBlueprint
{
	JobType type = JobType(-1);
	QStringList targetDirectories;
	QStringList targetExtensions;
	QStringList exemptFiles;
	QString moveDestination;
};


JobBlueprint blueprintFromModel(const QStandardItemModel& model, int row);
QList<QStandardItem*> blueprintToQList(const JobBlueprint& bp);
std::shared_ptr<JobBase> createJob(const JobBlueprint& bp);