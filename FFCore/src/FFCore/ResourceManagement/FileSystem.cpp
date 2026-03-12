#include "FFCore/ResourceManagement/FileSystem.h"

#include <fstream>

#include "FFCore/Core/Logger.h"

bool FF::FileSystem::ReadFile(const char* fileName, std::string& outFile)
{
    std::ifstream fileStream(fileName, std::ios::binary);
    if (!fileStream)
    {
        LOG_ERROR("Error reading %s", fileName)
        return false;
    }

    // get size
    fileStream.seekg(0, std::ios::end);
    const std::streamsize size = fileStream.tellg();
    fileStream.seekg(0, std::ios::beg);

    outFile.clear();
    if (size > 0)
    {
        outFile.resize(static_cast<size_t>(size));
        fileStream.read(outFile.data(), size);
        outFile.resize(static_cast<size_t>(fileStream.gcount()));
    }

    return true;
}

char* FF::FileSystem::ReadBinaryFile(const char* fileName, i32& size)
{
    size = 0;

    if (!fileName) 
    {
        LOG_ERROR("Invalid args to ReadBinaryFile\n")
        return nullptr;
    }

    FILE* f = std::fopen(fileName, "rb");
    if (!f) 
    {
        LOG_ERROR("Error opening '%s': %s\n", fileName, std::strerror(errno))
        return nullptr;
    }

    struct stat stat_buf {};
    if (stat(fileName, &stat_buf) != 0) 
    {
        LOG_ERROR("Error getting file stats for '%s': %s\n", fileName, std::strerror(errno))
        std::fclose(f);
        return nullptr;
    }

    if (stat_buf.st_size < 0 || stat_buf.st_size > std::numeric_limits<std::int32_t>::max()) 
    {
        LOG_ERROR("File too large or invalid size '%s' (%lld)\n",
                  fileName, static_cast<long long>(stat_buf.st_size))
        std::fclose(f);
        return nullptr;
    }

    const auto sizeTemp = static_cast<std::size_t>(stat_buf.st_size);
    char* data = static_cast<char*>(std::malloc(sizeTemp));
    if (!data && sizeTemp != 0) 
    {
        LOG_ERROR("Out of memory allocating %zu bytes for '%s'\n", sizeTemp, fileName);
        std::fclose(f);
        return nullptr;
    }

    const std::size_t bytesRead = std::fread(data, 1, sizeTemp, f);
    if (bytesRead != sizeTemp) 
    {
        LOG_ERROR("Error reading '%s' (read %zu of %zu)\n", fileName, bytesRead, sizeTemp);
        std::free(data);
        std::fclose(f);
        return nullptr;
    }

    std::fclose(f);
    size = static_cast<std::int32_t>(sizeTemp);
    return data;
}

void FF::FileSystem::WriteBinaryFile(const char* fileName, const void* data, i32 size)
{
    if (!fileName || !data || size < 0) 
    {
        LOG_ERROR("Invalid args to WriteBinaryFile\n")
        return;
    }

    FILE* f = std::fopen(fileName, "wb");
    if (!f) 
    {
        LOG_ERROR("Error opening '%s': %s\n", fileName, std::strerror(errno));
        return;
    }

    const auto to_write = static_cast<std::size_t>(size);
    const std::size_t written = std::fwrite(data, 1, to_write, f);

    if (written != to_write) {
        LOG_ERROR("Error writing '%s' (wrote %zu of %zu)\n", fileName, written, to_write)
        std::fclose(f);
        return;
    }

    std::fclose(f);
}
