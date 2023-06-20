#include "../include/JobBlueprint.h"
#include "../include/BlueprintUtilities.h"
#include "../include/Columns.h"
#include "../include/Utilities.h"
#include "../include/JobMove.h"
#include "../include/JobRemove.h"

#include <qstandarditemmodel.h>
#include <memory>

JobBlueprint Utilities::blueprintFromModel(const QStandardItemModel& model, int row)
{
	JobBlueprint ret;
	if (!model.index(row, 0).isValid())
	{
		return ret;
	}

	ret.type = Utilities::strToJobType(model.data(model.index(row, CleanModelColumns::Type)).toString());
	ret.targetDirectories = model.data(model.index(row, CleanModelColumns::TargetDirs)).toString().split("; ");
	ret.exemptFiles = model.data(model.index(row, CleanModelColumns::Exempt)).toString().split("; ");
	ret.targetExtensions = model.data(model.index(row, CleanModelColumns::Extensions)).toString().split("; ");
	ret.moveDestination = ret.type == JobType::Move ? 
		model.data(model.index(row, CleanModelColumns::Destination)).toString() : "";

	return ret;
}

QList<QStandardItem*> Utilities::blueprintToQList(const JobBlueprint& bp)
{
	QList<QStandardItem*> ret;
	ret.append(new QStandardItem(Utilities::to_string(bp.type)));

	auto to_string = [](const QStringList& list) -> QString {
		QString result;
		for (const auto& str : list) {
			result += str + "; ";
		}
		result.chop(2);
		return result;
	};

	ret.append(new QStandardItem(to_string(bp.targetExtensions)));
	ret.append(new QStandardItem(to_string(bp.targetDirectories)));

	if (bp.type == JobType::Move)
	{
		ret.append(new QStandardItem(bp.moveDestination));
	}

	return ret;
}

std::shared_ptr<JobBase> Utilities::createJob(const JobBlueprint& bp)
{
	if (bp.type == JobType(-1))
	{
		return nullptr;
	}

	std::shared_ptr<JobBase> ret = nullptr;;

	if (bp.type == JobType::Move)
	{
		ret = std::make_shared<JobMove>();
		std::static_pointer_cast<JobMove>(ret)->setDestinationPath(bp.moveDestination);
	}
	else
	{
		ret = std::make_shared<JobRemove>();
	}

	ret->setTargetDirectories(bp.targetDirectories);
	ret->setTargetExtensions(bp.targetExtensions);
	ret->setExemptFiles(bp.exemptFiles);
	return ret;
}