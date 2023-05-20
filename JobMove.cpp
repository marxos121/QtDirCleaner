#include "JobMove.h"

#include <iostream>

JobMove::JobMove()
	: JobBase(JobType::Move)
{
	setHeaderPending();
}

bool JobMove::isReady() const
{
	bool valid = JobBase::isReady();

	if (!std::filesystem::exists(m_destinationDirectory)) 
	{
		try
		{
			std::filesystem::create_directories(m_destinationDirectory);
		}
		
		catch(...)
		{
			return false;
		}
	}
	else if (!std::filesystem::is_directory(m_destinationDirectory)) 
	{
		std::wcerr << "! Error! Specified destination path is not a directory! (" << m_destinationDirectory << ")" << std::endl;
		valid = false;
	}

	return valid;
}

void JobMove::setHeaderPending()
{
	m_log.setHeader(L"========MOVE JOB PENDING========");
}

void JobMove::setHeaderStarted()
{
	m_log.setHeader(L"========MOVE JOB STARTED========");
}

void JobMove::addDescription()
{
	m_log += L"Destination directory: " + m_destinationDirectory.wstring() + L"\n";
	JobBase::addDescription();
}

void JobMove::addFooter()
{
	if (m_isFinished) 
	{
		m_log.setFooter(L"========MOVE JOB COMPLETE========");
	}
	else 
	{
		m_log.setFooter(L"========COULDN'T COMPLETE MOVE JOB========");
	}
}

void JobMove::addSummary()
{
	m_log += std::to_wstring(m_processedFiles) + L" files out of " + std::to_wstring(m_matchingFiles) + L" moved.";
}

bool JobMove::processFile(const std::filesystem::directory_entry& de)
{
	bool result = false;
	try
	{
		std::filesystem::copy(de, m_destinationDirectory);
	}
	catch (const std::filesystem::filesystem_error& err)
	{
		std::cerr << "! System error: " << err.what() << std::endl;
		return false;
	}

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
		m_log += L"File " + de.path().filename().wstring() + L" moved to : " + m_destinationDirectory.wstring() + L'\n';
	}
	else
	{
		m_log += L"Couldn't remove file: " + de.path().filename().wstring() + L'\n';
	}

	return result;
}

void JobMove::setDestinationPath(const std::filesystem::path& path)
{
	m_destinationDirectory = path;
}

const std::filesystem::path& JobMove::getDestinationPath() const
{
	return m_destinationDirectory;
}
