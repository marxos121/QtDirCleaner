#pragma once

#include <filesystem>
#include <unordered_set>
#include <string>

enum JobType {
    Move, Remove
};

class JobBase {
public:
    JobBase(JobType l_type);
    virtual ~JobBase() = default;

    void execute();

    void saveLog() const;
    virtual bool isValid() const;

protected:
	std::unordered_set<std::filesystem::path> m_targetDirectories;
	std::unordered_set<std::string> m_targetExtensions;
    std::unordered_set<std::string> m_exemptFiles;

    int m_processedFiles;
    int m_matchingFiles;
    bool m_isFinished;
    std::string m_log;

    void createLogDirectory() const;
    void clearLog();
    virtual void addHeader() = 0;
    virtual void addFooter() = 0;
    virtual void addSummary() = 0;

    virtual bool processFile(const std::filesystem::directory_entry& de) = 0;

private:
    //For internal use only
    const std::string LOG_DIRECTORY = "logs";
    const JobType m_type;

public: 
    // ========== Setters and Getters ==========
    JobType getType() const;
    const std::string& getLog() const;

    void setFinished(bool l_finished);
    bool getFinished() const;

    void addTargetDirectory(const std::filesystem::path& l_path);
    void removeTargetDirectory(const std::filesystem::path& l_path);
    const std::unordered_set<std::filesystem::path>& getTargetDirectories() const;

    void setTargetExtensions(const std::initializer_list<std::string>& l_extensions);
    void addTargetExtension(const std::string& l_extension);
    void removeTargetExtension(const std::string& l_extension);
    const std::unordered_set<std::string>& getTargetExtensions() const;

    void setExemptFiles(const std::initializer_list<std::string>& l_exemptions);
    void addExemptFile(const std::string& l_filename);
    void removeExemptFile(const std::string& l_filename);
    const std::unordered_set<std::string>& getExemptFiles() const;
    bool isExempt(const std::string& l_filename) const;
};