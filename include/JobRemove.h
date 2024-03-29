#pragma once

#include "../include/JobBase.h"

class JobRemove : public JobBase {
public:
	JobRemove();
	~JobRemove() = default;

protected:
	virtual void setHeaderPending() override;
	virtual void setHeaderStarted() override;
	virtual void addFooter() override;
	virtual void addSummary() override;

private:
	virtual bool processFile(const QFileInfo& file) override;
};