#include "JobBase.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <chrono>


JobBase::JobBase(JobType l_type)
    :  m_type(l_type), m_isFinished(false)
{
}

JobBase::JobBase(JobType l_type, std::istream& is)
    : m_type(l_type), m_isFinished(false)
{
    readIn(is);
}


void JobBase::saveLog() const
{
    const std::chrono::time_point now{ std::chrono::system_clock::now() };
    const std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>(now) };
    const std::chrono::hh_mm_ss hhmmss{ std::chrono::floor<std::chrono::milliseconds>(now -
        std::chrono::floor<std::chrono::days>(now)) };
    
    std::stringstream logname;
    logname << ymd << " " << hhmmss.hours() << "-" << hhmmss.minutes() << "-" << hhmmss.seconds();
    std::ofstream m_file(LOG_DIRECTORY + "/" + logname.str() + ".dlog");
    m_file << m_log;
    m_file.close();
}

bool JobBase::isValid() const
{
    if (m_targetDirectory.string().empty()) {
        std::cerr << "! Error! No target directory specified!" << std::endl;
        return false;
    }
    if (!std::filesystem::exists(m_targetDirectory)) {
        std::cerr << "! Error! Specified target directory doesn't exist (" << m_targetDirectory << ")" << std::endl;
        return false;
    }

    if (!std::filesystem::is_directory(m_targetDirectory)) {
        std::cerr << "! Error! Specified target path is not a directory! (" << m_targetDirectory << ")" << std::endl;
        return false;
    }

    return true;
}

void JobBase::execute()
{
    if (!isValid())
    {
        return;
    }

    clearLog();
    addHeader();

    for (auto& dirEntry : std::filesystem::directory_iterator(m_targetDirectory)) 
    {
        const std::string currExtension = dirEntry.path().extension().string();
        const std::string currFilename = dirEntry.path().filename().string();

        if ((m_targetExtensions.empty() || m_targetExtensions.find(currExtension) != m_targetExtensions.end())
            && m_exemptFiles.find(currFilename) == m_exemptFiles.end())
        {
            ++m_matchingFiles;

            if (processFile(dirEntry)) {
                ++m_processedFiles;
            }
        }
    }

    addSummary();

    m_isFinished = m_matchingFiles == m_processedFiles;

    addFooter();
    saveLog();

    //Universal job steps:
    //1. validate Job object	(virtual)
    //2. clear log + add header (v function)
    //3. iterate over dir
    //		3a. check conditions
    //		3b. do the job	(virtual) -> return t/f whether it succeeded
    //		3c. log the status and (optional) increment processed files count
    //4. Log the final report (virtual)
    //5. Add footer (virtual)
    //6. Save log
}

void JobBase::createLogDirectory() const
{
    if (std::filesystem::exists(LOG_DIRECTORY)) {
        return;
    }
    std::filesystem::create_directory(LOG_DIRECTORY);
}

void JobBase::clearLog()
{
    m_log.clear();
}

// ========== Setters and Getters ==========
JobType JobBase::getType() const {
    return m_type;
}

const std::string& JobBase::getLog() const {
    return m_log;
}

void JobBase::setFinished(bool finished) {
    m_isFinished = finished;
}

bool JobBase::getFinished() const {
    return m_isFinished;
}

void JobBase::setTargetDirectory(const std::filesystem::path& path) {
    m_targetDirectory = path;
}

const std::filesystem::path& JobBase::getTargetDirectory() const {
    return m_targetDirectory;
}

void JobBase::setTargetExtensions(const std::unordered_set<std::string>& extensions) {
    m_targetExtensions = extensions;
}

const std::unordered_set<std::string>& JobBase::getTargetExtensions() const {
    return m_targetExtensions;
}