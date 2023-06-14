#pragma once

#include <qstring.h>

class QtLog
{
public:
	QtLog& operator+=(const char* rhs);
	QtLog& operator+=(const QChar* rhs);
	QtLog& operator+=(const QString& rhs);
	void appendContent(const QString& l_content);
	void appendContent(const QtLog& rhs);

private:
	QString m_content;
	QString m_header;
	QString m_footer;

public:
	// ========== Setters and Getters ==========
	QString getAll(const QString& separator = "\n\n") const;
	const QString& getContent() const;
	const QString& getHeader() const;
	const QString& getFooter() const;

	void setContent(const QString& l_content);
	void setHeader(const QString& l_header);
	void setFooter(const QString& l_footer);
};

void clearLogContent(QtLog& log);
void saveLog(const QtLog& log, const QString& l_path = "log.dlog");
void appendAsContent(QtLog& to, const QtLog& from);