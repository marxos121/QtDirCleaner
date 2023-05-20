#pragma once

#include <deque>
#include <string>
#include <functional>

#include "JobBase.h"
#include "Log.h"

class DirCleaner {
public:
	DirCleaner();
	~DirCleaner();

	void readInJobs(const std::filesystem::path& l_path = L"jobs.jobs");
	void addJob(JobBase* l_jb);

	void executeNext();
	void executeAll();

	void saveLog();
	void clearLogFile();

private:
	std::deque<JobBase*> m_jobs;
	Log<wchar_t> m_log;
	int m_executedJobs;

	//Factory
	std::unordered_map<JobType, std::function<JobBase* ()>> m_jobFactory;
	template <typename T>
	void registerJobType(JobType l_type)
	{
		auto fact = []()
		{
			return new T();
		};

		m_jobFactory.emplace(l_type, fact);
	}

	JobType strToJobType(const std::wstring& type);
};