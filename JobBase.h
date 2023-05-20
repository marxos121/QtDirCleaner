#pragma once

#include "Log.h"

#include <filesystem>
#include <unordered_set>
#include <string>

enum JobType 
{
    Move, Remove
};

class JobBase {
public:
    JobBase(JobType l_type);
    virtual ~JobBase() = default;

    void execute();

    void saveLog() const;
    virtual bool isReady() const;

protected:
	std::unordered_set<std::filesystem::path> m_targetDirectories;
	std::unordered_set<std::wstring> m_targetExtensions;
    std::unordered_set<std::wstring> m_exemptFiles;

    int m_processedFiles;
    int m_matchingFiles;
    bool m_isFinished;
    Log<wchar_t> m_log;

    void createLogDirectory() const;
    void clearLog();
    virtual void setHeaderPending() = 0;
    virtual void setHeaderStarted() = 0;
    virtual void addDescription();
    virtual void addFooter() = 0;
    virtual void addSummary() = 0;

    virtual bool processFile(const std::filesystem::directory_entry& de) = 0;

private:
    //For internal use only
    const std::filesystem::path LOG_DIRECTORY = L"logs";
    const JobType m_type;

public: 
    // ========== Setters and Getters ==========
    JobType getType() const;
    const Log<wchar_t>& getLog() const;

    void setFinished(bool l_finished);
    bool getFinished() const;

    void addTargetDirectory(const std::filesystem::path& l_path);
    void removeTargetDirectory(const std::filesystem::path& l_path);
    const std::unordered_set<std::filesystem::path>& getTargetDirectories() const;

    void setTargetExtensions(const std::initializer_list<std::wstring>& l_extensions);
    void addTargetExtension(const std::wstring& l_extension);
    void removeTargetExtension(const std::wstring& l_extension);
    const std::unordered_set<std::wstring>& getTargetExtensions() const;

    void setExemptFiles(const std::initializer_list<std::wstring>& l_exemptions);
    void addExemptFile(const std::wstring& l_filename);
    void removeExemptFile(const std::wstring& l_filename);
    const std::unordered_set<std::wstring>& getExemptFiles() const;
    bool isExempt(const std::wstring& l_filename) const;
};