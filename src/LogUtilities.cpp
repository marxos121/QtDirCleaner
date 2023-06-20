#include "../include/LogUtilities.h"
#include "../include/QtLog.h"
#include <qfile.h>

void Utilities::saveLog(const QtLog& log, const QString& l_path)
{
    QFile file(l_path);
    if (file.open(QIODeviceBase::WriteOnly))
    {
        file.write(Utilities::getFullLog(log, "\n\n").toLocal8Bit());
    }
}

void Utilities::appendAsContent(QtLog& to, const QtLog& from)
{
    to.appendContent(getFullLog(from));
}

QString Utilities::getFullLog(const QtLog& log, const QString& separator) {
    return (log.getHeader().isEmpty() ? log.getHeader() : log.getHeader() + separator)
        + log.getContent() +
        (log.getFooter().isEmpty() ? log.getFooter() : separator + log.getFooter());
}

void Utilities::clearLogContent(QtLog& log)
{
    log.setContent("");
}
