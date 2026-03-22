#pragma once

#include "Logger.h"
#if defined (_WIN32)
    #include <windows.h>
#endif
#include <cstdlib>

#include <cstdarg>
#include <cstdio>

namespace FF
{
    inline void AssertImpl(bool condition, const char* file, i32 line, const char* format, ...)
    {
        if (!condition)
        {
            char messageBuffer[LOG_TEMPLATE_LENGTH];

            va_list args;
            va_start(args, format);
            vsnprintf(messageBuffer, LOG_TEMPLATE_LENGTH, format, args);
            va_end(args);

            char finalBuffer[LOG_TEMPLATE_LENGTH];

            snprintf(
                finalBuffer,
                LOG_TEMPLATE_LENGTH,
                "%s\n\n[Assert] [File: %s] [Line: %d]\n",
                messageBuffer,
                file,
                line
            );

            LOG_ERROR("%s", messageBuffer);

#if defined(_WIN32)
            MessageBoxA(
                nullptr,
                finalBuffer,
                "Assert Entered",
                MB_ICONERROR | MB_OK
            );
#endif

            std::abort();
        }
    }
}

#ifdef FF_DEBUG

#define ASSERT(condition, format, ...) \
FF::AssertImpl((condition), __FILE__, __LINE__, (format), ##__VA_ARGS__);

#define ASSERT_NO_ENTRY(format, ...) \
ASSERT(false, format, ##__VA_ARGS__)

#else

#define ASSERT(condition, format, ...) ((void)0)
#define ASSERT_NO_ENTRY(format, ...) ((void)0)

#endif