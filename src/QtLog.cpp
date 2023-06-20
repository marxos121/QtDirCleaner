#include "../include/QtLog.h"

QtLog& QtLog::operator+=(const char* rhs)
{
    return *this += QString(rhs);
}

QtLog& QtLog::operator+=(const QChar* rhs)
{
    return *this += QString(rhs);
}

QtLog& QtLog::operator+=(const QString& rhs)
{
    m_content.append(rhs);
    return *this;
}

void QtLog::appendContent(const QString& l_content)
{
    m_content.append(l_content);
}

void QtLog::appendContent(const QtLog& rhs)
{
    m_content.append(rhs.getContent());
}

// ========== Setter functions ==========
void QtLog::setContent(const QString& l_content) {
    m_content = l_content;
}

void QtLog::setHeader(const QString& l_header) {
    m_header = l_header;
}

void QtLog::setFooter(const QString& l_footer) {
    m_footer = l_footer;
}

// ========== Getter functions ==========

const QString& QtLog::getContent() const {
    return m_content;
}

const QString& QtLog::getHeader() const {
    return m_header;
}

const QString& QtLog::getFooter() const {
    return m_footer;
}

// ========== Non-member functions ==========
QtLog operator+(const QtLog& log, const QString& str)
{
    QtLog temp(log);
    temp += str;
    return temp;
}

QtLog operator+(const QtLog& log, const QChar* str)
{
    QtLog temp(log);
    temp += str;
    return temp;
}