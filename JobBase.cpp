#include "JobBase.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <chrono>


JobBase::JobBase(JobType l_type)
    :  m_type(l_type), m_isFinished(false), m_matchingFiles(0), m_processedFiles(0)
{
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
    if (m_targetDirectories.empty())
    {
        std::cerr << "! Error! No target directory specified!" << std::endl;
        return false;
    }

    for (const auto& dir : m_targetDirectories)
    {
        if (!std::filesystem::exists(dir)) {
            std::cerr << "! Error! Specified target directory doesn't exist (" << dir << ")" << std::endl;
            return false;
        }

        if (!std::filesystem::is_directory(dir)) {
            std::cerr << "! Error! Specified target path is not a directory! (" << dir << ")" << std::endl;
            return false;
        }
    }

    return true;
}

void JobBase::execute()
{
    if (!isValid() || m_isFinished)
    {
        return;
    }

    clearLog();
    addHeader();

    for(const auto& dir : m_targetDirectories)
    {
        for (auto& dirEntry : std::filesystem::directory_iterator(dir))
        {
            const std::string currExtension = dirEntry.path().extension().string();
            const std::string currFilename = dirEntry.path().filename().string();

            if ((m_targetExtensions.empty() || m_targetExtensions.find(currExtension) != m_targetExtensions.end())
                && m_exemptFiles.find(currFilename) == m_exemptFiles.end())
            {
                ++m_matchingFiles;

                if (processFile(dirEntry))
                {
                    ++m_processedFiles;
                }
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

void JobBase::addTargetDirectory(const std::filesystem::path& path) {
    m_targetDirectories.emplace(path);
}

void JobBase::removeTargetDirectory(const std::filesystem::path& l_path)
{
    m_targetDirectories.erase(l_path);
}

const std::unordered_set<std::filesystem::path>& JobBase::getTargetDirectories() const {
    return m_targetDirectories;
}

void JobBase::setTargetExtensions(const std::initializer_list<std::string>& extensions) {
    m_targetExtensions = extensions;
}

void JobBase::addTargetExtension(const std::string& l_extension)
{
    m_targetExtensions.emplace(l_extension);
}

void JobBase::removeTargetExtension(const std::string& l_extension)
{
    m_targetExtensions.erase(l_extension);
}

const std::unordered_set<std::string>& JobBase::getTargetExtensions() const {
    return m_targetExtensions;
}

void JobBase::setExemptFiles(const std::initializer_list<std::string>& l_exemptions)
{
    m_exemptFiles = l_exemptions;
}

void JobBase::addExemptFile(const std::string& l_filename)
{
    m_exemptFiles.emplace(l_filename);
}

void JobBase::removeExemptFile(const std::string& l_filename)
{
    m_exemptFiles.erase(l_filename);
}

const std::unordered_set<std::string>& JobBase::getExemptFiles() const
{
    return m_exemptFiles;
}

bool JobBase::isExempt(const std::string& l_filename) const
{
    return m_exemptFiles.find(l_filename) != m_exemptFiles.end();
}
