#pragma once

#include "JobBase.h"

class JobMove : public JobBase {
public:
	JobMove();
	JobMove(std::istream& is);
	~JobMove() = default;

	virtual void readIn(std::istream& is) override;
	virtual void execute() override;
	virtual bool isValid() const override;

private:
	std::filesystem::path m_destinationDir;

public:
	//Setters and getters
	void setDestinationPath(const std::filesystem::path& path);
	const std::filesystem::path& getDestinationPath() const;
};