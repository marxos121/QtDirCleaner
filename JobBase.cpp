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
    
    std::wstringstream logname;
    logname << ymd << " " << hhmmss.hours() << "-" << hhmmss.minutes() << "-" << hhmmss.seconds();
    createLogDirectory();

    //If LOG_DIRECTORY contains an absolute path, then use it; otherwise append to current path
    std::filesystem::path logPath =
        (LOG_DIRECTORY.string().length() > 1 && LOG_DIRECTORY.string()[1] == ':' ?
            LOG_DIRECTORY
            : std::filesystem::current_path() / LOG_DIRECTORY) / (logname.str() + L".dlog");
    m_log.save(logPath);
}

bool JobBase::isReady() const
{
    if (m_targetDirectories.empty())
    {
        std::cerr << "! Error! No target directory specified!" << std::endl;
        return false;
    }

    if (m_targetExtensions.empty())
    {
        std::cerr << "! Error! No target extension specified!" << std::endl;
        return false;
    }

    return true;
}

void JobBase::execute()
{
    if (!isReady() || m_isFinished)
    {
        return;
    }

    setHeaderStarted();
    addDescription();

    for(const auto& dir : m_targetDirectories)
    {
        if (!std::filesystem::exists(dir))
        {
            std::wcerr << "! Error! Specified target directory doesn't exist (" << dir << ")" << std::endl;
            continue;
        }

        else if (!std::filesystem::is_directory(dir))
        {
            std::wcerr << "! Error! Specified target path is not a directory! (" << dir << ")" << std::endl;
            continue;
        }

        for (auto& dirEntry : std::filesystem::directory_iterator(dir))
        {
            if (std::filesystem::is_directory(dirEntry))
            {
                continue;
            }

            const std::wstring currExtension = dirEntry.path().extension().wstring();
            const std::wstring currFilename = dirEntry.path().filename().wstring();

            if (m_targetExtensions.find(L".*") != m_targetExtensions.end()
                || (m_targetExtensions.find(currExtension) != m_targetExtensions.end()
                    && m_exemptFiles.find(currFilename) == m_exemptFiles.end()))
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
    m_log.clearContent();
}

void JobBase::addDescription()
{
    m_log += L"Target folder(s):\n";
    for (const auto& dir : m_targetDirectories)
    {
        m_log += dir.wstring() + L"\n";
    }

    m_log += L"\nTarget extension(s): ";
    for (const auto& ext : m_targetExtensions)
    {
        m_log += ext + L" ";
    }
    m_log += L"\n";
}

// ========== Setters and Getters ==========
JobType JobBase::getType() const {
    return m_type;
}

const Log<wchar_t>& JobBase::getLog() const {
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

void JobBase::setTargetExtensions(const std::initializer_list<std::wstring>& extensions) {
    m_targetExtensions = extensions;
}

void JobBase::addTargetExtension(const std::wstring& l_extension)
{
    m_targetExtensions.emplace(l_extension);
}

void JobBase::removeTargetExtension(const std::wstring& l_extension)
{
    m_targetExtensions.erase(l_extension);
}

void JobBase::clearTargetExtensions()
{
    m_targetExtensions.clear();
}

const std::unordered_set<std::wstring>& JobBase::getTargetExtensions() const {
    return m_targetExtensions;
}

void JobBase::setExemptFiles(const std::initializer_list<std::wstring>& l_exemptions)
{
    m_exemptFiles = l_exemptions;
}

void JobBase::addExemptFile(const std::wstring& l_filename)
{
    m_exemptFiles.emplace(l_filename);
}

void JobBase::removeExemptFile(const std::wstring& l_filename)
{
    m_exemptFiles.erase(l_filename);
}

const std::unordered_set<std::wstring>& JobBase::getExemptFiles() const
{
    return m_exemptFiles;
}

bool JobBase::isExempt(const std::wstring& l_filename) const
{
    return m_exemptFiles.find(l_filename) != m_exemptFiles.end();
}
