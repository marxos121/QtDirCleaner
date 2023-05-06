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

    void saveLog() const;
    virtual bool isValid() const;

    virtual void readIn(std::istream& is) = 0;
    virtual void execute() = 0;

protected:
	std::filesystem::path m_targetDirectory;
	std::unordered_set<std::string> m_targetExtensions;
    std::unordered_set<std::string> m_exemptFiles;

    const JobType m_type;
    bool m_isFinished;
    std::string m_log;

    const std::string LOG_DIRECTORY = "logs";
    void createLogDirectory() const;

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