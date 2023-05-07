#pragma once

#include "JobBase.h"

class JobRemove : public JobBase {
public:
	JobRemove();
	JobRemove(std::istream& is);
	~JobRemove() = default;

	virtual void readIn(std::istream& is) override;

protected:
	virtual void addHeader() override;
	virtual void addFooter() override;
	virtual void addSummary() override;

	virtual bool processFile(const std::filesystem::directory_entry& de) override;
};