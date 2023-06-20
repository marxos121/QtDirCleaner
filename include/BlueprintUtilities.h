#pragma once
#include <memory>

template <typename T> class QList;
class QStandardItemModel;
class QStandardItem;
class JobBase;
class JobBlueprint;

namespace Utilities
{
	JobBlueprint blueprintFromModel(const QStandardItemModel& model, int row);
	QList<QStandardItem*> blueprintToQList(const JobBlueprint& bp);
	std::shared_ptr<JobBase> createJob(const JobBlueprint& bp);
}