#pragma once

#include "../include/QtLog.h"

#include <qset.h>

class QFileInfo;

enum class JobType 
{
    Move, Remove
};

class JobBase {
public:
    JobBase(JobType l_type);
    virtual ~JobBase() = default;

    void execute();

private:
    const JobType m_type;
    bool m_isFinished;  //maybe change to enum class Status { pending, started, finished 

    int m_processedFiles;
    int m_matchingFiles;

    QSet<QString> m_targetDirectories;
    QSet<QString> m_targetExtensions;
    QSet<QString> m_exemptFiles;

    virtual bool processFile(const QFileInfo& de) = 0;

protected:
    virtual bool isReady() const;
    QtLog m_log;

    void clearLog();
    virtual void setHeaderPending() = 0;
    virtual void setHeaderStarted() = 0;
    virtual void addDescription();
    virtual void addFooter() = 0;
    virtual void addSummary() = 0;


public: 
    // ========== Setters and Getters ==========
    JobType getType() const;
    const QtLog& getLog() const;

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

    int getMatchingFiles() const;
    int getProcessedFiles() const;
};