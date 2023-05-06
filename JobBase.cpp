#include "JobBase.h"

#include <iostream>


JobBase::JobBase(JobType l_type)
    :  m_type(l_type), m_isFinished(false)
{
}

JobBase::JobBase(JobType l_type, std::istream& is)
    : m_type(l_type), m_isFinished(false)
{
    readIn(is);
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