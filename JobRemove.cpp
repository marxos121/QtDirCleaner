#include "JobRemove.h"

#include <iostream>

JobRemove::JobRemove()
	: JobBase(JobType::Remove)
{
}

JobRemove::JobRemove(std::istream& is)
	: JobBase(JobType::Remove)
{
	readIn(is);
}

void JobRemove::readIn(std::istream& is)
{
}

void JobRemove::execute()
{
	if (!isValid()) 
	{
		return;
	}

	m_log.clear();
	m_log += "========REMOVE JOB STARTED========\n\n";

	int matchingFiles = 0;
	int processedFiles = 0;

	for (auto& dirEntry : std::filesystem::directory_iterator(m_targetDirectory)) 
	{
		std::string currExtension = dirEntry.path().extension().string();

		if (m_targetExtensions.find(currExtension) != m_targetExtensions.end()
			&& m_exemptFiles.find(dirEntry.path().filename().string()) == m_exemptFiles.end()) 
		{

			++matchingFiles;

			try
			{
				std::filesystem::remove(dirEntry);
			}
			catch (const std::filesystem::filesystem_error& err) 
			{
				std::cerr << "! Error: " << err.what() << std::endl;
				m_log += err.what() + '\n';
				continue;
			}

			m_log += "File removed: " + dirEntry.path().filename().string() + currExtension + '\n';
			++processedFiles;
		}
	}

	m_log += std::to_string(processedFiles) + " files out of " + std::to_string(matchingFiles) + " removed.\n\n";

	if (matchingFiles == processedFiles) 
	{
		m_isFinished = true;
		
		m_log += "========REMOVE JOB COMPLETE========\n\n";
	}

	else 
	{
		m_isFinished = false;

		m_log += "========COULDN'T COMPLETE REMOVE JOB========\n\n";
	}

	saveLog();
}
