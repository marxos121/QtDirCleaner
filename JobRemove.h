#pragma once

#include "JobBase.h"

class JobRemove : public JobBase {
public:
	JobRemove();
	~JobRemove() = default;

protected:
	virtual void addHeader() override;
	virtual void addFooter() override;
	virtual void addSummary() override;

	virtual bool processFile(const std::filesystem::directory_entry& de) override;
};