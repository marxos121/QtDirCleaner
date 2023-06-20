#pragma once
#include "../include/JobBase.h"

class QString;

namespace Utilities
{
    inline const char* to_string(JobType type)
    {
        return type == JobType::Move ? "Move" :
            (type == JobType::Remove ? "Remove" : "Error");
    }


    JobType strToJobType(const QString& type);
}