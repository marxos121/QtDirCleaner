#pragma once
#include <qstringlist.h>

enum class JobType;

struct JobBlueprint
{
	JobType type = JobType(-1);
	QStringList targetDirectories;
	QStringList targetExtensions;
	QStringList exemptFiles;
	QString moveDestination;
};
