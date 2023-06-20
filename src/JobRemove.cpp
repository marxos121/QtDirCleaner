#include "../include/JobRemove.h"

#include <qfileinfo.h>

JobRemove::JobRemove()
	: JobBase(JobType::Remove)
{
	setHeaderPending();
}

void JobRemove::setHeaderPending()
{
	m_log += "========REMOVE JOB PENDING========";
}

void JobRemove::setHeaderStarted()
{
	m_log.setHeader("========REMOVE JOB STARTED========");
}

void JobRemove::addFooter()
{
	if (getFinished()) {
		m_log += "========REMOVE JOB COMPLETE========";
	}
	else {
		m_log += "========COULDN'T COMPLETE REMOVE JOB========";
	}
}

void JobRemove::addSummary()
{
	m_log += QString::number(getProcessedFiles()) + " files out of " + QString::number(getMatchingFiles()) + " removed.\n\n";
}

bool JobRemove::processFile(const QFileInfo& file)
{
	if (QFile::remove(file.absoluteFilePath()))
	{
		m_log += "File removed: " + file.path() + L'\n';
		return true;
	}
	else
	{
		m_log += "Couldn't remove file: " + file.path() + L'\n';
		return false;
	}
}