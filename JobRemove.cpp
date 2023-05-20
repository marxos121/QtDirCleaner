#include "JobRemove.h"

#include <iostream>

JobRemove::JobRemove()
	: JobBase(JobType::Remove)
{
	setHeaderPending();
}

void JobRemove::setHeaderPending()
{
	m_log += L"========REMOVE JOB PENDING========";
}

void JobRemove::setHeaderStarted()
{
	m_log.setHeader(L"========REMOVE JOB STARTED========");
}

void JobRemove::addFooter()
{
	if (m_isFinished) {
		m_log += L"========REMOVE JOB COMPLETE========";
	}
	else {
		m_log += L"========COULDN'T COMPLETE REMOVE JOB========";
	}
}

void JobRemove::addSummary()
{
	m_log += std::to_wstring(m_processedFiles) + L" files out of " + std::to_wstring(m_matchingFiles) + L" removed.\n\n";
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
		return false;
	}

	if (result)
	{
		m_log += L"File removed: " + de.path().filename().wstring() + L'\n';
	}
	else
	{
		m_log += L"Couldn't remove file: " + de.path().filename().wstring() + L'\n';
	}

	return result;
}