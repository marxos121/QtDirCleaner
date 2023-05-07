#pragma once

#include "JobBase.h"

class JobRemove : public JobBase {
public:
	JobRemove();
	JobRemove(std::istream& is);
	~JobRemove() = default;

	virtual void readIn(std::istream& is) override;
	virtual void execute() override;
};