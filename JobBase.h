#pragma once

#include "QtDirCleaner/QtLog.h"

#include <qstring.h>
#include <qset.h>

class QFileInfo;

enum class JobType 
{
    Move, Remove
};

inline QString to_string(JobType type)
{
    return type == JobType::Move ? "Move" : 
        (type == JobType::Remove ? "Remove" : "Error");
}


inline JobType strToJobType(const QString& type)
{
    if (type.toLower() == "move") {
        return JobType::Move;
    }

    if (type.toLower() == "remove") {
        return JobType::Remove;
    }

    return (JobType)-1;
}

class JobBase {
public:
    JobBase(JobType l_type);
    virtual ~JobBase() = default;

    void execute();

    void saveLog() const;
    virtual bool isReady() const;

protected:
	QSet<QString> m_targetDirectories;
    QSet<QString> m_targetExtensions;
    QSet<QString> m_exemptFiles;

    int m_processedFiles;
    int m_matchingFiles;
    bool m_isFinished;  //maybe change to enum class Status { pending, started, finished }
    QtLog m_log;

    void createLogDirectory() const;
    void clearLog();
    virtual void setHeaderPending() = 0;
    virtual void setHeaderStarted() = 0;
    virtual void addDescription();
    virtual void addFooter() = 0;
    virtual void addSummary() = 0;

    virtual bool processFile(const QFileInfo& de) = 0;

private:
    //For internal use only
    const QString LOG_DIRECTORY = "logs";
    const JobType m_type;

public: 
    // ========== Setters and Getters ==========
    JobType getType() const;
    const QtLog& getLog() const;

    void setFinished(bool l_finished);
    bool getFinished() const;

    void setTargetDirectories(const QStringList& L_directories);
    void addTargetDirectory(const QString& l_path);
    void removeTargetDirectory(const QString& l_path);
    const QSet<QString>& getTargetDirectories() const;

    void setTargetExtensions(const QStringList& l_extensions);
    void addTargetExtension(const QString& l_extension);
    void removeTargetExtension(const QString& l_extension);
    void clearTargetExtensions();
    const QSet<QString>& getTargetExtensions() const;

    void setExemptFiles(const QStringList& l_exemptions);
    void addExemptFile(const QString& l_filename);
    void removeExemptFile(const QString& l_filename);
    const QSet<QString>& getExemptFiles() const;
    bool isExempt(const QString& l_filename) const;
};