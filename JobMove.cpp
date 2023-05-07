#include "JobMove.h"

#include <iostream>

JobMove::JobMove()
	: JobBase(JobType::Move)
{
}

bool JobMove::isValid() const
{
	bool valid = JobBase::isValid();

	if (!std::filesystem::exists(m_destinationDirectory)) 
	{
		std::filesystem::create_directories(m_destinationDirectory);
	}
	else if (!std::filesystem::is_directory(m_destinationDirectory)) 
	{
		std::cerr << "! Error! Specified destination path is not a directory! (" << m_destinationDirectory << ")" << std::endl;
		valid = false;
	}

	return valid;
}

void JobMove::addHeader()
{
	m_log += "========MOVE JOB STARTED========\n\n";
}

void JobMove::addFooter()
{
	if (m_isFinished) 
	{
		m_log += "========MOVE JOB COMPLETE========\n\n";
	}
	else 
	{
		m_log += "========COULDN'T COMPLETE MOVE JOB========\n\n";
	}
}

void JobMove::addSummary()
{
	m_log += std::to_string(m_processedFiles) + " files out of " + std::to_string(m_matchingFiles) + " moved.\n\n";
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
		m_log += err.what() + '\n';
		return false;
	}

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

void JobMove::setDestinationPath(const std::filesystem::path& path)
{
	m_destinationDirectory = path;
}

const std::filesystem::path& JobMove::getDestinationPath() const
{
	return m_destinationDirectory;
}
