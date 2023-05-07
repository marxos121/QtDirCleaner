#pragma once

#include "JobBase.h"

class JobMove : public JobBase {
public:
	JobMove();
	JobMove(std::istream& is);
	~JobMove() = default;

	virtual void readIn(std::istream& is) override;
	virtual bool isValid() const override;

protected:
	virtual void addHeader() override;
	virtual void addFooter() override;
	virtual void addSummary() override;

	virtual bool processFile(const std::filesystem::directory_entry& de) override;

private:
	std::filesystem::path m_destinationDirectory;

public:
	//Setters and getters
	void setDestinationPath(const std::filesystem::path& path);
	const std::filesystem::path& getDestinationPath() const;
};