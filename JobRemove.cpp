#include "JobRemove.h"

#include <iostream>

JobRemove::JobRemove()
	: JobBase(JobType::Remove)
{
}

void JobRemove::addHeader()
{
	m_log += "========REMOVE JOB STARTED========\n\n";
}

void JobRemove::addFooter()
{
	if (m_isFinished) {
		m_log += "========REMOVE JOB COMPLETE========\n\n";
	}
	else {
		m_log += "========COULDN'T COMPLETE REMOVE JOB========\n\n";
	}
}

void JobRemove::addSummary()
{
	m_log += std::to_string(m_processedFiles) + " files out of " + std::to_string(m_matchingFiles) + " removed.\n\n";
}

bool JobRemove::processFile(const std::filesystem::directory_entry& de)
{
	bool result = false;
	try
	{
		result = std::filesystem::remove(de);
	}
	catch (const std::filesystem::filesystem_error& err)
	{
		std::cerr << "! System error: " << err.what() << std::endl;
		m_log += err.what() + '\n';
		return false;
	}

	if (result)
	{
		m_log += "File removed: " + de.path().filename().string() + '\n';
	}
	else
	{
		m_log += "Couldn't remove file: " + de.path().filename().string() + '\n';
	}

	return result;
}