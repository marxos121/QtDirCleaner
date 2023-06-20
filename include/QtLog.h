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
	const QString& getContent() const;
	const QString& getHeader() const;
	const QString& getFooter() const;

	void setContent(const QString& l_content);
	void setHeader(const QString& l_header);
	void setFooter(const QString& l_footer);
};
