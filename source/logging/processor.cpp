/*!
    \file processor.cpp
    \brief Logging processor interface implementation
    \author Ivan Shynkarenka
    \date 26.07.2016
    \copyright MIT License
*/

#include "logging/processor.h"

namespace CppLogging {

bool Processor::ProcessRecord(Record& record)
{
    // Process the given logging record with sub processors
    for (auto& processor : _processors)
        if (!processor->ProcessRecord(record))
            return false;

    // Filter the given logging record
    for (auto& filter : _filters)
        if (!filter->FilterRecord(record))
            return false;

    // Layout the given logging record
    for (auto& layout : _layouts)
        layout->LayoutRecord(record);

    // Append the given logging record
    for (auto& appender : _appenders)
        appender->AppendRecord(record);

    return true;
}

} // namespace CppLogging
