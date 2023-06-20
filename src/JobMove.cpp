#include "../include/JobMove.h"
#include "../include/Utilities.h"

#include <qdir.h>

JobMove::JobMove()
	: JobBase(JobType::Move)
{
	setHeaderPending();
}

void JobMove::setHeaderPending()
{
	m_log.setHeader("========MOVE JOB PENDING========");
}

void JobMove::setHeaderStarted()
{
	m_log.setHeader("========MOVE JOB STARTED========");
}

void JobMove::addDescription()
{
	m_log += "Destination directory: " + m_destinationDirectory + "\n";
	JobBase::addDescription();
}

void JobMove::addFooter()
{
	if (getFinished()) 
	{
		m_log.setFooter("========MOVE JOB COMPLETE========");
	}
	else 
	{
		m_log.setFooter("========COULDN'T COMPLETE MOVE JOB========");
	}
}

void JobMove::addSummary()
{
	m_log += QString::number(getProcessedFiles()) + " files out of " + QString::number(getMatchingFiles()) + " moved.";
}

bool JobMove::processFile(const QFileInfo& fileInfo)
{
	QDir destinationFilePath = m_destinationDirectory;
	QString filename = fileInfo.fileName();

	int n = 1;
	while (destinationFilePath.exists(filename))
	{
		filename = fileInfo.baseName() + " (" + QString::number(n) + ")." + fileInfo.completeSuffix();
		n++;
	}

	if (QFile::copy(fileInfo.filePath(),
		destinationFilePath.absolutePath() + QDir::separator() + filename))
	{
		if (QFile::remove(fileInfo.filePath()))
		{
			m_log += "File " + fileInfo.fileName() + " moved to: " + m_destinationDirectory + '\n';
			return true;
		}
		else
		{
			m_log += "Couldn't remove file: " + fileInfo.fileName() + '\n';
			return false;
		}
	}
	m_log += "Failed to copy file: " + fileInfo.filePath();
	return false;
}

bool JobMove::isReady() const
{
	return JobBase::isReady() && !m_destinationDirectory.isEmpty();
}

void JobMove::setDestinationPath(const QString& path)
{
	m_destinationDirectory = path;
}

const QString& JobMove::getDestinationPath() const
{
	return m_destinationDirectory;
}
