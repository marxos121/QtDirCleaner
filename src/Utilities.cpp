#include "../include/Utilities.h"

JobType Utilities::strToJobType(const QString& type)
{
    if (type.toLower() == "move") {
        return JobType::Move;
    }

    if (type.toLower() == "remove") {
        return JobType::Remove;
    }

    return (JobType)-1;
}