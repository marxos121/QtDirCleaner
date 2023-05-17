#include "DirCleaner.h"

#include "JobBase.h"
#include "JobMove.h"
#include "JobRemove.h"

#include <iostream>
#include <fstream>

#include <locale>

DirCleaner::DirCleaner()
{
	registerJobType<JobMove>(JobType::Move);
	registerJobType<JobRemove>(JobType::Remove);
}

DirCleaner::~DirCleaner()
{
	while (!m_jobs.empty())
	{
		delete m_jobs.front();
		m_jobs.pop_front();
	}
}

void DirCleaner::readInJobs(const std::filesystem::path& l_path)
{
	std::wifstream is(l_path);
	is.imbue(std::locale("en_US.utf8"));
	if (!is.is_open())
	{
		std::wcerr << "! Failed to open file: " << l_path << std::endl;
		return;
	}

	std::wstring line;
	while (std::getline(is, line))
	{
		std::wstring temp;
		std::wistringstream ss(line);

		ss >> temp;

		if (temp == L"[TYPE]")
		{
			ss >> temp;

			JobType type = strToJobType(temp);

			if (type == (JobType)-1)
			{
				continue;
			}

			m_jobs.push_back(m_jobFactory[type]());
			continue;
		}

		if (m_jobs.empty())
		{
			continue;
		}

		if (temp == L"[TARGET]")
		{
			std::wstring path;
			while (ss >> temp)
			{
				path += temp;
			}
			m_jobs.back()->addTargetDirectory(path);
		}

		else if (temp == L"[EXT]")
		{
			while (ss >> temp)
			{
				m_jobs.back()->addTargetExtension(temp);
			}
		}

		else if (temp == L"[EXEMPT]")
		{
			std::wstring path;
			while (ss >> temp)
			{
				path += temp + L' ';
			}

			path.pop_back();
			m_jobs.back()->addExemptFile(path);
		}

		else if (temp == L"[DEST]" && m_jobs.back()->getType() == JobType::Move)
		{
			auto currentJob = static_cast<JobMove*>(m_jobs.back());

			if (!currentJob->getDestinationPath().empty())
			{
				continue;
			}

			std::wstring path;
			while (ss >> temp)
			{
				path += temp;
			}
			currentJob->setDestinationPath(path);
		}
	}
}

void DirCleaner::addJob(JobBase* l_jb)
{
	JobBase* temp = nullptr;
	if (l_jb->getType() == JobType::Move) 
	{
		temp = new JobMove(*static_cast<JobMove*>(l_jb));
	}
	else if (l_jb->getType() == JobType::Remove)
	{
		temp = new JobRemove(*static_cast<JobRemove*>(l_jb));
	}
	m_jobs.push_back(l_jb);
}

void DirCleaner::executeNext()
{
	if (m_jobs.empty())
	{
		return;
	}

	m_jobs.front()->execute();
	m_log += m_jobs.front()->getLog() + L'\n';
	m_jobs.pop_front();

	++m_executedJobs;
}

void DirCleaner::executeAL() 
{
	while (!m_jobs.empty())
	{
		executeNext();
	}
}

void DirCleaner::saveLog()
{
	m_log += L"Executed " + std::to_wstring(m_executedJobs) + L" job" + (m_executedJobs == 1 ? L"" : L"s") + L".\n\n";
	std::wofstream os("DirCleanerLog.dlog", std::ios_base::app);
	os.imbue(std::locale("en_US.utf8"));
	os << m_log;
	os.close();
}

void DirCleaner::clearLogFile()
{
	std::ofstream os("DirCleanerLog.dlog");
	os.close();
}

JobType DirCleaner::strToJobType(const std::wstring& type) 
{
	if (type == L"move") {
		return JobType::Move;
	}

	if (type == L"remove") {
		return JobType::Remove;
	}

	return (JobType)-1;
}