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
    JobBase(JobType l_type, std::istream& is);
    virtual ~JobBase() = default;


    void execute();

    void saveLog() const;
    virtual bool isValid() const;

    virtual void readIn(std::istream& is) = 0;

protected:
	std::filesystem::path m_targetDirectory;
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

    void setTargetDirectory(const std::filesystem::path& l_path);
    const std::filesystem::path& getTargetDirectory() const;

    void setTargetExtensions(const std::unordered_set<std::string>& l_extensions);
    const std::unordered_set<std::string>& getTargetExtensions() const;
};