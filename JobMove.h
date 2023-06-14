#pragma once

#include "JobBase.h"

class JobMove : public JobBase {
public:
	JobMove();
	~JobMove() = default;

	virtual bool isReady() const override;

protected:
	virtual void setHeaderPending() override;
	virtual void setHeaderStarted() override;
	virtual void addDescription() override;
	virtual void addFooter() override;
	virtual void addSummary() override;

	virtual bool processFile(const QFileInfo& de) override;

private:
	QString m_destinationDirectory;

public:
	//Setters and getters
	void setDestinationPath(const QString& path);
	const QString& getDestinationPath() const;
};