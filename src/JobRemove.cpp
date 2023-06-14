#include "../include/JobRemove.h"

#include <iostream>
#include <qfileinfo.h>
#include <qfile.h>

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
	if (m_isFinished) {
		m_log += "========REMOVE JOB COMPLETE========";
	}
	else {
		m_log += "========COULDN'T COMPLETE REMOVE JOB========";
	}
}

void JobRemove::addSummary()
{
	m_log += QString::number(m_processedFiles) + " files out of " + QString::number(m_matchingFiles) + " removed.\n\n";
}

bool JobRemove::processFile(const QFileInfo& file)
{
	bool result = false;
	result = QFile::remove(file.absoluteFilePath());

	if (result)
	{
		m_log += "File removed: " + file.path() + L'\n';
	}
	else
	{
		m_log += "Couldn't remove file: " + file.path() + L'\n';
	}

	return result;
}