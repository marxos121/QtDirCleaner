#include "JobMove.h"

#include <iostream>
#include <qdir.h>

JobMove::JobMove()
	: JobBase(JobType::Move)
{
	setHeaderPending();
}

bool JobMove::isReady() const
{
	bool valid = JobBase::isReady();

	QDir dir(m_destinationDirectory);
	if (!dir.exists()) 
	{
		bool res = dir.mkpath(".");

		if (!res)
		{
			std::wcerr << "! Error! could not create a directory! (" << m_destinationDirectory.toStdWString() << ")" << std::endl;
		}
	}
	else if (!QFileInfo(dir.path()).isDir())
	{
		std::wcerr << "! Error! Specified destination path is not a directory! (" << m_destinationDirectory.toStdWString() << ")" << std::endl;
		valid = false;
	}

	return valid;
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
	if (m_isFinished) 
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
	m_log += QString::number(m_processedFiles) + " files out of " + QString::number(m_matchingFiles) + " moved.";
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

	bool result = QFile::copy(fileInfo.filePath(),
		destinationFilePath.absolutePath() + QDir::separator() + filename);

	if (result)
	{
		result = QFile::remove(fileInfo.filePath());

		if (result)
		{
			m_log += "File " + fileInfo.fileName() + " moved to: " + m_destinationDirectory + '\n';
		}
		else
		{
			m_log += "Couldn't remove file: " + fileInfo.fileName() + '\n';
		}
	}
	else
	{
		qDebug() << "Failed to copy file: " << fileInfo.filePath();
	}

	return result;
}
void JobMove::setDestinationPath(const QString& path)
{
	m_destinationDirectory = path;
}

const QString& JobMove::getDestinationPath() const
{
	return m_destinationDirectory;
}
