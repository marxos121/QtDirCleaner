#pragma once
#include <qstring.h>
class QtLog;

namespace Utilities
{
	QString getFullLog(const QtLog& log, const QString& separator = "\n\n");
	void clearLogContent(QtLog& log);
	void saveLog(const QtLog& log, const QString& l_path = "log.dlog");
	void appendAsContent(QtLog& to, const QtLog& from);
}