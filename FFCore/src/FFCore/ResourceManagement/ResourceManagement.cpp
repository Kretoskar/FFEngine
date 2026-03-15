#include "FFCore/ResourceManagement/ResourceManagement.h"

#include <ranges>

using namespace FF;

ResourceManager::ResourceManager()
{
    Start();
}

ResourceManager::~ResourceManager()
{
    Stop();
}

void ResourceManager::Start()
{
    _running = true;
    _workerThread = std::thread([this]() 
    {
        WorkerThread();
    });
}

void ResourceManager::Stop()
{
    {
        std::lock_guard<std::mutex> lock(_queueMutex);
        if (_running == false)
        {
            return;
        }
        _running = false;
    }
    _condition.notify_one();
    if (_workerThread.joinable()) 
    {
        _workerThread.join();
    }
}

void ResourceManager::WorkerThread()
{
    while (_running)
    {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(_queueMutex);
            _condition.wait(lock, [this]()
            {
                return !_taskQueue.empty() || !_running;
            });

            if (!_running && _taskQueue.empty()) 
            {
                return;
            }

            task = std::move(_taskQueue.front());
            _taskQueue.pop();
        }

        task();
    }
}

void ResourceManager::UnloadAll()
{
    for (std::unordered_map<HString, std::shared_ptr<Resource>>& typeResources : _resources | std::views::values) 
    {
        for (std::shared_ptr<Resource>& resource : typeResources | std::views::values) 
        {
            if (resource && resource->IsLoaded()) 
            {
                resource->Unload();
            }
        }
    }
    
    _resources.clear();
    _refCounts.clear();
}

bool ResourceManager::ReadTextFile(HString fileName, std::string& outFile)
{
    std::ifstream fileStream(fileName.Get(), std::ios::binary);
    if (!fileStream)
    {
        LOG_ERROR("Error reading %s", fileName.Get())
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