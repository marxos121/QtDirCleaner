#include "../include/JobBase.h"
#include "../include/LogUtilities.h"
#include <qdir.h>

JobBase::JobBase(JobType l_type)
    : m_type(l_type), m_isFinished(false), m_matchingFiles(0), m_processedFiles(0)
{
}

void JobBase::execute()
{
    if (!isReady())
    {
        return;
    }

    setHeaderStarted();
    addDescription();

    for (const auto& dir : m_targetDirectories)
    {
        if (!QDir(dir).exists())
        {
            m_log += "! Error! Specified target directory doesn't exist (" + dir + ")\n";
            continue;
        }

        for (const auto& file : QDir(dir).entryInfoList(QDir::Files))
        {
            auto path = file.absoluteFilePath();
            const auto currExtension = "." + file.completeSuffix();

            if ((m_targetExtensions.contains(".*") || m_targetExtensions.contains(currExtension)) 
                && !m_exemptFiles.contains(path))
            {
                ++m_matchingFiles;

                if (processFile(file))
                {
                    ++m_processedFiles;
                }
            }
        }
    }

    addSummary();

    m_isFinished = (m_matchingFiles == m_processedFiles);

    addFooter();
}

bool JobBase::isReady() const
{
    return !(getFinished() || m_targetDirectories.empty() || m_targetExtensions.empty());;
}

void JobBase::clearLog()
{
    Utilities::clearLogContent(m_log);
}

void JobBase::addDescription()
{
    m_log += "Target folder(s):\n";
    for (const auto& dir : m_targetDirectories)
    {
        m_log += dir + "\n";
    }

    m_log += "\nTarget extension(s): ";
    for (const auto& ext : m_targetExtensions)
    {
        m_log += ext + " ";
    }
    m_log += "\n";
}

// ========== Setters and Getters ==========
JobType JobBase::getType() const
{
    return m_type;
}

const QtLog& JobBase::getLog() const
{
    return m_log;
}

bool JobBase::getFinished() const
{
    return m_isFinished;
}

void JobBase::setTargetDirectories(const QStringList& l_directories)
{
    m_targetDirectories = QSet<QString>(l_directories.begin(), l_directories.end());
}

void JobBase::addTargetDirectory(const QString& path)
{
    m_targetDirectories.insert(path);
}

void JobBase::removeTargetDirectory(const QString& path)
{
    m_targetDirectories.remove(path);
}

const QSet<QString>& JobBase::getTargetDirectories() const
{
    return m_targetDirectories;
}

void JobBase::setTargetExtensions(const QStringList& l_extensions)
{
    m_targetExtensions = QSet<QString>(l_extensions.begin(), l_extensions.end());
}

void JobBase::addTargetExtension(const QString& extension)
{
    m_targetExtensions.insert(extension);
}

void JobBase::removeTargetExtension(const QString& extension)
{
    m_targetExtensions.remove(extension);
}

void JobBase::clearTargetExtensions()
{
    m_targetExtensions.clear();
}

const QSet<QString>& JobBase::getTargetExtensions() const
{
    return m_targetExtensions;
}

void JobBase::setExemptFiles(const QStringList& l_exemptions)
{
    m_exemptFiles = QSet<QString>(l_exemptions.begin(), l_exemptions.end());;
}

void JobBase::addExemptFile(const QString& filename)
{
    m_exemptFiles.insert(filename);
}

void JobBase::removeExemptFile(const QString& filename)
{
    m_exemptFiles.remove(filename);
}

const QSet<QString>& JobBase::getExemptFiles() const
{
    return m_exemptFiles;
}

bool JobBase::isExempt(const QString& filename) const
{
    return m_exemptFiles.contains(filename);
}

int JobBase::getMatchingFiles() const
{
    return m_matchingFiles;
}

int JobBase::getProcessedFiles() const
{
    return m_processedFiles;
}
