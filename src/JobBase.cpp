#include "../include/JobBase.h"

#include <qdir.h>
#include <qlist.h>
#include <iostream>
#include <chrono>


JobBase::JobBase(JobType l_type)
    : m_type(l_type), m_isFinished(false), m_matchingFiles(0), m_processedFiles(0)
{
}


void JobBase::saveLog() const
{
    const auto date = QDate::currentDate();
    QString logname = QString("%1 %2-%3.dlog")
        .arg(Qt::ISODate)
        .arg(QDateTime::currentDateTime().time().hour())
        .arg(QDateTime::currentDateTime().time().minute());
    createLogDirectory();

    // If LOG_DIRECTORY contains an absolute path, then use it; otherwise, append to the current path
    QString logPath = (LOG_DIRECTORY.length() > 1 && LOG_DIRECTORY[1] == ':') ?
        LOG_DIRECTORY :
        QDir::currentPath() + QDir::separator() + LOG_DIRECTORY;
    logPath = logPath + QDir::separator() + logname + ".dlog";
    ::saveLog(m_log, logPath);
}

bool JobBase::isReady() const
{
    if (m_isFinished)
    {
        std::cerr << "! Error! Job already finished." << std::endl;
        return false;
    }

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
            std::wcerr << "! Error! Specified target directory doesn't exist (" << dir.toStdWString() << ")" << std::endl;
            continue;
        }

        for (const auto& file : QDir(dir).entryInfoList(QDir::Files))
        {
            auto path = file.absoluteFilePath();
            const auto currExtension = "." + file.completeSuffix();
            const auto currFilename = file.fileName();

            if ((m_targetExtensions.contains(".*") || m_targetExtensions.contains(currExtension)) 
                && !m_exemptFiles.contains(currFilename) 
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

void JobBase::createLogDirectory() const
{
    QDir dir(LOG_DIRECTORY);
    if (!dir.exists())
    {
        if (!dir.mkpath("."))
        {
            std::cerr << "! Error! Failed to create log directory." << std::endl;
        }
    }
}

void JobBase::clearLog()
{
    clearLogContent(m_log);
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

void JobBase::setFinished(bool finished)
{
    m_isFinished = finished;
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
