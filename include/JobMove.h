#pragma once

#include "../include/JobBase.h"

class JobMove : public JobBase {
public:
	JobMove();
	~JobMove() = default;

protected:
	bool isReady() const override;
	virtual void setHeaderPending() override;
	virtual void setHeaderStarted() override;
	virtual void addDescription() override;
	virtual void addFooter() override;
	virtual void addSummary() override;

private:
	QString m_destinationDirectory;
	virtual bool processFile(const QFileInfo& de) override;

public:
	//Setters and getters
	void setDestinationPath(const QString& path);
	const QString& getDestinationPath() const;
};