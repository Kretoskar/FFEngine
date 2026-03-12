#pragma once
#include <string>

#include "FFCore/Core/Types.h"

namespace FF::FileSystem
{
    bool ReadFile(const char* fileName, std::string& outFile);

    char* ReadBinaryFile(const char* fileName, i32& size);
    void WriteBinaryFile(const char* fileName, const void* data, i32 size);
}
