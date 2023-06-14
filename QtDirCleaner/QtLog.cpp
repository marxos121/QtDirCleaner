#include "QtLog.h"

#include <qfile.h>
#include <qtextstream.h>

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
QString QtLog::getAll(const QString& separator) const {
    return (m_header.isEmpty() ? m_header : m_header + separator)
        + m_content +
        (m_footer.isEmpty() ? m_footer : separator + m_footer);
}

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

void appendAsContent(QtLog& to, const QtLog& from)
{
    to.appendContent(from.getAll());
}

void clearLogContent(QtLog& log)
{
    log.setContent("");
}

void saveLog(const QtLog& log, const QString& l_path)
{
    QFile file(l_path);
    if (file.open(QIODeviceBase::WriteOnly))
    {
        QTextStream out{ &file };
        out << log.getAll();
    }
}